#include "Camera.h"

Camera::Camera()
{
	this->pos = vec3(0);
	this->spherical = vec3(0, 0, 0);
}

Camera::Camera(vec3 position)
{
	this->pos = position;
	calcSpherical();
	calcPos();
}

Camera::Camera(float x, float y, float z)
{
	this->pos = vec3(x, y, z);
	calcSpherical();
	calcPos();
}

void Camera::setPosition(vec3 position)
{
	this->pos = position;
	calcSpherical();
	calcPos();
}

vec3 Camera::getPosition()
{
	return this->pos;
}

void Camera::rotateLeftRight(float degree)
{
	this->spherical.z += degree;
	if (this->spherical.z > 360.0f || this->spherical.z < -360.0f)
		this->spherical.z -= this->spherical.z;
	calcPos();
}

void Camera::rotateUpDown(float degree)
{
	this->spherical.y += degree;
	if (this->spherical.y > 85.0f)
		this->spherical.y = 85.0f;
	if (this->spherical.y < 5.0f)
		this->spherical.y = 5.0f;
	calcPos();
}

void Camera::zoomInOut(float distance)
{
	this->spherical.x += distance;
	if (this->spherical.x < 2.0f)
		this->spherical.x = 2.0f;
	if (this->spherical.x > 60.0f)
		this->spherical.x = 60.0f;
	calcPos();
}

void Camera::apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, 0, 0, 0, 0, 1, 0);
}

void Camera::calcSpherical()
{
	vec3 projXY = vec3(pos.x, pos.y, 0);
	vec3 projZX = vec3(pos.x, 0, pos.z);
	this->spherical = vec3
	(
		length(this->pos),											// radius
		degrees((acos(dot(normalize(pos), normalize(projZX))))),	// PHI Y
		degrees(acos(dot(normalize(projXY), normalize(projZX))))	// THETA Z
	);
	
}

void Camera::calcPos()
{
	float rCosPhi = this->spherical.x * cos(radians(this->spherical.y));
	this->pos = vec3
	(
		rCosPhi*cos(radians(this->spherical.z)),
		this->spherical.x * sin(radians(this->spherical.y)),
		rCosPhi*sin(radians(this->spherical.z))
	);
}


vec2 Camera::getAngles()
{
	return vec2(spherical.y, spherical.z);
}