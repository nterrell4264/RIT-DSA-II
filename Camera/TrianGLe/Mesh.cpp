#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
}

void Mesh::Render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, triCount * 3);
	//glBindVertexArray(0);
}
void Mesh::Update() {
}

void Mesh::SetVertices(GLfloat triNum, GLfloat points[])
{
	triCount = triNum;
	coordCount = triNum * 9;
	pointData = vector<GLfloat>(coordCount);
	memcpy(&(pointData[0]), points, coordCount * sizeof(GLfloat));
}

void Mesh::InitializeGL(GLuint shader) {
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
