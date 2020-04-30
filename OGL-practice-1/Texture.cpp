#include "Texture.h"
//
//// Load texture from file
//void load(char filename);
//// Apply texture (bind to a texture block and parameter settings)
//void apply(GLenum texUnit = GL_TEXTURE0);
//// Disable texturing for all tex blocks
//static void disableAll();
//
//// Filtering mode
//static int texFilterMode;
//
//private:
//	// Texture block id
//	GLuint texIndex;
Texture::Texture(const char* filename)
{
	this->load(filename);
}

void Texture::load(const char* filename)
{
	// Make an image
	ILuint img = ilGenImage();
	ilBindImage(img);
	if (!ilLoadImage(filename))
		printf("ERROR: cannot load image %s\n", filename);

	// Get the width and height of our image
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	printf("Path: \"%s\"\nwidth: %i; height: %i\n", filename, width, height);

	// Copy to temp buf
	ILubyte* buf = new ILubyte[width * height * 4];
	ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, buf);

	// Copy from temp buf to ogl texture
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texIndex);
	glBindTexture(GL_TEXTURE_2D, texIndex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	glBindTexture(GL_TEXTURE_2D, 0);

	ilBindImage(0);
	// Clear memory
	delete[] buf;
	ilDeleteImage(img);
}

void Texture::apply(GLenum texUnit)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, texIndex);
	glEnable(GL_TEXTURE_2D);
	applyTextureMode();
	glTexEnvi(GL_TEXTURE_ENV_MODE, GL_MODULATE, 1);
	// TODO:  AF 
}

void Texture::disableAll()
{
	int textureUnits = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &textureUnits);
	for (int i = 0; i < textureUnits; i++)
		glDisable(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Texture::applyTextureMode()
{
	const int params[3] = { GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_MAX_TEXTURE_MAX_ANISOTROPY };
	const int modes[9][3] =
	{
		{GL_NEAREST, GL_NEAREST, 1},
		{GL_LINEAR, GL_LINEAR, 1},
		{GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, 1},
		{GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, 1},
		{GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, 2},
		{GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, 4},
		{GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, 8},
		{GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, 16},
		{GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, 32},
	};

	for (int i = 0; i < 3; i++)
		glTexParameteri(GL_TEXTURE_2D, params[i], modes[Texture::texFilterMode][i]);
}