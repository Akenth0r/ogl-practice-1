#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Mesh.h"
#include "GraphicObject.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "GameObject.h"
#include "Data.h"
#include "Simulation.h"
#include "Display.h"
#include "PathFinder.h"

using namespace std;
using namespace glm;


int main(int argc, char* argv[])
{
	// Initialize glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Lab1");
	// Init GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		cerr << "GLEW INITIALIZATION ERROR: " << glewGetErrorString(error) << endl;
		system("pause");
	}
	else
		cout << "GLEW VERSION " << glewGetString(GLEW_VERSION) << endl;

	// Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(simulation);
	glutMouseWheelFunc(mouseWheelFunc);
	
	initData();
	glutMainLoop();

	return 0;
}

