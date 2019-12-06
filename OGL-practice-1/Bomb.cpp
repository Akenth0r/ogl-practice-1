#include "Bomb.h"

Bomb::Bomb()
{
	isBombTicking = false;
	curTime = 0.0f;
	curDrawTime = 0.0f;
	timer = 3.0f;
	lineCount = 10;
	timePerLine = timer / (lineCount + 1);
	bombIcon = bombTick = nullptr;
}

void Bomb::start()
{
	if (!isBombTicking)
		isBombTicking = true;
}

bool Bomb::count(float deltaTime)
{
	bool explode = false;
	
	if (isBombTicking)
	{
		curTime += deltaTime;
		curDrawTime += deltaTime;
		if (curTime > timer)
		{
			explode = true;
			curTime = 0.0f;
			lineCount = 10;
			isBombTicking = false;
		}

		if (curDrawTime > timePerLine)
		{
			lineCount--;
			curDrawTime = 0.0f;
		}
	}
	return explode;
}

void Bomb::setTimer(float timeInSeconds)
{
	timer = timeInSeconds;
}

float Bomb::getTimer()
{
	return timer;
}

void Bomb::drawHUD()
{
	int offset_x = 20,
		offset_y = 80;
	
	if (lineCount >= 0)
	{
		bombIcon->drawFromLeftUp(offset_x, offset_y);
		offset_x += bombIcon->getWidth() + 5;
	}

	int line_w = bombTick->getWidth();
	for (int i = 0; i < lineCount; i++)
	{
		bombTick->drawFromLeftUp(offset_x, offset_y);
		offset_x += line_w + 2; // width + 5 pixels offset
	}

}

void Bomb::setSprites(Sprite* bombIcon, Sprite* bombTick)
{
	this->bombIcon = bombIcon;
	this->bombTick = bombTick;
}

bool Bomb::isTicking()
{
	return isBombTicking;
}