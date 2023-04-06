#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); //Turn on double buffering.
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(520, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	
	Cube::Load((char*)"cube.txt");
	
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	camera = new Camera();
	for (int i = 0; i < 200; i++)
	{
		cube[i] = new Cube(((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
		cube[i]->_rotation = (rand() % 360);
		cube[i]->_direction = (rand() % 2);
		cube[i]->_speed = (rand() % 1 + 3);
	}


	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 5.0f;
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 1.0f;

	glutDisplayFunc(GLUTCallbacks::Display);
	glMatrixMode(GL_PROJECTION); //Swap to projection.
	glLoadIdentity();
	//Set the viewport to be the entire window.
	glViewport(0, 0, 1280, 720);
	gluPerspective(50, 1.25, 1, 1000); //FOV, Aspect ratio, Near clipping, Far clipping.
	glMatrixMode(GL_MODELVIEW); //Swap back to content.
	glEnable(GL_CULL_FACE); //Enable culling.
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);//Cull the back faces.
	
	glutMainLoop();
	
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //this clears the scene

	for (int i = 0; i < 200; i++)
	{
		cube[i]->Draw();
	}

	glFlush(); //flushes the scene drawn to the graphics card

	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();

	for (int i = 0; i < 200; i++)
	{
		cube[i]->Update();
	}

	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);


	glutPostRedisplay(); //Causes the scene to redraw itself after update has finished.
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		camera->eye.y = camera->eye.y - 0.1f;
	}
	else if (key == 's')
	{
		camera->eye.y = camera->eye.y + 0.1f;
	}

	if (key == 'a')
	{
		camera->eye.x = camera->eye.x + 0.1f;
	}
	else if (key == 'd')
	{
		camera->eye.x = camera->eye.x - 0.1f;
	}

	if (key == 'q')
	{
		camera->eye.z = camera->eye.z + 0.1f;
	}
	else if (key == 'e')
	{
		camera->eye.z = camera->eye.z - 0.1f;
	}
}

HelloGL::~HelloGL(void)
{
	delete camera;
	for (int i = 0; i < 200; i++)
	{
		delete cube[i];
	}
}


