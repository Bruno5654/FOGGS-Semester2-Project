#pragma once
#include "Structures.h"
#include "SceneObject.h"


class Cube : public SceneObject
{
private:
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;
	static int numVertices, numColors, numIndices;

	Vector3 _position;


public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

	GLfloat _rotation;
	int _direction;
	float _speed;
};
