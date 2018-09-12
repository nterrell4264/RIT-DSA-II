#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex(int index, int value) {
	position = index;
	number = value;
	adjacencies = new bool[4]{ false, false, false, false };
}

Vertex::~Vertex()
{
	delete[] adjacencies;
}

void Vertex::AddAdjacency(int dir) {
	adjacencies[dir] = true;
}
