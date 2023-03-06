#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); //Turn on double buffering.
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(520, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	
	rotation = 0.0f;
	rotationKey = 0.0f;

	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 1.0f;

	glutDisplayFunc(GLUTCallbacks::Display);
	glMatrixMode(GL_PROJECTION); //Swap to projection.
	glLoadIdentity();
	//Set the viewport to be the entire window.
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000); //FOV, Aspect ratio, Near clipping, Far clipping.
	glMatrixMode(GL_MODELVIEW); //Swap back to content.
	glutMainLoop();
	
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene

	//DrawPolygon();
	DrawTeapot();
	//DrawTriangle(-0.25f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f);
	//DrawTriangle(0.25f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f);
	//DrawTriangle(0.0f, 0.5f, -0.25f, 0.0f, 0.25f, 0.0f);

	glFlush(); //flushes the scene drawn to the graphics card

	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();

	//Camera Movement


	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);


	glutPostRedisplay(); //Causes the scene to redraw itself after update has finished.

	rotation += 0.5f;
	if (rotation >= 360.0f)
		rotation = 0.0f;
	
	if (rotationKey >= 360.0f)
		rotationKey = 0.0f;
	
	if (rotationKey < 0.0f)
		rotationKey = 360.0f;
}

void HelloGL::DrawPolygon()
{
	glPushMatrix();
	//glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rotationKey, 0.0f, 0.0f, -1.0f);
	glBegin(GL_POLYGON); //starts to draw a polygon
	{
		glColor4f(0.0f, 0.75f, 0.25f, 0.0f);
		glVertex2f(-0.75f, 0.6f); //define the first point of the polygon,top left
		glVertex2f(0.75f, 0.6f); //next point, top right
		glVertex2f(0.75f, -0.6f); //bottom right
		glVertex2f(-0.75f, -0.6f); //last point of the polygon, bottom left
		glEnd(); // defines the end of the draw
	}
	glPopMatrix();
}

void HelloGL::DrawTeapot()
{
	glPushMatrix();
	//glTranslatef(0.0f, 0.0f, -5.0f);
	//glRotatef(rotationKey, 0.0f, 0.0f, -1.0f);
	glutWireTeapot(0.1);
	glPopMatrix();
}

void HelloGL::DrawTriangle(float vert1x, float vert1y, float vert2x, float vert2y, float vert3x, float vert3y)
{
	glPushMatrix();
	glRotatef(rotation, 0.0f, -1.0f, 0.0f);
	glBegin(GL_POLYGON); //starts to draw a polygon
	{
		glColor4f(1.0f, 1.0f, 0.5f, 0.0f);
		glVertex2f(vert1x, vert1y); 
		glVertex2f(vert2x, vert2y); 
		glVertex2f(vert3x, vert3y); 
		glEnd(); 
	}
	glPopMatrix();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{
		case 'd':
			rotationKey += 0.5f;
			camera->eye.x += 0.1f;
			break;
		case 'a':
			rotationKey -= 0.5f;
			camera->eye.x -= 0.1f;
			break;
		case 'w':
			camera->eye.y += 0.1f;
			break;
		case 's':
			camera->eye.y -= 0.1f;
			break;
		case '+':
			camera->eye.z += 0.1f;
			break;
		case '-':
			camera->eye.z -= 0.1f;
			break;
		default:
			break;
	}
}



HelloGL::~HelloGL(void)
{
	delete camera;
}


