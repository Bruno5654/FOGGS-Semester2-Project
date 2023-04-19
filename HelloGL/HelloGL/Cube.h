#pragma once
#include "Structures.h"

class Cube
{
private:
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;
	static int numVertices, numColors, numIndices;

	Vector3 _position;
	Mesh* _mesh;


public:
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

	GLfloat _rotation;
	int _direction;
	float _speed;
};
