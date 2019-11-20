#include "Simulation.h"

void simulation()
{
	float deltaTime = getSimulationTime(); // time from last frame
	controlsSimulation();
	gameObjSimulation(deltaTime);
	glutPostRedisplay();
}


void gameObjSimulation(float deltaTime)
{
	// Move depending on camera position
	// TODO: OPTIMIZE
	vec3 camPos = camera.getPosition();
	vec3 x_axis = vec3(1, 0, 0);
	vec3 z_axis = vec3(0, 0, 1);
	vec3 viewDir = normalize((camPos));
	vec2 angles =
	{
		degrees(dot(viewDir,x_axis)),
		degrees(dot(viewDir, z_axis))
	};

	MoveDirection a, d, w, s, last;
	// Set wasd depending on cam position
	if (abs(angles.x) > abs(angles.y) && angles.x >= 0)		// 1
	{
		d = MoveDirection::up;
		a = MoveDirection::down;
		w = MoveDirection::left;
		s = MoveDirection::right;
	}
	if (abs(angles.x) < abs(angles.y) && angles.y >= 0)		// 2
	{
		d = MoveDirection::right;
		a = MoveDirection::left;
		w = MoveDirection::up;
		s = MoveDirection::down;
	}
	if (abs(angles.x) < abs(angles.y) && angles.y < 0)			// 3
	{
		d = MoveDirection::left;
		a = MoveDirection::right;
		w = MoveDirection::down;
		s = MoveDirection::up;
	}

	if (abs(angles.x) > abs(angles.y) && angles.x < 0)			// 4
	{
		d = MoveDirection::down;
		a = MoveDirection::up;
		w = MoveDirection::right;
		s = MoveDirection::left;
	}

	ivec2 pOldPos = player->getPosition(); // old player pos
	ivec2 pNewPos;						  // new player pos
	if (GetAsyncKeyState(0x57)) // w
	{
		player->move(w);
		last = w;
	}
	else if (GetAsyncKeyState(0x41)) // a
	{
		player->move(a);
		last = a;
	}
	else if (GetAsyncKeyState(0x53)) // s
	{
		player->move(s);
		last = s;
	}
	else if (GetAsyncKeyState(0x44)) // d
	{
		player->move(d);
		last = d;
	}
	else if (GetAsyncKeyState(0x45)) // e
	{
		if (!eIsPressed)
		{
			player->setAutoMove(!(player->getAutoMove()));
			eIsPressed = true;
		}
	}
	else if (!GetAsyncKeyState(0x45))
	{
		eIsPressed = false;
	}

	if (player->getAutoMove())
	{
		PathFinder pf;
		ivec2 pPos = player->getPosition();
		vector<ivec2> path = pf.findPath(pPos, ivec2(19, 1));

		if (!player->isMoving())
		{
			if (!path.empty())
			{
				ivec2 dif = pPos - path[1];
				if (dif.x == 1)
					player->move(MoveDirection::left);
				else if (dif.x == -1)
					player->move(MoveDirection::right);
				else if (dif.y == 1)
					player->move(MoveDirection::up);
				else if (dif.y == -1)
					player->move(MoveDirection::down);
			}
		}
	}

	pNewPos = player->getPosition(); // player position after moving
	if (passabilityMap[pNewPos.y][pNewPos.x] == CHAMFER_BOX) // We've met light box
	{
		ivec2 gameObjOldPos = pNewPos; // old game obj pos is new player pos
		gameObjects[pNewPos.y][pNewPos.x]->move(last); // move
		ivec2 gameObjNewPos = gameObjects[pNewPos.y][pNewPos.x]->getPosition();
		if (passabilityMap[gameObjNewPos.y][gameObjNewPos.x] != EMPTY) //  next from light box gameobj isn't empty
		{
			// Cancel movement before it's start in simulation
			player->setPosition(pOldPos);
			player->stop();
			gameObjects[pNewPos.y][pNewPos.x]->setPosition(gameObjOldPos);
			gameObjects[pNewPos.y][pNewPos.x]->stop();
		}
		else  // next game obj from light box is empty
		{
			passabilityMap[pOldPos.y][pOldPos.x] = EMPTY;
			passabilityMap[pNewPos.y][pNewPos.x] = PLAYER;
			shared_ptr<GameObject> tmp = gameObjects[gameObjOldPos.y][gameObjOldPos.x];
			gameObjects[gameObjOldPos.y][gameObjOldPos.x] = gameObjects[gameObjNewPos.y][gameObjNewPos.x];
			gameObjects[gameObjNewPos.y][gameObjNewPos.x] = tmp;
			passabilityMap[gameObjNewPos.y][gameObjNewPos.x] = CHAMFER_BOX;
		}

	}
	else if (passabilityMap[pNewPos.y][pNewPos.x] == GREY_BOX || passabilityMap[pNewPos.y][pNewPos.x] == DARK_BOX)
	{
		player->setPosition(pOldPos);
		player->stop();
	}
	else if (passabilityMap[pNewPos.y][pNewPos.x] == EMPTY)
	{
		passabilityMap[pOldPos.y][pOldPos.x] = EMPTY;
		passabilityMap[pNewPos.y][pNewPos.x] = PLAYER;
	}
	// TODO: ADD PORTALS
	portals[0].simulate();
	portals[1].simulate();
	// move player
	player->simulate(deltaTime);

	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			gameObjects[i][j]->simulate(deltaTime);
	// player moving
}


float getSimulationTime()
{
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return (float(newSimTick.QuadPart - oldSimTick.QuadPart)) / frequency.QuadPart;
}


void controlsSimulation()
{
	static float sensitivity = 0.2;
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		GetCursorPos(&newCursPos);
		int deltax = newCursPos.x - oldCursPos.x;
		int deltay = newCursPos.y - oldCursPos.y;

		if (deltax || deltay)
		{
			camera.rotateLeftRight(deltax  * sensitivity);
			camera.rotateUpDown(deltay * sensitivity);
		}
		oldCursPos = newCursPos;
	}
	else
	{
		oldCursPos = newCursPos;
		GetCursorPos(&newCursPos);
	}
}


void mouseWheelFunc(int wheel, int direction, int x, int y)
{
	if (direction == 1)
		camera.zoomInOut(-0.5);
	if (direction == -1)
		camera.zoomInOut(0.5);
}