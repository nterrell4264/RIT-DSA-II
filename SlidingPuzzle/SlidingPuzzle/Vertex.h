#pragma once
class Vertex
{
public:
	Vertex(int index, int value);
	~Vertex();

	//Variables
	int position;
	int number;
	int visited; //Tracks which move number it was last visited
};

