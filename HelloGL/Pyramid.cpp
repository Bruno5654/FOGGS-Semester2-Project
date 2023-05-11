#include "Pyramid.h"
#include <iostream>

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	
	_rotation = 0;
	_direction = 0;
	_speed = 1;
}

Pyramid::~Pyramid()
{
}

void Pyramid::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 36; i++)
		{
			//glColor3fv(&_mesh->Colors[_mesh->Indices[i]].r);
			glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
		}

		glEnd();

		glPopMatrix();
	}
}

void Pyramid::Update()
{

}
