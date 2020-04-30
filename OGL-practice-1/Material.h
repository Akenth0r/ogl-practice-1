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

using namespace glm;
using namespace std;

class Material
{
public:
	// Apply material
	virtual void apply() = 0;
	virtual bool isTransparent() { return false; }
};