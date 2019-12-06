#include "Display.h"

void display()
{
	outFPS();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//glEnable(GL_MULTISAMPLE);

	camera.apply();
	lights[0].apply();

	drawOpaque();

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	drawTransparent();
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	drawSprites();

	glutSwapBuffers();

	string title = string(sFPS) + string(" || Antialiasing: ") + (multisample_mode?string(" on"):string(" off"));
	glutSetWindowTitle(title.c_str());
}

void drawOpaque()
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			if (!gameObjects[i][j]->isTransparent())
				gameObjects[i][j]->draw();
	if (!plane->isTransparent())
		plane->draw();
	if (!player->isTransparent())
		player->draw();
	if (bomb.isTicking())
		bomb_gobj->draw();
}

void drawTransparent()
{
	glDepthMask(false);
	glEnable(GL_CULL_FACE);
	
	// Front face
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			if (gameObjects[i][j]->isTransparent())
				gameObjects[i][j]->draw();
	if (plane->isTransparent())
		plane->draw();
	if (player->isTransparent())
		player->draw();
	//  Back face
	glCullFace(GL_BACK);
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			if (gameObjects[i][j]->isTransparent())
				gameObjects[i][j]->draw();
	if (plane->isTransparent())
		plane->draw();
	if (player->isTransparent())
		player->draw();

	glCullFace(GL_FRONT);
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);


}

void outFPS()
{
	FPScount++;
	QueryPerformanceCounter(&newDrawTick);
	float delta = float(newDrawTick.QuadPart - oldDrawTick.QuadPart) / frequency.QuadPart;
	if (delta >= 0.5)
	{
		sprintf_s(sFPS, "FPS: %d", (int)(FPScount / delta));
		//glutSetWindowTitle(sFPS);
		oldDrawTick = newDrawTick;
		FPScount = 0;
	}

}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	Sprite::screenWidth = w;
	Sprite::screenHeight = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, .2, 70.);
}


void drawSprites()
{
	// Sprites
	authorSpr.drawFromRightUp(200, 50);
	if (bomb.isTicking())
		bomb.drawHUD();
}