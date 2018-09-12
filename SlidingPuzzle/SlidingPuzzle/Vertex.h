#pragma once
class Vertex
{
public:
	Vertex(int index);
	~Vertex();

	//Variables
	int position;
	int number;
	bool* adjacencies;
	int visited; //Tracks which move number it was last visited

	//Functions
	void AddAdjacency(int dir);
};

