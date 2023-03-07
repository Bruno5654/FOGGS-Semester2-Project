#include "HelloGL.h"

Vertex HelloGL::vertices[] = {1,1,1, -1,1,1 -1,-1,1, //v0-v1-v2 (front)
							-1,-1,1, 1,-1,1, 1,1,1, //v2-v3-v0
							1,1,1, 1,-1,1, 1,-1,-1, //v0-v3-v4 (right)
							1,-1,1, 1,1,-1, 1,1,1, //v4-v5-v0
							1,1,1, 1,1,-1, -1,1,-1, //v0-v5-v6 (top)
							-1,1,-1, -1,1,1, 1,1,1, //v6-v1-v0
							-1,1,1, -1,1,-1, -1,-1,-1, //v1-v6-v7 (left)
							-1,-1,-1, -1,-1,1, -1,1,1, //v7-v2-v1
							-1,-1,-1, 1,-1,-1, 1,-1,1, //v7-v4-v3 (bottom)
							1,-1,1, -1,-1,1, -1,-1,-1, //v3-v2-v7
							1,-1,-1, -1,-1,-1, -1,1,-1, //v4-v7-v6 (back)
							-1,1,-1, 1,1,-1, 1,-1,-1}; //v3-v2-v7

Color HelloGL::colors[] = { 1,1,1, 1,1,0 - 1,0,0, //v0-v1-v2 (front)
							1,0,0, 1,0,1, 1,1,1, //v2-v3-v0
							1,1,1, 1,0,1, 0,0,1, //v0-v3-v4 (right)
							1,0,0, 1,0,1, 0,0,1, //v4-v5-v0
							1,1,1, 1,0,1, 0,0,1, //v0-v5-v6 (top)
							0,1,0, 1,1,0, 1,1,1, //v6-v1-v0
							1,1,0, 0,1,0, 0,0,0, //v1-v6-v7 (left)
							0,0,0, 1,0,0, 1,1,0, //v7-v2-v1
							0,0,0, 0,0,1, 1,0,1, //v7-v4-v3 (bottom)
							1,0,1, 1,0,0, 0,0,0, //v3-v2-v7
							0,0,1, 0,0,0, 0,1,0, //v4-v7-v6 (back)
							0,1,0, 0,1,1, 0,0,1 }; //v3-v2-v7

Vertex HelloGL::indexedVertices[] = { 1,1,1, -1,1,1, //v0,v1,
									-1,-1,1, 1,-1,1, //v2,v3
									-1,1,-1, -1,-1,-1 };//v6,v7

Color HelloGL::indexedColors[] = { 1,1,1, 1,1,0, //v0,v1,
									1,0,0, 1,0,1, //v2,v3
									0,0,1, 0,1,1,
									0,1,0, 0,0,0};//v6,v7

GLushort HelloGL::indices[] = { 0,1,2, 2,3,0, //front
							   0,3,4, 4,5,0, //right
							   0,5,6, 6,1,0, //top
							   1,6,7, 7,2,1, //left
							   7,4,3, 3,2,7, //bottom
							   4,7,6, 6,5,4 }; //back

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
	//camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 1.0f;

	glutDisplayFunc(GLUTCallbacks::Display);
	glMatrixMode(GL_PROJECTION); //Swap to projection.
	glLoadIdentity();
	//Set the viewport to be the entire window.
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000); //FOV, Aspect ratio, Near clipping, Far clipping.
	glMatrixMode(GL_MODELVIEW); //Swap back to content.
	glEnable(GL_CULL_FACE); //Enable culling.
	glCullFace(GL_BACK);//Cull the back faces.
	
	glutMainLoop();
	
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //this clears the scene

	//DrawPolygon();
	//DrawTeapot();
	//DrawTriangle(-0.25f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f);
	//DrawTriangle(0.25f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f);
	//DrawTriangle(0.0f, 0.5f, -0.25f, 0.0f, 0.25f, 0.0f);
	DrawCubeArray();

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

void HelloGL::DrawCube()
{
	glBegin(GL_TRIANGLES);
	//Face v0-v1-v2
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	//Face v2-v3-v0
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	//Face v0-v3-v4
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	//Face v4-v5-v0
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	//Face v0-v5-v6
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	//Face v6-v1-v0
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	//Face v1-v6-v7
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	//Face v7-v2-v1
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	//Face v7-v4-v3
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	//Face v3-v2-v7
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	//Face v4-v7-v6
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	//Face v6-v5-v4
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);

	glEnd();
}

void HelloGL::DrawCubeArray()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		//glColor3f(colors[i].r, colors[i].g, colors[i].b);
		//glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		glColor3fv(&colors[i].r);
		glVertex3fv(&vertices[i].x);
	}
	glEnd();

	glPopMatrix();
}

void HelloGL::DrawIndexedCube()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glColor3fv(&indexedColors[indices[i]].r);
		glVertex3fv(&indexedVertices[indices[i]].x);
	}
	glEnd();

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


