#pragma once
#include "Mesh.h"
#include "GraphicObject.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include <memory>
#include "Portal.h"
#include "Sprite.h"
#include "Bomb.h"
#include "Monster.h"


class GameObjectFactory;
class Portal;
class Sprite;
class Monster;

enum MESH_TYPES
{
	EMPTY,			// 0
	CHAMFER_BOX,	// 1
	GREY_BOX,		// 2
	DARK_BOX,		// 3
	PLAYER,			// 4
	PORTAL1,		// 5
	PORTAL2,		// 6
	BOMB,			// 7
	MONSTER			// 8
};


extern const int gObjCount;
extern const int LightCount;
extern const int MaterialCount;
extern const int MeshCount;
extern const int p1_entries_count;
extern const int p2_entries_count;
extern vector<Monster*> monsters;
extern bool eIsPressed,
		    oneIsPressed,
		    multisample_mode,
		    gameover,
			twoIsPressed;

// Variables
extern Light lights[1];
extern GameObjectFactory GOFactory;
extern Camera camera;
extern shared_ptr<GameObject>  gameObjects[21][21];
extern shared_ptr<GameObject>  player;
extern shared_ptr<GameObject>  plane;
extern Portal portals[2];
extern shared_ptr<GameObject> portal1_entries[4];
extern shared_ptr<GameObject> portal2_entries[2];
extern shared_ptr<GameObject> bomb_gobj;
extern Bomb bomb;
extern Sprite authorSpr,
		bombSpr,
		bombTickSpr;
extern char sFPS[30];
extern int FPScount;

// Ticks
extern LARGE_INTEGER frequency;
extern LARGE_INTEGER oldSimTick;
extern LARGE_INTEGER newSimTick;
extern LARGE_INTEGER oldDrawTick;
extern LARGE_INTEGER newDrawTick;
extern POINT oldCursPos;
extern POINT newCursPos;

// Passability map
extern int passabilityMap[21][21];

void initData();
