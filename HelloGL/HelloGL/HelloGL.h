#pragma once
#include <Windows.h> //Requried for OpenGL on windows.
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#define REFRESHRATE 16

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};



class HelloGL
{
	public:
		//constructor def
		HelloGL(int argc, char* argv[]);
		//destructor
		~HelloGL(void);

		void Display();
		void Update();

		void DrawPolygon();
		void DrawTeapot();
		void DrawTriangle(float vert1x, float vert1y, float vert2x, float vert2y, float vert3x, float vert3y);

		void Keyboard(unsigned char key, int x, int y);
	
	private:
		//
		Camera* camera;
		float rotation;
		float rotationKey;
	
};


