#pragma once
#include "GL/glew.h"

#include "Sprite.h"
class Bomb
{
public:
	// Constructor
	Bomb();
	// Start counting
	void start();
	// Main method (returns true if bomb is exploding)
	bool count(float deltaTime);
	// Set bomb timer in seconds
	void setTimer(float timeInSeconds);
	// Get bomb timer in seconds
	float getTimer();
	// Set sprites
	void setSprites(Sprite* bombIcon, Sprite* bombTick);
	// draw HUD
	void drawHUD();
	// Is bomb ticking
	bool isTicking();

private:
	// Private Methods

	// Private Fields
	// Sprites
	Sprite  *bombIcon,
			*bombTick;
	// Is bomb ticking
	bool isBombTicking;
	// Current tick time
	float curTime;
	// Current drawtime
	float curDrawTime;
	// Max time
	float timer;
	// Timer lines to draw count
	int lineCount;
	// Time to delete one line
	float timePerLine;
};

