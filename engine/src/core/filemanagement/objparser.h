#pragma once
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>

class MeshBuilder;
class MeshResource;

struct VertexAttributes;

namespace OBJParser
{
	struct OBJParsedData
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;

		std::map<std::string, int> originalFaces;
	};

	struct OBJFace
	{
		int count = 0;
		std::vector<int> vertexIds;
		std::vector<int> uvIds;
		std::vector<int> normalIds;
	};

	const char* const OBJECT_NAME = "o";
	const char* const OBJ_VERTEX = "v";
	const char* const OBJ_TEXTURE = "vt";
	const char* const OBJ_NORMAL = "vn";
	const char* const FACE = "f";
	const char* const FACE_SPLITTER = "/";
	const char* const MATERIAL_NAME = "usemtl";

	void readFile(const char* path, MeshBuilder& builder);
	void parse(MeshBuilder& builder, std::string& line, OBJParsedData& data);
	void parseFace(OBJFace& face, OBJParsedData& data, std::vector<std::string>& params);

	int validateStrNumber(std::string str, int elementsSize);
};