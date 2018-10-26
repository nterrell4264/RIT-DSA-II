#include "Shape.h"

Shape::Shape(float xPos, float yPos, float zPos)
{
	x = xPos;
	y = yPos;
	z = zPos;
}
Shape::~Shape()
{
	glDeleteBuffers(1, &vbo);
}

void Shape::SetVertices(GLfloat triNum, GLfloat points[])
{
	triCount = triNum;
	coordCount = triNum * 9;
	pointData = vector<GLfloat>(coordCount);
	memcpy(&(pointData[0]), points, coordCount * sizeof(GLfloat));
}
void Shape::Translate(float dx, float dy, float dz) {
	x += dx;
	y += dy;
	z += dz;
	for (int i = 0; i < coordCount; i += 3) { //Loops through every vertex
		pointData[i] += x;
		pointData[i + 1] += y;
		pointData[i + 2] += z;
	}

}

void Shape::InitializeGL(GLuint shader) {
	///Initializes vertex objects
	//VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * coordCount, &(pointData[0]), GL_STATIC_DRAW);
	//Shader
	GLuint attribIndex = glGetAttribLocation(shader, "position");
	glVertexAttribPointer(attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	glEnableVertexAttribArray(attribIndex);

	//cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Shape::Render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, triCount * 3);
	//glBindVertexArray(0);
}
