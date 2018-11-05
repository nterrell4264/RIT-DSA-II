#include "Shape.h"

Shape::Shape(float xPos, float yPos, float zPos)
{
	position = vec3(xPos, yPos, xPos);
	rotation = vec3(0);
	mesh = new Mesh();
}
Shape::~Shape()
{
	mesh = nullptr;
}

void Shape::Translate(float dx, float dy, float dz) {
	position += vec3(dx,dy,dz);
}
void Shape::Rotate(float rx, float ry, float rz)
{
	rotation += vec3(rx, ry, rz);
}
void Shape::Update() {
	mesh->Update();
}

void Shape::Reset() {
	rotation = vec3(0);
}
