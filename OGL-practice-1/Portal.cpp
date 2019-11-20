#include "Portal.h"

Portal::Portal()
{
	isLeft = true;
}

Portal::Portal(ivec4 entries)
{
	this->entries.push_back(ivec2(entries.x, entries.y));
	this->entries.push_back(ivec2(entries.z, entries.w));
	isLeft = true;
}

Portal::Portal(ivec2 entry1, ivec2 entry2)
{
	this->entries.push_back(entry1);
	this->entries.push_back(entry2);
	isLeft = true;
}

Portal::Portal(vector <ivec2> entries)
{
	this->entries = entries;
	isLeft = true;
}

void Portal::AddEntry(ivec2 entry)
{
	this->entries.push_back(entry);
}

bool Portal::isPlayerInPortal()
{
	for (auto entry : entries)
	{
		if (entry == player->getPosition())
			return true;
	}
	return false;
}

bool Portal::isPlayerLeftPortal()
{
	return isLeft;
}

void Portal::setPlayerLeftPortal(bool left)
{
	isLeft = left;
}

ivec2 Portal::getNextPlayerPos()
{
	ivec2 pPos = player->getPosition();
	ivec2 nextPos;
	for (auto it = entries.begin(); it != entries.end(); it++)
	{
		if ((*it) == pPos) // found entry with similar to player pos position
		{
			if (it + 1 != entries.end())
				nextPos = *(it + 1);
			else
				nextPos = *(entries.begin());
			break;
		}
	}
	return nextPos;
}

void Portal::simulate()
{
	ivec2 oldPPos = player->getPosition(),
		  newPPos;
	if (isPlayerInPortal() && entries.size() >= 2)
	{
		if (isPlayerLeftPortal())
		{
			if (!player->isMoving())
			{
				newPPos = getNextPlayerPos();
				player->setPosition(newPPos);
				passabilityMap[oldPPos.y][oldPPos.x] = EMPTY;
				passabilityMap[newPPos.y][newPPos.x] = PLAYER;
				isLeft = false;
			}
		}
	}
	else
		isLeft = true;
}