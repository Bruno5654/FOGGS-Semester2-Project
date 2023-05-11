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
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr)
	{
		//glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 36; i++)
		{
			//glTexCoord2fv(&_mesh->TexCoords[_mesh->Indices[i]].u);
			glColor3fv(&_mesh->Colors[_mesh->Indices[i]].r);
			glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
		}

		std::cout << "Drawn Pyramid." << std::endl;

		//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnd();

		glPopMatrix();
	}
}

void Pyramid::Update()
{

}
