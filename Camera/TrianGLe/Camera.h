#pragma once
#include "Include.h"

class Camera
{
public:
	//Constructors and destructors
	Camera();
	Camera(GLuint* shaderProgram, GLFWwindow* window, vec3 location = vec3(0.f, 0.f, -10.f));
	~Camera();
	Camera& operator= (const Camera& other);

	//Spatial data
	vec3 position;
	vec3 forward;
	vec3 up;
	vec3 right;
	const float speed = .5f;

	float yaw;
	float pitch;

	//GLM data
	GLFWwindow* window;
	int* width;
	int* height;

	GLuint* shader;
	mat4 modelToWorld;

	float lastX;
	float lastY;
	const float sensitivity = .005f;
	bool clickIn = true;

	//Functions
	void Update();
	void mouseMove(double xpos, double ypos);
};

