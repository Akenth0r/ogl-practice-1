#pragma once
#include <GL/glew.h>
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

enum TexFilters { NEAREST, BILINEAR, BILINEAR_MIPMAP, THREELINEAR, ANISO2, ANISO4, ANISO8, ANISO16, ANISO32, TEXFILTERS_COUNT };

class Texture
{
public:
	Texture(const char* filename);
	// Load texture from file
	void load(const char* filename);
	// Apply texture (bind to a texture block and parameter settings)
	void apply(GLenum texUnit = GL_TEXTURE0);
	// Disable texturing for all tex blocks
	static void disableAll();

	// Filtering mode
	static int texFilterMode;

private:
	// Texture block id
	GLuint texIndex;

	// Set texture mode
	void applyTextureMode();
};