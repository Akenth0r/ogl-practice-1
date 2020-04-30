#pragma once
#include "Data.h"
#include "PathFinder.h"

void mouseWheelFunc(int wheel, int direction, int x, int y);
void gameObjSimulation(float deltaTime);
float getSimulationTime();
// Camera rotation
void controlsSimulation();
void simulation();
void bombSimulation(float deltaTime);
void monsterSimulation();