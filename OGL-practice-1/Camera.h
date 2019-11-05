#pragma once
#include <GL/freeglut.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

using namespace glm;

class Camera
{
public:
	// Camera constructors
	Camera();
	Camera(vec3 position);
	Camera(float x, float y, float z);

	// Get and set camera position
	void setPosition(vec3 position);
	vec3 getPosition();

	// Move and rotate functions
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);

	// Get phi and theta 
	vec2 getAngles();

	// Set camera matrix
	void apply();

	// Default destructor
	~Camera()=default;

private:
	// Vars
	vec3 pos;				// x, y, z
	vec3 spherical;			// r, phi, theta

private:
	// Additional methods
	void calcSpherical();
	void calcPos();
};