#include "Spinner.h"

Spinner::Spinner(Shape** shapes, int shapeCount)
{
	objects = new tuple<Shape*,bool>**[11];
	for (int i = -5; i <= 5; i++) {
		objects[i+5] = new tuple<Shape*,bool>*[7];
		for (int j = -3; j <= 3; j++) {
			objects[i+5][j+3] = new tuple<Shape*, bool>[11];
			for (int k = -5; k <= 5; k++) {
				for (int s = 0; s < shapeCount; s++) {
					tuple<Shape*, bool> shape = make_tuple(shapes[s],false); //Code is broken: the tuple disappears once it leaves scope, but there's no way to make a tuple*
					if (get<0>(shape)->position.x == i && get<0>(shape)->position.y == j && get<0>(shape)->position.z == k)
						objects[i + 5][j + 3][k + 5] = shape;
					else objects[i + 5][j + 3][k + 5] = make_tuple(nullptr,false);
				}
			}
		}
	}
	starter = shapes[0];
}

Spinner::Spinner() { //not intended for use - compiler wants it for some reason

}

Spinner::~Spinner()
{
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 7; j++) {
			delete[] objects[i][j];
		}
		delete[] objects[i];
	}
	delete[] objects;
}

void Spinner::StartSpin() {
	SpinOut(starter->position.x, starter->position.y, starter->position.z);
}

void Spinner::StopSpin(Shape** shapes, int shapeCount) {
	for (int i = 0; i < shapeCount; i++) shapes[i]->Reset();
}

void Spinner::SpinOff(Shape** shapes, int shapeCount) {
	for (int i = 0; i < shapeCount; i++) {
		shapes[i]->spinning = true;
	}
}
void Spinner::SpinOut(int x, int y, int z) {
	if (abs(x) <= 5 && abs(y) <= 3 && abs(z) <= 5) {
		tuple<Shape*,bool> shape = objects[x + 5][y + 3][z + 5];
		if (get<1>(shape)) { //If grid location has not been visited
			if (get<0>(shape) != nullptr && !get<0>(shape)->spinning) { //If non-spinning ring is at this location
				get<0>(shape)->spinning = true;
				get<1>(shape) = true;
				//Recursively checks neighbors
				SpinOut(x + 1, y, z);
				SpinOut(x - 1, y, z);
				SpinOut(x, y + 1, z);
				SpinOut(x, y - 1, z);
				SpinOut(x, y, z + 1);
				SpinOut(x, y, z - 1);
			}
		}
	}
}
