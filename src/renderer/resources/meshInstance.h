#pragma once
#include <GLFW/glfw3.h>

class TextureResource;

class MeshResource
{
public:
	GLuint VOA; // Vertex object array
	GLuint VBO; // Vertex Buffer Object
	GLuint EBO; // Element Buffer Object
	int indicesCount;
	TextureResource* textureRes;

	~MeshResource();

	void cleanup();
};


//------------------------------------------------------------------------------
// Mesh instance
//------------------------------------------------------------------------------

class MeshInstance
{

};