#pragma once
#include "Include.h"

class Camera
{
public:
	//Constructors and destructors
	Camera();
	Camera(GLuint* shaderProgram, GLFWwindow* window);
	~Camera();
	Camera& operator= (const Camera& other);

	//Spatial data
	vec3 position;
	vec3 forward;
	vec3 up;
	const float speed = .5f;

	//GLM data
	GLFWwindow* window;
	int* width;
	int* height;

	GLuint* shader;
	mat4 modelToWorld;

	float lastX;
	float lastY;
	const float sensitivity = .05f;

	//Functions
	void Update();
	void mouseMove(GLFWwindow* window, double xpos, double ypos);
};

