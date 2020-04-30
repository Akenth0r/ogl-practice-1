#include "GraphicObject.h"

GraphicObject::GraphicObject()
{
	position = vec3(0);
	angle = 0;
	model = mat4(1);
	material = nullptr;
	mesh = nullptr;
}

void GraphicObject::setPos(const vec3 &pos)
{
	position = pos;
	recalculateModelMat();
}

vec3 GraphicObject::getPos()
{
	return position;
}

void GraphicObject::setAngle(GLfloat deg)
{
	angle = deg;
	recalculateModelMat();
}

GLfloat GraphicObject::getAngle()
{
	return angle;
}

void GraphicObject::setMaterial(Material* material)
{
	this->material = material;
}

bool GraphicObject::isTransparent()
{
	if (material)
		return material->isTransparent();
	return false;
}

void GraphicObject::draw()
{
	glPushMatrix();
	if (material)
	{
		material->apply();
	}
	glMultMatrixf(value_ptr(model));
	if (mesh)
		mesh->draw();
	Texture::disableAll();
	glPopMatrix();
}


void GraphicObject::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void GraphicObject::recalculateModelMat()
{
	model = translate(position) * rotate(radians(angle), vec3(0, 1, 0));
}