#include "shader.h"
#include "Shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

///Based on the tutorial made in ATLAS.

#pragma region variables
//Window data
const GLint WIDTH = 800, HEIGHT = 600;
GLuint colorbuffer;

//Shape
Shape* triangle;
Shape* rectangle;
Shape* circle;
#pragma endregion

int main() {
	#pragma region GL Stuff
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
	#pragma endregion
	#pragma region Shapes
	//Triangle
	triangle = new Shape();
	triangle->SetVertices(1, new GLfloat[9]{
		0.0f, .5f, 0.0f,
		.433f, 0.0f, 0.0f,
		-.433f, 0.0f, 0.0f
		});
	triangle->InitializeGL(shaderProgram);
	//Rectangle
	rectangle = new Shape();
	rectangle->SetVertices(2, new GLfloat[18]{
		-1.f, -.2f, 0.0f,
		-1.f, .2f, 0.0f,
		-.5f, .2f, 0.0f,
		-1.f, -.2f, 0.0f,
		-.5f, -.2f, 0.0f,
		-.5f, .2f, 0.0f
		});
	rectangle->InitializeGL(shaderProgram);
	//Circle
	circle = new Shape();
	const int parts = 90;
	GLfloat circleVertices[parts * 9];
	for (int i = 0; i < parts; i++) { //Creates 90 triangles around in a circle
		circleVertices[i * 9] = .5f;
		circleVertices[i * 9 + 1] = -.5f;
		circleVertices[i * 9 + 2] = 0.f;
		circleVertices[i * 9 + 3] = .5f + cos(i * 2 * 3.14159f / parts) / 4;
		circleVertices[i * 9 + 4] = -.5f + sin(i * 2 * 3.14159f / parts) / 4;
		circleVertices[i * 9 + 5] = 0.f;
		circleVertices[i * 9 + 6] = .5f + cos((i+1) * 2 * 3.14159f / parts) / 4;
		circleVertices[i * 9 + 7] = -.5f + sin((i+1) * 2 * 3.14159f / parts) / 4;
		circleVertices[i * 9 + 8] = 0.f;
	}
	circle->SetVertices(parts, circleVertices);
	circle->InitializeGL(shaderProgram);
	#pragma endregion
	while (!glfwWindowShouldClose(window)) //Draw loop
	{
		//Gets input
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break; //Exit command

		//Updates
		triangle->Translate(.01f, .01f);
		rectangle->Translate(.01f, .01f);
		circle->Translate(.01f, .01f);

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

		//Renders
		triangle->Render();
		rectangle->Render();
		circle->Render();

		//'clear' for next draw call
		//glDisableVertexAttribArray(attribIndex);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}
	//Cleanup
	glfwTerminate();
	delete triangle;
	delete rectangle;
	delete circle;
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}