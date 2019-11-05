#pragma once
#include <Windows.h>
#include "GL/glew.h"
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <GLM/glm.hpp>
#include <map>

struct Vertex
{
	GLfloat coord[3];
	GLfloat normal[3];
	GLfloat texCoord[2];
};

class Mesh
{
public:
	// Constructor
	Mesh();
	// Load mesh from file
	void load(const char* filename);
	// Out mesh
	void draw();
	~Mesh();

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLuint buffers[2];
};