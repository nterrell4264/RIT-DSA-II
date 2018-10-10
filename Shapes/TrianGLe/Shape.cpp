#include "Shape.h"

Shape::Shape()
{
	///Initializes vertex objects
	//VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointData), pointData, GL_STATIC_DRAW);
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Shape::~Shape()
{
	delete[] pointData;
}

void Shape::SetVertices(GLfloat triNum, GLfloat* points)
{
	triCount = triNum;
	vertexCount = triNum * 3;
	pointData = points;
}
void Shape::Translate(float x, float y, float z) {
	for (int i = 0; i < vertexCount; i += 3) { //Loops through every vertex
		pointData[i] += x;
		pointData[i + 1] += y;
		pointData[i + 2] += z;
	}
}

void Shape::SetRender(GLuint* shader)
{
	shaderProgram = shader;
}

void Shape::Render() {
	//Draws
	glUseProgram(*shaderProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	//Releases
	glBindVertexArray(0);
	glUseProgram(0);
}
