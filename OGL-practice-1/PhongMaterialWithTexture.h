#pragma once
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
#include "Material.h"
#include "PhongMaterial.h"
#include "Texture.h"

class PhongMaterialWithTexture : public PhongMaterial
{
public:
	// Def constructor
	PhongMaterialWithTexture();
	// Constructor with params
	PhongMaterialWithTexture(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, float shininess, Texture* tex);
	// Load material from json file
	void load(const char* filename);
	// Apply texture phong material
	void apply();
	// Set Texture
	void setTexture(Texture* tex);
	~PhongMaterialWithTexture();

private:
	Texture* tex;
};