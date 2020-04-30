#pragma once
#include <memory>
#include "Data.h"
#include "GameObject.h"
#include "rapidjson/rapidjson.h"
#include <string>
#include <map>
#include "PhongMaterial.h"
#include "PhongMaterialWithTexture.h"
#include "Monster.h"
enum GameObjectType
{
	LIGHT_OBJECT,
	HEAVY_OBJECT,
	BORDER_OBJECT,
	MAIN_HERO_OBJECT,
	MONSTER_OBJECT,
	PLANE_OBJECT,
	PORTAL1_OBJECT,
	PORTAL2_OBJECT,
	BOMB_OBJECT,
	MAX_OBJECT_COUNT,
	EMPTY_OBJECT
};


class GameObjectFactory
{
public:
	GameObjectFactory();
	// Initialization (meshes, materials et cetera)
	//void init();
	void init(const char* filenameJSON);
	// Create new object
	shared_ptr<GameObject> create(GameObjectType type, int x, int y);
	~GameObjectFactory()=default;
	
private:
	Mesh	  meshes[MAX_OBJECT_COUNT];
	Material* materials[MAX_OBJECT_COUNT];
	rapidjson::Document docJSON;
	map<string, GameObjectType> gObjType;
	void initObject(GameObjectType type, rapidjson::Value::ConstMemberIterator obj);
};