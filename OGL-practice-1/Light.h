#pragma once
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

using namespace glm;

class Light
{
public:
	// Constructors
	Light();
	Light(vec3 position);
	Light(float x, float y, float z);

	// Set different light source parameters
	void setPosition(vec3 position);
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);

	// Apply a light source
	void apply(GLenum LightNumber = GL_LIGHT0);
	
	~Light()=default;

private:
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};