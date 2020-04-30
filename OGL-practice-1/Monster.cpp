#include "Monster.h"
#include <time.h>

Monster::Monster() : GameObject()
{
	srand(time(NULL));
	this->endPoint = genNewEndPoint();
	alive = true;
}

bool Monster::isValidMove(ivec2 move)
{

}

ivec2 Monster::genNewEndPoint()
{
	ivec2 newEndPoint;
	do
	{
		newEndPoint.x = rand() % 21;
		newEndPoint.y = rand() % 21;
	} while (passabilityMap[newEndPoint.y][newEndPoint.x] != EMPTY);
	printf("X: %i, Y: %i\n", newEndPoint.x, newEndPoint.y);
	return newEndPoint;
}

void Monster::pathSimulation()
{
	if (alive)
	{
		if (!this->isMoving())
		{
			ivec2 oldPos = position;
			if (this->position == endPoint)
				this->endPoint = genNewEndPoint();
			PathFinder pfinder;
			vector<ivec2> path = pfinder.findPath(this->position, this->endPoint);
			if (!path.empty())
			{
				ivec2 dif = this->position - path[1];
				if (dif.x == 1)
					this->move(MoveDirection::left);
				else if (dif.x == -1)
					this->move(MoveDirection::right);
				else if (dif.y == 1)
					this->move(MoveDirection::up);
				else if (dif.y == -1)
					this->move(MoveDirection::down);
				int tmp = passabilityMap[position.y][position.x];
				passabilityMap[position.y][position.x] = MONSTER;
				passabilityMap[oldPos.y][oldPos.x] = EMPTY;
				ivec2 pPos = player->getPosition();
				if (pPos == position)
				{
						passabilityMap[pPos.y][pPos.x] = EMPTY;
						player = GOFactory.create(EMPTY_OBJECT, pPos.x, pPos.y);
						gameover = true;
				}
			}
			else if (oldPos == position || passabilityMap[path[1].y][path[1].x] == MONSTER)
			{
				this->endPoint = genNewEndPoint();
				return;
			}
		}
	}
}

void Monster::draw()
{
	if (alive)
		GameObject::draw();
}

void Monster::kill()
{
	this->alive = false;
}