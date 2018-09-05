#include "Main.h"

///Based on the tutorial made in ATLAS.

const GLint WIDTH = 640, HEIGHT = 320;

int main() {
	//Initializes the GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Compatibility - forwards, but not backwards
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Window resizability
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//GLFW creation
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Create Window Tutorial", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	//GLEW
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(.25f, 0.7f, 0.6f, 1.0f);
	
	while (!glfwWindowShouldClose(window)) //Draw loop
	{
		// Checking for events/inputs
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw OpenGL stuff

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}