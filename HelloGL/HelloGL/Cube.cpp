#include "Cube.h"
#include <fstream>
#include <iostream>

Vertex* Cube::indexedVertices = nullptr;
Color* Cube::indexedColors = nullptr;
GLushort* Cube::indices   = nullptr;

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;


Cube::Cube(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	
	_rotation = 0;
	_direction = 0;
	_speed = 1;
}

void Cube::Draw()
{
	if (indexedVertices != nullptr && indexedColors != nullptr && indices != nullptr)
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
			glColor3fv(&indexedColors[indices[i]].r);
			glVertex3fv(&indexedVertices[indices[i]].x);
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

bool Cube::Load(char* path) 
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file " << path << std::endl;
		return false;
	}
	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		inFile >> indexedVertices[i].x;
		inFile >> indexedVertices[i].y;
		inFile >> indexedVertices[i].z;
	}
	
	inFile >> numColors;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++)
	{
		inFile >> indexedColors[i].r;
		inFile >> indexedColors[i].g;
		inFile >> indexedColors[i].b;
	}

	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		inFile >> indices[i].r;
		inFile >> indices[i].g;
		inFile >> indices[i].b;
	}
	
	inFile.close();
	return true;
}

Cube::~Cube()
{

}