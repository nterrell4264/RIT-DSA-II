#include "Main.h"

///Based on the tutorial made in ATLAS.

const GLint WIDTH = 640, HEIGHT = 320;
GLuint vbo;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main() {
	//Initializes the GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//GLFW creation
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Create Window Tutorial", nullptr, nullptr); glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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
	glewInit();

	//Triangle
	float vertices[] = {
		-.5, -.5,
		.5, .5,
		.5, -.5 };

	//Binds things
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	while (!glfwWindowShouldClose(window)) //Draw loop
	{//Clears the screen
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.25f, 0.7f, 0.6f, 1.0f);

		//Binds things
		GLuint vertexAttribArrayIndex = 0;
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(vertexAttribArrayIndex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(sizeof(float) * 0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(vertexAttribArrayIndex);

		//Draws and displays the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(vertexAttribArrayIndex);
		glfwSwapBuffers(window);
		//Gets input
		glfwPollEvents();
	}
	//Cleanup
	glDeleteBuffers(1, &vbo);
	glfwTerminate();
	return EXIT_SUCCESS;
}