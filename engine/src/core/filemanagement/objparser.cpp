#include "objparser.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include "renderer/resources/meshBuilder.h"
#include "renderer/resources/gResourceManager.h"

namespace OBJParser
{
	void readFile(const char* path, MeshBuilder& builder)
	{
		OBJParsedData* data = new OBJParsedData();

		// Read file
		try
		{
			std::fstream file(path);

			std::string line;
			while (std::getline(file, line))
			{
				parse(builder, line, *data);
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "Failed to load OBJ: " << path << "\n";
		}

		delete data;
	}

	void OBJParser::parse(MeshBuilder& builder, std::string& line, OBJParsedData& data)
	{
		// Ignore comments
		if (line.empty() || line[0] == '#')
			return;

		bool hasParam = false;
		std::string paramName = "";
		std::vector<std::string> params;
		std::string readingParam = "";

		// Read chars
		for (int i = 0; i < line.size(); i++)
		{
			// Read line type word - e.g. vn for normals
			if (!hasParam)
			{
				if (line[i] != ' ')
					paramName += line[i];
				else
					hasParam = true;

				continue;
			}

			// Store params
			if (line[i] == ' ' && readingParam != "")
			{
				params.push_back(readingParam);
				readingParam = "";
				continue;
			}

			char c = line[i];
			readingParam += c;
		}

		// Push last parameter
		if (!readingParam.empty())
			params.push_back(readingParam);

		// TODO: Change parsing way
		if (paramName == OBJECT_NAME)
		{
			// TODO
		}
		else if (paramName == OBJ_VERTEX)
		{
			// Add vertex position to temp data
			glm::vec3 pos = {
				std::stof(params[0]),
				std::stof(params[1]),
				std::stof(params[2])
			};

			data.vertices.push_back(pos);
		}
		else if (paramName == FACE)
		{
			OBJFace face;
			parseFace(face, data, params);

			std::vector<int> faceIds;
			faceIds.reserve(face.count);

			//int vID = builder.vertexBuffer.size();

			for (int i = 0; i < face.count; i++)
			{
				faceIds.push_back(-1);

				if (data.originalFaces.find(params[i]) == data.originalFaces.end())
				{
					// Add new original face
					int vId = face.vertexIds[i];

					// UVs
					glm::vec2 uv = glm::vec2(0, 0);
					if (!data.uvs.empty())
						uv = face.uvIds[i] == -1 ? glm::vec2(0, 0) : data.uvs[face.uvIds[i]];

					// Normals
					glm::vec3 norm = glm::vec3(0, 0, 0);
					if (!data.normals.empty())
						norm = face.normalIds[i] == -1 ? glm::vec3(0, 0, 0) : data.normals[face.normalIds[i]];

					// Add vertex
					int vertexId = builder.vertexBuffer.size();
					data.originalFaces.insert({ params[i], vertexId });
					builder.addVertices(data.vertices[vId], { 1, 0,0, 1 }, uv, norm);
					faceIds[i] = vertexId;
				}
				else
				{
					// Reuse existing face
					std::string match = params[i];
					int id = data.originalFaces[params[i]];
					VertexAttributes vertex = builder.vertexBuffer[id];
					faceIds[i] = id;
				}

				// Debug
				/*
				std::cout << "Vert - pos: (" << data.vertices[vId].x << ", " << data.vertices[vId].y << ", " << data.vertices[vId].z << ")";
				std::cout << ", uv: (" << uv.x << ", " << uv.y << ")";
				std::cout << ", norm: (" << norm.x << ", " << norm.y << ", " << norm.z << ") \n";
				*/
			}

			for (int i = 1; i < face.count - 1; i++)
			{
				builder.addTriangles(faceIds[0], faceIds[i], faceIds[i + 1]);
			}
		}
		else if (paramName == OBJ_TEXTURE)
		{
			// Add UV position to temp data
			glm::vec2 uv = {
				std::stof(params[0]),
				std::stof(params[1])
			};

			data.uvs.push_back(uv);
		}
		else if (paramName == OBJ_NORMAL)
		{
			// Add normal vector to temp data
			glm::vec3 norm = {
				std::stof(params[0]),
				std::stof(params[1]),
				std::stof(params[2])
			};

			data.normals.push_back(norm);
		}
	}

	void OBJParser::parseFace(OBJFace& face, OBJParsedData& data, std::vector<std::string>& params)
	{
		int verticesSize = data.vertices.size();
		int uvsSize = data.uvs.size();
		int normalsSize = data.normals.size();
		face.count = params.size();

		for (std::string& param : params)
		{
			int currentValuePos = 0;
			std::string currentValue = "";

			for (int i = 0; i < param.size(); i++)
			{
				char c = param[i];

				// Splitter hit
				if (c == FACE_SPLITTER[0])
				{
					// Store value
					switch (currentValuePos)
					{
					case 0: face.vertexIds.push_back(validateStrNumber(currentValue, verticesSize)); break;
					case 1: face.uvIds.push_back(validateStrNumber(currentValue, uvsSize)); break;
					case 2: face.normalIds.push_back(validateStrNumber(currentValue, normalsSize)); break;
					}

					// Move to next value
					currentValuePos++;
					currentValue = "";
					continue;
				}

				if (c == ' ' || i + 1 == param.size())
				{
					if (c != ' ')
						currentValue += c;

					// Store last value
					switch (currentValuePos)
					{
					case 0: face.vertexIds.push_back(validateStrNumber(currentValue, verticesSize)); break;
					case 1: face.uvIds.push_back(validateStrNumber(currentValue, uvsSize)); break;
					case 2: face.normalIds.push_back(validateStrNumber(currentValue, normalsSize)); break;
					}
				}

				// Store value
				currentValue += c;
			}
		}
	}

	int OBJParser::validateStrNumber(std::string str, int elementsSize)
	{
		if (str == "")
			return -1;

		// Validate
		for (char c : str)
		{
			if (c < '0' || c > '9' && c != '-')
				return -1;
		}

		int value = std::stoi(str);

		// Negative values
		if (value < 0)
			value = elementsSize - value;
		else
			value = value - 1;

		return value;
	}
}