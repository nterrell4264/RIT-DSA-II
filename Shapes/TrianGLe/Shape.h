#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
class Shape
{
public:
	Shape();
	~Shape();
	//Render variables
	GLuint vao;
	GLuint vbo;
	//Data
	GLfloat triCount = 0;
	GLfloat vertexCount = 0;
	GLfloat* pointData = nullptr;

	//Render functions
	void SetShader(GLuint shader);
	void Render();
	//Data-related functions
	void SetVertices(GLfloat triNum, GLfloat* points);
	void Translate(float x, float y, float z);
};

