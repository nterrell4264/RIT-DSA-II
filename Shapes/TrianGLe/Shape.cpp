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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexCount * 3, pointData, GL_STATIC_DRAW);

	//cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Shape::~Shape()
{
	glDeleteBuffers(1, &vbo);
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

void Shape::SetShader(GLuint shader) {
	GLuint attribIndex = glGetAttribLocation(shader, "position");
	glVertexAttribPointer(attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(attribIndex);
}
void Shape::Render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	//glBindVertexArray(0);
}
