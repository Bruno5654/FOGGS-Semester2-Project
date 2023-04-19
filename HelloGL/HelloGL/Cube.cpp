#include "Cube.h"
#include <fstream>
#include <iostream>

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;


Cube::Cube(Mesh* mesh, float x, float y, float z)
{
	_mesh = mesh;
	
	_position.x = x;
	_position.y = y;
	_position.z = z;
	
	_rotation = 0;
	_direction = 0;
	_speed = 1;
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr)
	{
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		switch (_direction)
		{
		case 0:
			glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
			break;
		case 1:
			glRotatef(_rotation, 0.0f, 1.0f, 0.0f);
			break;
		case 2:
			glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
			break;

		}


		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 36; i++)
		{
			glColor3fv(&_mesh->Colors[_mesh->Indices[i]].r);
			glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
		}
		glEnd();

		glPopMatrix();
	}
}

void Cube::Update()
{
	_rotation += _speed;

	if (_rotation >= 360.0f)
		_rotation = 0.0f;
}

Cube::~Cube()
{

}