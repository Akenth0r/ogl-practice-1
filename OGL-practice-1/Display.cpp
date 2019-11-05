#include "Display.h"

void display()
{
	outFPS();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	camera.apply();
	lights[0].apply();
	plane->draw();
	player->draw();

	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
		{
				gameObjects[i][j]->draw();
		}
	glutSwapBuffers();

}


void outFPS()
{
	FPScount++;
	QueryPerformanceCounter(&newDrawTick);
	float delta = float(newDrawTick.QuadPart - oldDrawTick.QuadPart) / frequency.QuadPart;
	if (delta >= 0.5)
	{
		sprintf_s(sFPS, "FPS: %d", (int)(FPScount / delta));
		glutSetWindowTitle(sFPS);
		oldDrawTick = newDrawTick;
		FPScount = 0;
	}

}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, .2, 70.);
}
