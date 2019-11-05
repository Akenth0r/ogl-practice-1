#pragma once
#include "Mesh.h"
#include "GraphicObject.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include <memory>
class GameObjectFactory;

enum MESH_TYPES
{
	EMPTY,			// 0
	CHAMFER_BOX,	// 1
	GREY_BOX,		// 2
	DARK_BOX,		// 3
	PLAYER			// 4
};


extern const int gObjCount;
extern const int LightCount;
extern const int MaterialCount;
extern const int MeshCount;

extern bool eIsPressed;

// Variables
extern Light lights[1];
extern GameObjectFactory GOFactory;
extern Camera camera;
extern shared_ptr<GameObject>  gameObjects[21][21];
extern shared_ptr<GameObject>  player;
extern shared_ptr<GameObject> plane;

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
