#include "GameObject.h"



GameObject::GameObject()
{
	position = ivec2(0);
	graphicObject = GraphicObject();
	h = 0.0f;
	state = MoveDirection::stop;
	speed = 0.0f;
	progress = 0.0f;
	autoMove = false;
}


void GameObject::setGraphicObject(GraphicObject graphicObject)
{
	this->graphicObject = graphicObject;
}

void GameObject::setPosition(int x, int y)
{
	position = ivec2(x, y);
}


void GameObject::setPosition(ivec2 position)
{
	this->position = position;
}


void GameObject::draw()
{
	if (!isMoving())
		graphicObject.setPos(vec3(position.x - 10, h, position.y - 10));
	graphicObject.draw();
}


ivec2 GameObject::getPosition()
{
	return position;
}


vec3 GameObject::getWorldPosition()
{
	return graphicObject.getPos();
}


void GameObject::move(MoveDirection direction, float speed)
{
	
	if (!isMoving())
		switch (direction)
		{
		case MoveDirection::down:
			if (position.y + 1 <= 20)
			{
				this->state = direction;
				this->speed = speed;
				position.y += 1;
			}
			break;
		case MoveDirection::up:
			if (position.y - 1 >= 0)
			{
				this->state = direction;
				this->speed = speed;
				position.y -= 1;
			}
			break;
		case MoveDirection::left:
			if (position.x - 1 >= 0)
			{
				this->state = direction;
				this->speed = speed;
				position.x -= 1;
			}
			break;
		case MoveDirection::right:
			if (position.x + 1 <= 20)
			{
				this->state = direction;
				this->speed = speed;
				position.x += 1;
			}
			break;
		case MoveDirection::stop:
			break;
		}
	
}


bool GameObject::isMoving()
{
	return state != MoveDirection::stop;
}

void GameObject::stop()
{
	state = MoveDirection::stop;
	progress = 0;
}


void GameObject::simulate(float sec)
{
	vec3 gObjPos = graphicObject.getPos();
	if (progress >= 1.0f)
	{
		state = MoveDirection::stop;
		progress = 0;
	}
		float dmove = speed * sec;

		switch (state)
		{
		case MoveDirection::down:
			gObjPos = vec3(gObjPos.x, gObjPos.y, gObjPos.z + dmove);
			progress += dmove;
			break;
		case MoveDirection::up:
			gObjPos = vec3(gObjPos.x, gObjPos.y, gObjPos.z - dmove);
			progress += dmove;
			break;
		case MoveDirection::left:
			gObjPos = vec3(gObjPos.x - dmove, gObjPos.y, gObjPos.z);
			progress += dmove;
			break;
		case MoveDirection::right:
			gObjPos = vec3(gObjPos.x + dmove, gObjPos.y, gObjPos.z);
			progress += dmove;
			break;
		case MoveDirection::stop:
			break;
		}
		graphicObject.setPos(gObjPos);
}

float GameObject::getHeight()
{
	return h;
}


void GameObject::setHeight(float h)
{
	this->h = h;
}

void GameObject::setAutoMove(bool flag)
{
	this->autoMove = flag;
}

bool GameObject::getAutoMove()
{
	return this->autoMove;
}