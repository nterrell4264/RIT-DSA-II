#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <vector>
using namespace std;

class Shape
{
public:
	Shape(float xPos = 0, float yPos = 0, float zPos = 0);
	~Shape();
	//GL variables
	GLuint vao;
	GLuint vbo;
	mat4 worldMatrix;
	//Data
	vec3 position;
	vec3 rotation;
	GLfloat triCount = 0;
	GLfloat coordCount = 0;
	vector<GLfloat> pointData;

	bool spinning = false;

	//Render functions
	void InitializeGL(GLuint shader);
	void Render();
	void Update();
	//Data-related functions
	void SetVertices(GLfloat triNum, GLfloat points[]);
	void Translate(float dx = 0.f, float dy = 0.f, float dz = 0.f);
	void Rotate(float rx = 0.f, float ry = 0.f, float rz = 0.f);
	void Reset();
};

