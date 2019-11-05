#include "GameObjectFactory.h"


void GameObjectFactory::init()
{
	meshes[0].load(".\\meshes\\ChamferBox.obj");
	meshes[1].load(".\\meshes\\Box.obj");
	meshes[2].load(".\\meshes\\simple_plane.obj");
	meshes[3].load(".\\meshes\\sphere.obj");

	// Initialize materials
	materials[0].load(".\\materials\\mat1.json"); // yellow
	materials[1].load(".\\materials\\mat2.json"); // dark
	materials[2].load(".\\materials\\mat3.json"); // grey
	materials[3].load(".\\materials\\mat4.json"); // plane
	materials[4].load(".\\materials\\player.json"); // player
}

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	shared_ptr<GameObject> tmp(new GameObject);
	GraphicObject tmpGObj;
	
	switch (type)
	{
	case LIGHT_OBJECT:
		tmpGObj.setMaterial(&(this->materials[0]));
		tmpGObj.setMesh(&(this->meshes[0]));
		break;
	case HEAVY_OBJECT:
		tmpGObj.setMaterial(&(this->materials[2]));
		tmpGObj.setMesh(&(this->meshes[0]));
		break;
	case BORDER_OBJECT:
		tmpGObj.setMaterial(&(this->materials[1]));
		tmpGObj.setMesh(&(this->meshes[1]));
		break;
	case MAIN_HERO_OBJECT:
		tmpGObj.setMaterial(&materials[4]);
		tmpGObj.setMesh(&meshes[3]);
		break;
	case PLANE_OBJECT:
		tmpGObj.setMaterial(&(this->materials[3]));
		tmpGObj.setMesh(&(this->meshes[2]));
		tmp->setHeight(-0.5f);
		break;
	}
	tmp->setPosition(x, y);
	tmp->setGraphicObject(tmpGObj);
	return tmp;
}