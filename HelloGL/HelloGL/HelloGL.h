#pragma once
#include <Windows.h> //Requried for OpenGL on windows.
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Cube.h"
#define REFRESHRATE 16

class HelloGL
{
	public:
		//constructor def
		HelloGL(int argc, char* argv[]);
		//destructor
		~HelloGL(void);

		void Display();
		void Update();

		void Keyboard(unsigned char key, int x, int y);
	
	private:
		//
		Camera* camera;
		Cube* cube[200];

};


