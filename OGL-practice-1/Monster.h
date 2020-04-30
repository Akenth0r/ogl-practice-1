#pragma once
#include "GameObject.h"
#include <GLM/glm.hpp>
#include <memory>
#include "PathFinder.h"

class Monster :
	public GameObject
{
public:
	Monster();
	bool isValidMove(ivec2 move);
	ivec2 genNewEndPoint();
	void pathSimulation();
	void draw();
	void kill();
private:
	
	ivec2 endPoint;
	bool alive;
};