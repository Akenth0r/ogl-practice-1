#include "Data.h"

const int gObjCount = 5;
const int LightCount = 1;
const int MaterialCount = 5;
const int MeshCount = 4;


Light lights[LightCount];
Camera camera;
shared_ptr<GameObject>  gameObjects[21][21];
shared_ptr<GameObject>  player;
shared_ptr<GameObject>  plane;
shared_ptr<GameObject>  bomb_gobj;
//shared_ptr<GameObject> portal1_entries[4];
//shared_ptr<GameObject> portal2_entries[2];
Portal portals[2];
vector<ivec2> p1_entries,
			  p2_entries;

bool eIsPressed = false,
	 oneIsPressed = false,
	 multisample_mode = false,
	 gameover = false;

LARGE_INTEGER frequency;
LARGE_INTEGER oldSimTick;
LARGE_INTEGER newSimTick;
LARGE_INTEGER oldDrawTick;
LARGE_INTEGER newDrawTick;
POINT oldCursPos;
POINT newCursPos;
Sprite authorSpr,
	   bombSpr,
	   bombTickSpr;
char sFPS[30];
Bomb bomb;
int FPScount;
// Passability map
int passabilityMap[21][21] = {
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,5,3,
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,5,1,0,0,0,3,
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,6,1,0,3,
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
3,0,0,0,0,0,2,0,2,0,0,6,2,0,1,0,0,0,2,0,3,
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
3,0,1,5,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,5,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

int Sprite::screenHeight;
int Sprite::screenWidth;
GameObjectFactory GOFactory;

void initData()
{
	GOFactory.init(".\\scene.json");
	// Initialize camera
	camera.setPosition(vec3(1.0, 10.0, 5.0));

	// Initialize light sources
	lights[0].setPosition(vec3(0.0f, 20.0f, 2.0f));
	lights[0].setAmbient(vec4(.8f, .8f, .8f, 1.0f));
	lights[0].setDiffuse(vec4(.5f, .5f, .5f, 1.f));
	lights[0].setSpecular(vec4(0.1f, 0.1f, 0.1f, 1.0f));

	plane = GOFactory.create(PLANE_OBJECT, 10, 10);
	player = GOFactory.create(MAIN_HERO_OBJECT, 1, 1);
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
		{
			switch (passabilityMap[i][j])
			{
			case EMPTY:  gameObjects[i][j] = GOFactory.create(EMPTY_OBJECT, j, i);  break;
			case CHAMFER_BOX: gameObjects[i][j] = GOFactory.create(LIGHT_OBJECT, j, i); break;
			case GREY_BOX: gameObjects[i][j] = GOFactory.create(HEAVY_OBJECT, j, i); break;
			case DARK_BOX: gameObjects[i][j] = GOFactory.create(BORDER_OBJECT, j, i); break;
			case PLAYER: gameObjects[i][j] = GOFactory.create(EMPTY_OBJECT, j, i); break;
			case PORTAL1: 
				gameObjects[i][j] = GOFactory.create(PORTAL1_OBJECT, j, i);
				p1_entries.push_back(ivec2(j, i));
				break;
			case PORTAL2:
				gameObjects[i][j] = GOFactory.create(PORTAL2_OBJECT, j, i);
				p2_entries.push_back(ivec2(j, i));
				break;
			default: break;
			}
		}


	// Initialize portals
	portals[0] = Portal(p1_entries);
	portals[1] = Portal(p2_entries);

	// Load sprites
	authorSpr.load("SPRITES\\author.png");
	bombSpr.load("SPRITES\\Bomb.ico");
	bombTickSpr.load("SPRITES\\BombTick.tga");

	// Initialize bomb object
	bomb_gobj = GOFactory.create(BOMB_OBJECT, 0, 0);

	// Set bomb sprites
	bomb.setSprites(&bombSpr, &bombTickSpr);

	// Enter in the main loop
	QueryPerformanceCounter(&newSimTick);
	QueryPerformanceFrequency(&frequency);
	newSimTick = newDrawTick;

}
