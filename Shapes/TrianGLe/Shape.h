#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
class Shape
{
public:
	Shape();
	~Shape();
	GLfloat triCount = 0;
	GLfloat* pointData = nullptr;

	void SetVertices(GLfloat triNum, GLfloat* points);
};

