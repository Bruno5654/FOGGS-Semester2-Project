#pragma once
#include "Structures.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
	private:
		static Vertex* indexedVertices;
		static Color* indexedColors;
		static GLushort* indices;
		static int numVertices, numColors, numIndices;

		Vector3 _position;

	public:
		Pyramid(Mesh* mesh, float x, float y, float z);
		~Pyramid();

		void Draw();
		void Update();

		GLfloat _rotation;
		int _direction;
		float _speed;
};

