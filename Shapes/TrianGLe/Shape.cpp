#include "Shape.h"

Shape::Shape()
{
}


Shape::~Shape()
{
	delete[] pointData;
}

void Shape::SetVertices(GLfloat triNum, GLfloat* points)
{
	triCount = triNum;
	pointData = points;
}
