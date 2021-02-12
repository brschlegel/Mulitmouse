#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif


#include <iostream>
#include <map>
#include <vector>
#include "Color.h"
#include "MouseManager.h"
#include "Physics.h"
#include "Goal.h"
#include "CollisionManager.h"
#include <memory>

using namespace std;
// the window's width and height
int width, height;
MouseManager mouseManager;
PhysicsWorld world = PhysicsWorld(b2Vec2(0, -10));
CollisionManager collisionManager = CollisionManager(&world, &mouseManager);
Goal g = Goal(-2, 2, Color::getGreen(), 1, 1);
bool warpPointer = true;


void init(void)
{

	// initialize the size of the window
	width = 1600;
	height = 800;
	mouseManager = MouseManager();
	world.AddRectBarrier(0, -5, 20, 1);
	world.AddRectBarrier(0, 5, 20, 1);
	world.AddRectBarrier(-9, 0, 1, 10);
	world.AddRectBarrier(9, 0, 1, 10);
	
	world.AddBox(0, 4, 1, Color::getRed(), .5f,.5f);
	collisionManager.buildGoal(-2, 2, 1, 1, Color::getGreen());

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
	mouseManager.draw();
	collisionManager.draw();

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

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}

	if (key == 'b') {
		world.AddBox(0, 4, 1, Color::getRed(), .5f, .5f);
	}

	if (key == 'w') {
		warpPointer = !warpPointer;
	}
	glutPostRedisplay();
}


void update()
{
	mouseManager.update();
	//keep the mouse from going off screen
	if (warpPointer) {
		glutWarpPointer(width / 2, height / 2);
	}
	//collisions

	world.Update();
	collisionManager.update();
	display();
	
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
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);


	//start the glut main loop
	glutMainLoop();

	return 0;
}