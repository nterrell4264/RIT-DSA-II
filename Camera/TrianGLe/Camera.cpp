#include "Camera.h"

Camera::Camera() { //pls no userino in code
	width = new int;
	height = new int;
}

Camera::Camera(GLuint* shaderProgram, GLFWwindow* glfwWindow)
{
	position = vec3(0.f, 1.f, -10.f);
	forward = vec3(0.f, 0.f, 1.f);
	up = vec3(0.f, 1.f, 0.f);

	window = glfwWindow;
	width = new int;
	height = new int;
	glfwGetWindowSize(window, width, height);
	lastX = *width / 2;
	lastY = *height / 2;

	shader = shaderProgram;
	modelToWorld = glm::identity<glm::mat4>();
}

Camera::~Camera()
{
	shader = nullptr;
	delete width;
	delete height;
	window = nullptr;
}

Camera & Camera::operator=(const Camera & other)
{
	width = new int;
	height = new int;

	position = other.position;
	forward = other.forward;
	up = other.forward;

	window = other.window;
	*width = *other.width;
	*height = *other.height;
	lastX = *width / 2;
	lastY = *height / 2;

	shader = other.shader;
	modelToWorld = other.modelToWorld;
	return *this;
}

void Camera::Update() {
	//Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += forward * speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= forward * speed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= cross(forward, up) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += cross(forward, up) * speed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) position -= up * speed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) position += up * speed;

	//Rotation
	vec3 rotation = glm::identity<vec3>();
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotation.y += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotation.y -= 0.01f;
	modelToWorld = glm::rotate(glm::identity<glm::mat4>(), rotation.y, glm::vec3(0, 1, 0));

	//Viewport setup

	glm::mat4 view = glm::lookAtLH(position, position + forward, up);
	glm::mat4 projection = glm::perspectiveFovLH<GLfloat>(glm::pi<float>() / 3.0f, (float)*width, (float)*height, 0.01f, 100.f);

	//Viewport calculations
	glUseProgram(*shader);//get location of the view matrix in the shader

	GLuint viewMatLoc = glGetUniformLocation(*shader, "viewMatrix");
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, &(view[0][0]));
	GLuint projectionMatLoc = glGetUniformLocation(*shader, "projectionMatrix");
	glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, &(projection[0][0]));
	GLuint modelToWorldLoc = glGetUniformLocation(*shader, "modelToWorld");
	glUniformMatrix4fv(modelToWorldLoc, 1, GL_FALSE, &(modelToWorld[0][0]));
}

void Camera::mouseMove(GLFWwindow * window, double xpos, double ypos)
{
	float xOffset = xpos - lastX;
	float yOffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;
}