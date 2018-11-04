#pragma once
#include "Include.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	//GL variables
	GLuint vao;
	GLuint vbo;
	//Mesh variables
	GLfloat triCount = 0;
	GLfloat coordCount = 0;
	vector<GLfloat> pointData;

	//Render functions
	void Render();
	void Update();
	void InitializeGL(GLuint shader);
	void SetVertices(GLfloat triNum, GLfloat points[]);
};

