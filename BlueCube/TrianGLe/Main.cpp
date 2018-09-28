#include "shader.h"\

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		glfwTerminate();
		std::cin.get();
		_CrtDumpMemoryLeaks();
		return EXIT_FAILURE;
	}

	///Shaders
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

	//GLM definitions
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::mat4 modelToWorld = glm::identity<glm::mat4>();

	///Vertex setup
	//VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	//
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

		//Rotates cube
		rotation.y += 0.001f;
		modelToWorld = glm::rotate(glm::identity<glm::mat4>(), rotation.y, glm::vec3(0, 1, 0));

		//Sets up camera matrices
		glm::mat4 view = glm::lookAtLH(glm::vec3(0.0f, 0.0f, -5.f), glm::vec3(0.0f, 0.0f, -4.f), glm::vec3(0.0f, 1.f, 0.0f));
		glm::mat4 projection = glm::perspectiveFovLH<GLfloat>(glm::pi<float>() / 3.0f, (float)WIDTH, (float)HEIGHT, 0.01f, 100.f);

		//Clears the buffer
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.25f, 0.7f, 0.6f, 1.0f);

		//Viewport calculations
		glUseProgram(shaderProgram);//get location of the view matrix in the shader

		GLuint viewMatLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
		glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, &(view[0][0]));
		GLuint projectionMatLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
		glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, &(projection[0][0]));
		GLuint modelToWorldLoc = glGetUniformLocation(shaderProgram, "modelToWorld");
		glUniformMatrix4fv(modelToWorldLoc, 1, GL_FALSE, &(modelToWorld[0][0]));

		//Renders
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
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}