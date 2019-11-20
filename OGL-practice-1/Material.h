#pragma once
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <fstream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <string>
#include <iostream>

using namespace glm;
using namespace std;

class Material
{
public:
	Material();

	// Set material parameters
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);

	// Load parameters from external JSON file
	void load(const char* filename);

	// Set all parameters
	void apply();

	// Check if material is transparent
	bool isTransparent();

	~Material()=default;

private:
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};