#pragma once
#include "GL/glew.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

class Sprite
{
public:
	// Screen h\w
	static int screenWidth;
	static int screenHeight;

	// Constructor
	Sprite()=default;
	// Load image from file
	void load(const char* filename, bool flip = false);
	// Out sprite relative to upper left corner of the screen
	void drawFromLeftUp(int x, int y);
	// Out sprite relative to upper right corner of the screen
	void drawFromRightUp(int x, int y);
	// Get width
	int getWidth();
	// Get height
	int getHeight();
	// Destructor
	~Sprite();
private:
	// Img width
	int width;
	// Img height
	int height;
	int format, type;
	// OGL buffer for image storing
	GLuint bufferID;
};
