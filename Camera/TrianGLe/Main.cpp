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
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Moveable Camera", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, &mouseWrapper);

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

	//Cameras
	cameras = new Camera*[3];
	cameras[0] = new Camera(&shaderProgram, window);
	cameras[1] = new Camera(&shaderProgram, window, vec3(10.f,5.f,0.f));
	cameras[2] = new Camera(&shaderProgram, window, vec3(0.f,-5.f,0.f));
	mainCamera = cameras[0];
	#pragma endregion

	#pragma region Shapes
	rings = new Shape*[ringCount]();
	rings[0] = MakeRing(0.f, 0.f, 0.f, .5f, .1f, shaderProgram);
	for(int i = 1; i < ringCount; i++)
		rings[i] = MakeRing(rand() % 11 - 5, rand() % 7 - 3, rand() % 11 - 5, .5f, .1f, shaderProgram);
	#pragma endregion

	#pragma region Draw loop
	while (!glfwWindowShouldClose(window))//Draw loop
	{
		//General input
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break; //Exit command
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) { //Switch cameras
			if (!camKeyPressed) {
				camIndex = (camIndex + 1) % 3;
				mainCamera = cameras[camIndex];
			}
			camKeyPressed = true;
		}
		else {
			camKeyPressed = false;
		}

		//Camera input/recalculation
		mainCamera->Update();

		//Clears the buffer
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.25f, 0.7f, 0.6f, 1.0f);

		//Mesh function
		for (int i = 0; i < 8; i++) {
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
	//delete ringMesh;

	delete[] cameras;
	mainCamera = nullptr;

	delete vs;
	delete fs;
	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
	#pragma endregion
}

Shape* MakeRing(float originX, float originY, float originZ, float ringRadius, float ringWidth, GLuint shader) {
	Shape* ring = new Shape(originX, originY, originZ);
	//if (ringMesh == nullptr) { //Creates one mesh (pun not intended) for all rings
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
	//}
	return ring;
}

void mouseWrapper(GLFWwindow * window, double xpos, double ypos)
{
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) mainCamera->mouseMove(xpos, ypos);
}
