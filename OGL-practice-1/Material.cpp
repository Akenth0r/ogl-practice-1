#include "Material.h"


Material::Material()
{
	ambient = diffuse = specular = emission = vec4(0);
	shininess = 0.0f;
}

void Material::setAmbient(vec4 color)
{
	ambient = color;
}


void Material::setDiffuse(vec4 color)
{
	diffuse = color;
}


void Material::setSpecular(vec4 color)
{
	specular = color;
}


void Material::setEmission(vec4 color)
{
	emission = color;
}


void Material::setShininess(float p)
{
	shininess = p;
}

void Material::load(const char* filename)
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
		std::cout << "Error: "  << doc.GetParseError()  << endl
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

	// Debug
	string json_string(buffer.GetString());
	cout << json_string.c_str() << endl;

	// Close the file
	ifs.close();
}

void Material::apply()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(GL_FRONT, GL_SPECULAR, value_ptr(specular));
	glMaterialfv(GL_FRONT, GL_EMISSION, value_ptr(emission));
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}

