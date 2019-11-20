#pragma once
#include <Windows.h>
#include "GraphicObject.h"
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <memory>

enum class MoveDirection
{
	stop,
	left,
	right,
	up,
	down
};

class GameObject
{
public:
	GameObject();

	// Set graphic object by copy
	void setGraphicObject(GraphicObject graphicObject);

	// Set logic coords
	void setPosition(int x, int y);
	void setPosition(ivec2 position);
	
	// Set height
	void setHeight(float h);

	// Get height
	float getHeight();

	// Get current logic coords
	ivec2 getPosition();

	// Get current world coords
	vec3 getWorldPosition();

	// Move in selected direction
	void move(MoveDirection direction, float speed = 3.0f);

	// Cancel moving before simulation
	void stop();

	// Check if game object is moving
	bool isMoving();

	// simulation func
	void simulate(float sec);

	// Check if game object is transparent
	bool isTransparent();

	// Draw game object
	void draw();

	bool getAutoMove();

	void setAutoMove(bool flag);

	~GameObject()=default;

private:
	ivec2 position;
	float h;
	GraphicObject graphicObject;
	MoveDirection state;
	float progress;
	float speed;
	bool autoMove;
};