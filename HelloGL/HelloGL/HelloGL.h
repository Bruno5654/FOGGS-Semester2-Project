#pragma once
#include <Windows.h> //Requried for OpenGL on windows.
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"

class HelloGL
{
	public:
	//constructor def
	HelloGL(int argc, char* argv[]);
	//destructor
	~HelloGL(void);

	void Display();
	void DrawPolygon();
	void DrawTriangle(float vert1x, float vert1y, float vert2x, float vert2y, float vert3x, float vert3y);
};


