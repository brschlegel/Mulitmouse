#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

#include <Windows.h>
#include <iostream>
#include "manymouse.h"
#include "Mouse.h"
#include <map>
#include <PolygonPhysicsObject.h>
#include <vector>
#include "Box.h"
#include "Color.h"
#include "Barrier.h"
#include "PhysicsWorld.h"

using namespace std;
// the window's width and height
int width, height;
Mouse m;
map<int, Mouse*> mice;
PhysicsWorld world = PhysicsWorld(b2Vec2(0, -10));

// tracking the game time - millisecond 
unsigned int curTime = 0;
unsigned int preTime = 0;


void init(void)
{
	std::cout << ManyMouse_Init();
	// initialize the size of the window
	width = 1600;
	height = 800;
	m = Mouse();
	
	world.AddRectBarrier(0, -5, 10, 1);
	world.AddBox(0, 4, 1, Color::getRed(), .5f,.5f);
	
}

// called when the GL context need to be rendered
void display(void)
{

	// clear the screen to white, which is the background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// clear the buffer stored for drawing
	glClear(GL_COLOR_BUFFER_BIT);


	// this is to define in which transformed space / coordinate system (in a matrix form) the objects will be drawn. 
	// (we'll learn matrix-based transformation in later classes.) 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Specify a color for the following object(s) that will be drawn 
	glColor3f(1.0, 0.0, 0.0); // The color is RGB, each color channel is defined in [0, 1].

	world.draw();

	//draw mice
	for (map<int, Mouse*>::iterator itr = mice.begin(); itr != mice.end(); ++itr)
	{
		itr->second->draw();
	}

	glutSwapBuffers(); // This example uses double framebuffers. This instructs the app that the current frame is finished and ready to display.
					   // The app then knows to swap it with the other buffer which was just displayed so that the display function can begin working on that buffer
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
	// update thescreen dimensions
	width = w;
	height = h;

	//do an orthographic parallel projection, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0 * (float(width) / float(height)), 5.0 * (float(width) / float(height)), -5.0, 5.0); // Define the size of the canvas left =-5, right =-5, bottom =-5, top=5,
									  // so the orgin is at the center of the canvas.  

	/* tell OpenGL to use the whole window for drawing */
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	
	glutPostRedisplay();
}

void update()
{
	curTime = glutGet(GLUT_ELAPSED_TIME); // returns the number of milliseconds since glutInit() was called.
	float deltaTime = (float)(curTime - preTime) / 1000.0f; // frame-different time in seconds
	ManyMouseEvent event;
	while (ManyMouse_PollEvent(&event) != 0)
	{
		switch (event.type)
		{

		case MANYMOUSE_EVENT_RELMOTION:
			//std::cout << "rel motion" << std::endl;
			//std::cout << "device: " << event.device << " item: " << event.item << " value: " << event.value << std::endl;
			if (mice.find(event.device) == mice.end())
			{
				mice[event.device] = new Mouse();
			}
			if (event.item == 0)
			{
				mice[event.device]->updateX((float)event.value);
			}
			else 
			{
				mice[event.device]->updateY((float)event.value);
			}
			break;
		case MANYMOUSE_EVENT_BUTTON:
			if (mice.find(event.device) == mice.end())
			{
				mice[event.device] = new Mouse();
			}

			if (event.item == 0)
			{
				mice[event.device]->leftButtonPressed = event.value;
				//mice[event.device]->physicsSelect = NULL;
				if (!event.value && mice[event.device]->physicsSelect != NULL)
				{
					mice[event.device]->releasePhysicsSelect();
				}
			}
			else
			{
				mice[event.device]->rightButtonPressed = event.value;
				world.AddBox(0, 4, 1, Color::getRed(), .5f, .5f);
			}
		}


	}

	//collisions
	for (int j = 0; j < world.bodies.size(); j++)
	{
		for (map<int, Mouse*>::iterator itr = mice.begin(); itr != mice.end(); ++itr)
		{
			b2AABB a;
			b2Transform t;
			t.Set(b2Vec2(itr->second->x, itr->second->y), 0);
			itr->second->shape.ComputeAABB(&a,t,0);
			b2AABB b;
			b2Transform bt = world.bodies[j]->body->GetTransform();
			
			world.bodies[j]->shape.ComputeAABB(&b, bt, 0);
			if (b2TestOverlap(a, b))
			{
				if (itr->second->leftButtonPressed && itr->second->physicsSelect == NULL)
				{
					world.bodies[j]->body->SetType(b2_kinematicBody);
					world.bodies[j]->body->SetLinearVelocity(b2Vec2_zero);
					itr->second->physicsSelect = world.bodies[j];
					
				}
			}
		}
	}
	//draw mice
	for (map<int, Mouse*>::iterator itr = mice.begin(); itr != mice.end(); ++itr)
	{
		itr->second->update();
	}
	
	world.Update();
	
	display();
	preTime = curTime; // make the curTime become the preTime for the next frame
}



int main(int argc, char* argv[])
{
	// before create a glut window,
	// initialize stuff not opengl/glut dependent
	init();

	//initialize GLUT, let it extract command-line GLUT options that you may provide
	//NOTE that the '&' before argc
	glutInit(&argc, argv);
	
	// specify as double bufferred can make the display faster
	// Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//set the initial window size */
	glutInitWindowSize((int)width, (int)height);

	// create the window with a title
	glutCreateWindow("First OpenGL Program");
	glutSetCursor(GLUT_CURSOR_NONE);
	glutFullScreen();
	/* --- register callbacks with GLUT --- */

	//register function to handle window resizes
	glutReshapeFunc(reshape);

	//register function that draws in the window
	glutDisplayFunc(display);

	glutIdleFunc(update);


	//start the glut main loop
	glutMainLoop();

	return 0;
}