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
Shape* cylinder;
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
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::mat4 modelToWorld = glm::identity<glm::mat4>();
	#pragma endregion

	#pragma region Cylinder
	cylinder = new Shape();
	const float originX = 0.f;
	const float originY = 0.f;
	const float z1 = -.5f;
	const float z2 = .5f;
	const int parts = 30;
	GLfloat cylinderVertices[parts * 36];
	//End 1
	for (int i = 0; i < parts; i++) {
		cylinderVertices[i * 9] = originX;
		cylinderVertices[i * 9 + 1] = originY;
		cylinderVertices[i * 9 + 2] = z1;
		cylinderVertices[i * 9 + 3] = cos(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 4] = sin(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 5] = z1;
		cylinderVertices[i * 9 + 6] = cos((i+1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 7] = sin((i+1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 8] = z1;
	}
	//End 2
	for (int i = 0; i < parts; i++) {
		cylinderVertices[i * 9 + parts * 9] = originX;
		cylinderVertices[i * 9 + 1 + parts * 9] = originY;
		cylinderVertices[i * 9 + 2 + parts * 9] = z2;
		cylinderVertices[i * 9 + 3 + parts * 9] = cos(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 4 + parts * 9] = sin(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 5 + parts * 9] = z2;
		cylinderVertices[i * 9 + 6 + parts * 9] = cos((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 7 + parts * 9] = sin((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 9 + 8 + parts * 9] = z2;
	}
	//Tube
	for (int i = 0; i < parts; i++) {
		//Triangle between two faces on z-level 0 and one on z-level 1.
		cylinderVertices[i * 18 + parts * 18] = cos(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 1 + parts * 18] = sin(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 2 + parts * 18] = z1;
		cylinderVertices[i * 18 + 3 + parts * 18] = cos((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 4 + parts * 18] = sin((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 5 + parts * 18] = z1;
		cylinderVertices[i * 18 + 6 + parts * 18] = cos(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 7 + parts * 18] = sin(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 8 + parts * 18] = z2;
		//Triangle between two faces on z-level 1 and one on z-level 0.
		cylinderVertices[i * 18 + 9 + parts * 18] = cos(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 10 + parts * 18] = sin(i * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 11 + parts * 18] = z2;
		cylinderVertices[i * 18 + 12 + parts * 18] = cos((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 13 + parts * 18] = sin((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 14 + parts * 18] = z2;
		cylinderVertices[i * 18 + 15 + parts * 18] = cos((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 16 + parts * 18] = sin((i + 1) * 2 * 3.14159f / parts) / 4;
		cylinderVertices[i * 18 + 17 + parts * 18] = z1;
	}
	cylinder->SetVertices(parts * 4, cylinderVertices);
	cylinder->InitializeGL(shaderProgram);
	#pragma endregion
	while (!glfwWindowShouldClose(window)) //Draw loop
	{
		//Gets input
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break; //Exit command

		//Rotates scene
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotation.y += 0.01f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotation.y -= 0.01f;
		modelToWorld = glm::rotate(glm::identity<glm::mat4>(), rotation.y, glm::vec3(0, 1, 0));

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
		cylinder->Render();

		//'clear' for next draw call
		//glDisableVertexAttribArray(attribIndex);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}
	//Cleanup
	glfwTerminate();
	delete cylinder;
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}