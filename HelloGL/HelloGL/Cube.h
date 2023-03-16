#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
private:
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;
	static int numVertices, numColors, numIndices;

	Vector3 _position;



public:
	Cube(float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	static bool Load(char* path);

	GLfloat _rotation;
	int _direction;
	float _speed;
};
