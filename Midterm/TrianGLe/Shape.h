#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>
using namespace std;

class Shape
{
public:
	Shape(float xPos = 0, float yPos = 0, float zPos = 0);
	~Shape();
	//Render variables
	GLuint vao;
	GLuint vbo;
	//Data
	float x;
	float y;
	float z;
	GLfloat triCount = 0;
	GLfloat coordCount = 0;
	vector<GLfloat> pointData;

	//Render functions
	void InitializeGL(GLuint shader);
	void Render();
	//Data-related functions
	void SetVertices(GLfloat triNum, GLfloat points[]);
	void Translate(float dx = 0, float dy = 0, float dz = 0);
};

