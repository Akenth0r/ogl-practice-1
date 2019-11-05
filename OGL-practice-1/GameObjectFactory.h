#pragma once
#include <memory>
#include "Data.h"
#include "GameObject.h"
enum GameObjectType
{
	LIGHT_OBJECT,
	HEAVY_OBJECT,
	BORDER_OBJECT,
	MAIN_HERO_OBJECT,
	MONSTER_OBJECT,
	PLANE_OBJECT,
	MAX_OBJECT_COUNT,
	EMPTY_OBJECT
};


class GameObjectFactory
{
public:
	GameObjectFactory()=default;
	// Initialization (meshes, materials et cetera)
	void init();
	// Create new object
	shared_ptr<GameObject> create(GameObjectType type, int x, int y);
	~GameObjectFactory()=default;
	
private:
	Mesh	 meshes[MAX_OBJECT_COUNT];
	Material materials[MAX_OBJECT_COUNT];
};