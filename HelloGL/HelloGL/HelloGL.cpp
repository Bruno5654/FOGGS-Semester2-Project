#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Simple OpenGL Program");
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene
	DrawPolygon();
	DrawTriangle(-0.25, 0.0, -0.5, -0.5, 0.0, -0.5);
	DrawTriangle(0.25, 0.0, 0.0, -0.5, 0.5, -0.5);
	DrawTriangle(0.0, 0.5, -0.25, 0.0, 0.25, 0.0);
	glFlush(); //flushes the scene drawn to the graphics card
}

void HelloGL::Update()
{
	glutPostRedisplay(); //Causes the scene to redraw itself after update has finished.
}

void HelloGL::DrawPolygon()
{
	glBegin(GL_POLYGON); //starts to draw a polygon
	{
		glColor4f(0.0f, 0.75f, 0.25f, 0.0f);
		glVertex2f(-0.75, 0.6); //define the first point of the polygon,top left
		glVertex2f(0.75, 0.6); //next point, top right
		glVertex2f(0.75, -0.6); //bottom right
		glVertex2f(-0.75, -0.6); //last point of the polygon, bottom left
		glEnd(); // defines the end of the draw
	}
}

void HelloGL::DrawTriangle(float vert1x, float vert1y, float vert2x, float vert2y, float vert3x, float vert3y)
{
	glBegin(GL_POLYGON); //starts to draw a polygon
	{
		glColor4f(1.0f, 1.0f, 0.5f, 0.0f);
		glVertex2f(vert1x, vert1y); 
		glVertex2f(vert2x, vert2y); 
		glVertex2f(vert3x, vert3y); 
		glEnd(); 
	}
}

HelloGL::~HelloGL(void)
{

}


