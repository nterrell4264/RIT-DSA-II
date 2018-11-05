#pragma once
#include "Include.h"

class Shape
{
public:
	Shape(float xPos = 0, float yPos = 0, float zPos = 0);
	~Shape();

	//Data
	vec3 position;
	vec3 rotation;
	//GL variables
	GLuint vao;
	GLuint vbo;
	//Mesh variables\
	//Mesh* mesh;
	GLfloat triCount = 0;
	GLfloat coordCount = 0;
	vector<GLfloat> pointData;

	//Render functions
	void Render();
	void InitializeGL(GLuint shader);
	void SetVertices(GLfloat triNum, GLfloat points[]);

	//Data-related functions
	void Update();
	void Translate(float dx = 0.f, float dy = 0.f, float dz = 0.f);
	void Rotate(float rx = 0.f, float ry = 0.f, float rz = 0.f);
	void Reset();
};

