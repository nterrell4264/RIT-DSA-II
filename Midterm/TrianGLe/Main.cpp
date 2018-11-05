#include "Main.h"

///Based on the tutorial made in ATLAS.

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

	#pragma region Shapes and Spinning
	rings = new Shape*[ringCount]();
	rings[0] = MakeRing(0.f, 0.f, 0.f, .5f, .1f, shaderProgram);
	for(int i = 1; i < ringCount; i++)
		rings[i] = MakeRing(rand() % 11 - 5, rand() % 7 - 3, rand() % 11 - 5, .5f, .1f, shaderProgram);

	spinner = Spinner(/*rings, ringCount*/); //object array is broken, this prevents data leaks
	#pragma endregion

	#pragma region Draw loop
	while (!glfwWindowShouldClose(window))//Draw loop
	{
		//General input
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break; //Exit command
		//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) spinner.StartSpin(); //Spin command
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) spinner.SpinOff(rings, ringCount); //Simple spin command
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) spinner.StopSpin(rings, ringCount); //Stop spin command

		//Scene rotation
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotation.y += 0.01f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotation.y -= 0.01f;
		modelToWorld = glm::rotate(glm::identity<glm::mat4>(), rotation.y, glm::vec3(0, 1, 0));

		//Sets up camera matrices
		glm::mat4 view = glm::lookAtLH(glm::vec3(0.f, 5.f, -10.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
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

		//Mesh function
		for (int i = 0; i < 8; i++) {
			rings[i]->Update();
			rings[i]->Render();
		}

		//'clear' for next draw call
		//glDisableVertexAttribArray(attribIndex);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}
	//Cleanup
	glfwTerminate();
	delete[] rings;
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
	#pragma endregion
}

Shape* MakeRing(float originX, float originY, float originZ, float ringRadius, float ringWidth, GLuint shader) {
	Shape* ring = new Shape(originX, originY, originZ);
	GLfloat ringVertices[parts * parts * 18];
	for (int i = 0; i < parts; i++) {
		for (int j = 0; j < parts; j++) {
			//Triangle between two faces on current angle and one on next angle.
			//Vertex 1: current point
			ringVertices[(i * parts + j) * 18] = originX + cos(i * 2 * 3.14159f / parts) * (ringRadius + cos(j * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 1] = originY + sin(i * 2 * 3.14159f / parts) * (ringRadius + cos(j * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 2] = originZ + sin(j * 2 * 3.14159f / parts) * ringWidth;
			//Vertex 2: equivalent point on next circle
			ringVertices[(i * parts + j) * 18 + 3] = originX + cos((i + 1) * 2 * 3.14159f / parts) * (ringRadius + cos(j * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 4] = originY + sin((i + 1) * 2 * 3.14159f / parts) * (ringRadius + cos(j * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 5] = originZ + sin(j * 2 * 3.14159f / parts) * ringWidth;
			//Vertex 3: next point on next circle
			ringVertices[(i * parts + j) * 18 + 6] = originX + cos((i + 1) * 2 * 3.14159f / parts) * (ringRadius + cos((j + 1) * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 7] = originY + sin((i + 1) * 2 * 3.14159f / parts) * (ringRadius + cos((j + 1) * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 8] = originZ + sin((j + 1) * 2 * 3.14159f / parts) * ringWidth;
			//Triangle between two faces on current angle and one on next angle.
			//Vertex 1: current point
			ringVertices[(i * parts + j) * 18 + 9] = originX + cos(i * 2 * 3.14159f / parts) * (ringRadius + cos(j * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 10] = originY + sin(i * 2 * 3.14159f / parts) * (ringRadius + cos(j * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 11] = originZ + sin(j * 2 * 3.14159f / parts) * ringWidth;
			//Vertex 2: next point on this circle
			ringVertices[(i * parts + j) * 18 + 12] = originX + cos(i * 2 * 3.14159f / parts) * (ringRadius + cos((j + 1) * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 13] = originY + sin(i * 2 * 3.14159f / parts) * (ringRadius + cos((j + 1) * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 14] = originZ + sin((j + 1) * 2 * 3.14159f / parts) * ringWidth;
			//Vertex 3: next point on next circle
			ringVertices[(i * parts + j) * 18 + 15] = originX + cos((i + 1) * 2 * 3.14159f / parts) * (ringRadius + cos((j + 1) * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 16] = originY + sin((i + 1) * 2 * 3.14159f / parts) * (ringRadius + cos((j + 1) * 2 * 3.14159f / parts) * ringWidth);
			ringVertices[(i * parts + j) * 18 + 17] = originZ + sin((j + 1) * 2 * 3.14159f / parts) * ringWidth;
		}
	}
	ring->SetVertices(parts * parts * 2, ringVertices);
	ring->InitializeGL(shader);
	return ring;
}