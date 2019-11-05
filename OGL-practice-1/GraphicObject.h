#pragma once
#include "Mesh.h"
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Material.h"

using namespace glm;

class GraphicObject
{
public:
	// Default constructor
	GraphicObject();

	// Set and get object pos
	void setPos(const vec3 &pos);
	vec3 getPos();

	// Set and get rotation angle
	void setAngle(GLfloat deg);
	GLfloat getAngle();

	// Set current object material
	void setMaterial(Material* material);

	// Set object mesh
	void setMesh(Mesh* mesh);

	// Draw object on the screen
	void draw();

private:
	// Object pos in the world space
	vec3 position;
	// Rotation angle (in degrees)
	GLfloat angle;
	// Model material
	Material* material;
	// Model mesh
	Mesh* mesh;
	// Model matrix
	mat4 model;

	// Recalculate matrix using current values of pos, angle and color
	void recalculateModelMat();
};