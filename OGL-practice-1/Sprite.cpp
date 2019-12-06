#include "Sprite.h"

void Sprite::load(const char* filename, bool flip)
{
	// Make an image
	ILuint img = ilGenImage();
	ilBindImage(img);
	if (!ilLoadImage(filename))
		printf("ERROR: cannot load image %s\n", filename);
	if (flip)
		iluFlipImage();

	// Get the width and height of our image
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	printf("Path: \"%s\"\nwidth: %i; height: %i\n", filename, width, height);

	// Copy to temp buf
	ILubyte* buf = new ILubyte[width * height * 4];
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, buf);

	// Copy from temp buf to ogl pixel unpack buf
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferID);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, buf, GL_DYNAMIC_COPY);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	// Clear memory
	delete[] buf;
	ilDeleteImage(img);
}

void Sprite::drawFromLeftUp(int x, int y)
{
	// As usual
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glWindowPos2i(x, screenHeight - y);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferID);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	glDisable(GL_BLEND);
}

void Sprite::drawFromRightUp(int x, int y)
{
	// Reversed
	glWindowPos2i(screenWidth - x, screenHeight - y);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferID);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	glDisable(GL_BLEND);
}

int Sprite::getHeight()
{
	return height;
}

int Sprite::getWidth()
{
	return width;
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &bufferID);
}