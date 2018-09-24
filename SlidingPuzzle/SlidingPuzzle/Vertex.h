#pragma once
class Vertex
{
public:
	Vertex(int value);
	~Vertex();
	Vertex(const Vertex& other);
	Vertex& operator= (const Vertex& other); //Copy constructor

	//Variables
	int number;
	int visited; //Tracks which move number it was last visited
};

