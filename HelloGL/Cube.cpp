#include "Cube.h"
#include <fstream>
#include <iostream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh,texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	
	_texture = texture;

	_rotation = 0;
	_direction = rand() % 3;
	_speed = (rand() % 3) + 1;
}

void Cube::InitMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.0; _material->Ambient.y = 0.05; _material->Ambient.z = 0.4;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.4; _material->Diffuse.y = 0.5; _material->Diffuse.z = 0.5;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 0.04; _material->Specular.y = 0.7; _material->Specular.z = 0.7;
	_material->Specular.w = 1.0;
	_material->Shininess = 0.08;
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		
		InitMaterial();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

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
			glTexCoord2fv(&_mesh->TexCoords[_mesh->Indices[i]].u);
			glVertex3fv(&_mesh->Vertices[_mesh->Indices[i]].x);
		}

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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