#include "shader.h"
#include "Shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

///Based on the tutorial made in ATLAS.

#pragma region variables
//Window data
const GLint WIDTH = 800, HEIGHT = 600;
GLuint triVAO;
GLuint triVBO;
GLuint rectVAO;
GLuint rectVBO;
GLuint colorbuffer;

//Shape
//Shape* triangle;
GLfloat triVertices = 3;
static const GLfloat triangle_data[] = {
	0.0f, .5f, 0.0f,
	.433f, 0.0f, 0.0f,
	-.433f, 0.0f, 0.0f
};

GLfloat rectVertices = 4;
static const GLfloat rectangle_data[] = {
	-.75f, -.1f, 0.0f,
	-.75f, .1f, 0.0f,
	-.25f, .1f, 0.0f,
	-.75f, -.1f, 0.0f,
	-.25f, -.1f, 0.0f,
	-.25f, .1f, 0.0f
};
#pragma endregion

void SetupVertexObjects(GLuint vao, GLuint vbo) {
	//VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_data), rectangle_data, GL_STATIC_DRAW);
}

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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Moving Shapes", nullptr, nullptr);
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
	glm::mat4 modelToWorld = glm::identity<glm::mat4>();

	///Vertex setup
	//Triangle
	glGenVertexArrays(1, &triVAO);
	glBindVertexArray(triVAO);
	
	glGenBuffers(1, &triVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);
	//Rectangle
	glGenVertexArrays(1, &rectVAO);
	glBindVertexArray(rectVAO);

	glGenBuffers(1, &rectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_data), rectangle_data, GL_STATIC_DRAW);

	//Position
	GLuint attribIndex = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(attribIndex);

	//cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	delete fs;
	delete vs;

	//Initializes shapes
	/*triangle = new Shape();
	triangle->SetVertices(1, new GLfloat[9]{
		0.0f, .5f, 0.0f,
		.433f, 0.0f, 0.0f,
		-.433f, 0.0f, 0.0f
		});
	triangle->SetRender(&shaderProgram);*/
	
	while (!glfwWindowShouldClose(window)) //Draw loop
	{
		//Gets input
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break; //Exit command

		//Sets up camera matrices
		glm::mat4 view = glm::lookAtLH(glm::vec3(0.0f, 0.0f, -2.f), glm::vec3(0.0f, 0.0f, -1.f), glm::vec3(0.0f, 1.f, 0.0f));
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

		//glUseProgram(0);

		//Renders
		//triangle->Render();
		glBindVertexArray(triVAO);
		glDrawArrays(GL_TRIANGLES, 0, triVertices);
		glBindVertexArray(rectVAO);
		glDrawArrays(GL_TRIANGLES, 0, rectVertices);

		//'clear' for next draw call
		//glDisableVertexAttribArray(attribIndex);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}
	//Cleanup
	glDeleteBuffers(1, &triVBO);
	glDeleteBuffers(1, &rectVBO);
	glfwTerminate();
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}