#include "GameObjectFactory.h"


//void GameObjectFactory::init()
//{
//	meshes[0].load(".\\meshes\\ChamferBox.obj");
//	meshes[1].load(".\\meshes\\Box.obj");
//	meshes[2].load(".\\meshes\\simple_plane.obj");
//	meshes[3].load(".\\meshes\\sphere.obj");
//
//	// Initialize materials
//	materials[0].load(".\\materials\\mat1.json"); // yellow
//	materials[1].load(".\\materials\\mat2.json"); // dark
//	materials[2].load(".\\materials\\mat3.json"); // grey
//	materials[3].load(".\\materials\\mat4.json"); // plane
//	materials[4].load(".\\materials\\player.json"); // player
//}
GameObjectFactory::GameObjectFactory()
{
	gObjType =
	{
		{"LightObject", LIGHT_OBJECT},
		{"HeavyObject", HEAVY_OBJECT},
		{"BorderObject", BORDER_OBJECT},
		{"PlayerObject", MAIN_HERO_OBJECT},
		{"Portal_1_Object", PORTAL1_OBJECT},
		{"Portal_2_Object", PORTAL2_OBJECT},
		{"PlaneObject", PLANE_OBJECT}
	};
}

void GameObjectFactory::init(const char* filenameJSON)
{
	// Open the file
	ifstream ifs(filenameJSON);

	if (!ifs.is_open())
	{
		cerr << "Couldn't open file " << filenameJSON << " for reading." << endl;
		return;
	}
	// Read from file
	rapidjson::IStreamWrapper isw(ifs);
	docJSON.ParseStream(isw); // Parse file
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	docJSON.Accept(writer);

	if (docJSON.HasParseError())
	{
		std::cout << "Error: " << docJSON.GetParseError() << endl
			<< "Offset: " << docJSON.GetErrorOffset() << endl;
		return;
	}


	
	// Init objects
	for (auto it = docJSON.MemberBegin(); it != docJSON.MemberEnd(); it++)
	{
		string name = it->name.GetString();
		initObject(gObjType[name], it);
	}

	// Debug
	string json_string(buffer.GetString());
	cout << json_string.c_str() << endl;

	// Close the file
	ifs.close();
}

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	shared_ptr<GameObject> tmp(new GameObject);
	GraphicObject tmpGObj;
	tmpGObj.setMaterial(&(this->materials[type]));
	tmpGObj.setMesh(&(this->meshes[type]));
	if (type == PLANE_OBJECT)
		tmp->setHeight(-0.5f);
	tmp->setPosition(x, y);
	tmp->setGraphicObject(tmpGObj);
	return tmp;
}

void GameObjectFactory::initObject(GameObjectType type, rapidjson::Value::ConstMemberIterator obj)
{
	// Load mesh
	// TODO: TEXTURES IN NEXT LABS
	meshes[type].load((string(".\\meshes\\") + (obj->value["Mesh"])["FileName"].GetString()).c_str());

	// Now is turn of the material
	// diffuse
	materials[type].setDiffuse( 
		vec4
		(
			(obj->value["Material"])["PhongParameters"]["diffuse"][0].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["diffuse"][1].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["diffuse"][2].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["diffuse"][3].GetDouble()
		)
	);
	
	// ambient
	materials[type].setAmbient(
		vec4
		(
			(obj->value["Material"])["PhongParameters"]["ambient"][0].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["ambient"][1].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["ambient"][2].GetDouble(),
			1.0
		)
	);

	// specular
	materials[type].setSpecular(
		vec4
		(
			(obj->value["Material"])["PhongParameters"]["specular"][0].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["specular"][1].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["specular"][2].GetDouble(),
			1.0
		)
	);

	// emission
	materials[type].setEmission(
		vec4
		(
			(obj->value["Material"])["PhongParameters"]["emission"][0].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["emission"][1].GetDouble(),
			(obj->value["Material"])["PhongParameters"]["emission"][2].GetDouble(),
			1.0
		)
	);

	// shininess
	//materials[type].setShininess(obj->value["Material"]["PhongParameteres"]["shininess"].GetDouble());
}