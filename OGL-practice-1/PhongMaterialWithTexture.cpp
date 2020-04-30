#include "PhongMaterialWithTexture.h"

PhongMaterialWithTexture::PhongMaterialWithTexture() : PhongMaterial()
{
	this->tex = nullptr;
}

PhongMaterialWithTexture::PhongMaterialWithTexture(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, float shininess, Texture* tex)
	: PhongMaterial(ambient, diffuse, specular, emission, shininess)
{
	this->tex = tex;
}

void PhongMaterialWithTexture::apply()
{
	PhongMaterial::apply();
	if (tex)
		tex->apply();
}

void PhongMaterialWithTexture::load(const char* filename)
{
	// Open the file
	ifstream ifs(filename);

	if (!ifs.is_open())
	{
		cerr << "Couldn't open file " << filename << " for reading." << endl;
		return;
	}

	// Read from file
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw); // Parse file
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	if (doc.HasParseError())
	{
		std::cout << "Error: " << doc.GetParseError() << endl
			<< "Offset: " << doc.GetErrorOffset() << endl;
		return;
	}

	// Get the values
	ambient = vec4
	(
		doc["ambient"][0].GetDouble(),
		doc["ambient"][1].GetDouble(),
		doc["ambient"][2].GetDouble(),
		doc["ambient"][3].GetDouble()
	);

	diffuse = vec4
	(
		doc["diffuse"][0].GetDouble(),
		doc["diffuse"][1].GetDouble(),
		doc["diffuse"][2].GetDouble(),
		doc["diffuse"][3].GetDouble()
	);

	specular = vec4
	(
		doc["specular"][0].GetDouble(),
		doc["specular"][1].GetDouble(),
		doc["specular"][2].GetDouble(),
		doc["specular"][3].GetDouble()
	);

	emission = vec4
	(
		doc["emission"][0].GetDouble(),
		doc["emission"][1].GetDouble(),
		doc["emission"][2].GetDouble(),
		doc["emission"][3].GetDouble()
	);

	shininess = doc["shininess"].GetDouble();

	if (this->tex)
		delete this->tex;

	this->tex = new Texture(doc["texture"].GetString());

	// Debug
	string json_string(buffer.GetString());
	cout << json_string.c_str() << endl;

	// Close the file
	ifs.close();
}

void PhongMaterialWithTexture::setTexture(Texture* tex)
{
	this->tex = tex;
}

PhongMaterialWithTexture::~PhongMaterialWithTexture()
{
	delete tex;
}