#pragma once
#include "GLUTCallbacks.h"
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h"
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

		void InitObjects();
		void InitLighting();
	
		void InitGL(int argc, char* argv[]);
		void Keyboard(unsigned char key, int x, int y);
	
	private:
		//
		Camera* camera;
		SceneObject* objects[1000];
		Vector4* _lightPosition;
		Lighting* _lightData;

};


