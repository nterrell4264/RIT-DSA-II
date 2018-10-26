#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>
using namespace std;

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
	GLfloat coordCount = 0;
	vector<GLfloat> pointData;

	//Render functions
	void InitializeGL(GLuint shader);
	void Render();
	//Data-related functions
	void SetVertices(GLfloat triNum, GLfloat points[]);
	void Translate(float x, float y, float z = 0);
};

