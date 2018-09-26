#include "shader.h"

///Based on the tutorial made in ATLAS.

#pragma region variables
//Window data
const GLint WIDTH = 640, HEIGHT = 320;
GLuint vao;
GLuint vbo;
GLuint colorbuffer;

//Cube data
const GLfloat VERTICES = 36;
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
};
#pragma endregion

int main() {
	//Initializes the GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		std::cin.get();
		_CrtDumpMemoryLeaks();
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//GLFW creation
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "A Cube", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);

	//GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	//Shaders
	GLuint shaderProgram = glCreateProgram();
	//Vertex Shader
	Shader *vs = new Shader();
	vs->InitFromFile("shaders/vertexShader.glsl", GL_VERTEX_SHADER);
	glAttachShader(shaderProgram, vs->GetShaderLoc());
	//Fragment Shader
	Shader *fs = new Shader();
	fs->InitFromFile("shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);
	glAttachShader(shaderProgram, fs->GetShaderLoc());

	glLinkProgram(shaderProgram);

	//Vertex setup
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint attribIndex = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(attribIndex, VERTICES, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(attribIndex);
	
	//cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	delete fs;
	delete vs;
	
	while (!glfwWindowShouldClose(window)) //Draw loop
	{
		//Gets input
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break; //Exit command

		//Clears the buffer
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.25f, 0.7f, 0.6f, 1.0f);

		//Draws and shade
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, VERTICES);

		//'clear' for next draw call
		//glDisableVertexAttribArray(attribIndex);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}
	//Cleanup
	glDeleteBuffers(1, &vbo);
	glfwTerminate();
	return EXIT_SUCCESS;
}