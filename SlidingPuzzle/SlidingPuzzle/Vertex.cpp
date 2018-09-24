#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex(int value) {
	number = value;
	visited = -3;
}

Vertex::~Vertex()
{
}

//Copy constructor
Vertex::Vertex(const Vertex& other)
{
	if (this != &other) {
		number = other.number;
		visited = other.visited;
	}
}
//Copy assignment
Vertex& Vertex::operator= (const Vertex& other)
{
	if (this != &other) {
		number = other.number;
		visited = other.visited;
	}
	return *this;
}
