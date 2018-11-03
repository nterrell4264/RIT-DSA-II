#include "Shape.h"

Shape::Shape(float xPos, float yPos, float zPos)
{
	position = vec3(xPos, yPos, xPos);
	rotation = vec3(0);
	worldMatrix = glm::identity<mat4>();
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
	position += vec3(dx,dy,dz);
}
void Shape::Rotate(float rx, float ry, float rz)
{
	rotation += vec3(rx, ry, rz);
}
void Shape::Update() {
	if (spinning) Rotate(0, .005f, 0);
	worldMatrix = glm::identity<glm::mat4>();

	worldMatrix = translate(worldMatrix, position);
	worldMatrix = rotate(worldMatrix, rotation.x, glm::vec3(1.f, 0.f, 0.f));
	worldMatrix = rotate(worldMatrix, rotation.y, glm::vec3(0.f, 1.f, 0.f));
	worldMatrix = rotate(worldMatrix, rotation.z, glm::vec3(0.f, 0.f, 1.f));
}

void Shape::Reset() {
	rotation = vec3(0);
	spinning = false;
	worldMatrix = glm::identity<mat4>();
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
