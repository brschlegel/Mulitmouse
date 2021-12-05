


#include <iostream>
#include <map>
#include <vector>
#include "Color.h"
#include "MouseManager.h"
#include "Physics.h"
#include "Goal.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "LevelManager.h"
#include <ctime>
#include <cstdlib>
#include "Delegate.h"
#include "BenMath.h"




#define SFML_STATIC

#include <SFML/Window.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Source.h"
#include <chrono>


using namespace std;

int width, height;
PhysicsWorld world = PhysicsWorld();
CollisionManager collisionManager = CollisionManager(&world);
LevelManager* levelManager;
ShapeManager shapeManager = ShapeManager();
UIManager uiManager = UIManager();
Goal g = Goal(-2, 2, Color::getGreen(), 1, 1);
bool warpPointer = true;


void init(void)
{
	//Initialize srand
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	MouseManager::getInstance();
	// initialize the size of the window
	levelManager = LevelManager::getInstance();
	UIData::getInstance();
	ScoreManager::getInstance();

}

// called when the GL context need to be rendered
void display(sf::RenderWindow* window)
{
	
	// clear the screen to white, which is the background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// clear the buffer stored for drawing
	glClear(GL_COLOR_BUFFER_BIT);


	// this is to define in which transformed space / coordinate system (in a matrix form) the objects will be drawn. 
	// (we'll learn matrix-based transformation in later classes.) 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Specify a color for the following object(s) that will be drawn 
	glColor3f(1.0, 0.0, 0.0); // The color is RGB, each color channel is defined in [0, 1].
	glPushMatrix();
	

	levelManager->currentLevel->draw(window);
	
	MouseManager::instance->draw(window);

	
	
	glPopMatrix();

	//glutSwapBuffers(); // This example uses double framebuffers. This instructs the app that the current frame is finished and ready to display.

	
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
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	
}



void update()
{
	MouseManager::getInstance()->update();
	//keep the mouse from going off screen
	
	//collisions
	//world.Update();
	//collisionManager.update();
	levelManager->currentLevel->update();
	shapeManager.update(levelManager->currentLevel->currentScene->shapes);
	levelManager->checkChangeLevel();
	
}

int main()
{



	srand((unsigned)time(NULL));
	// create the window
	//sf::Window window(sf::VideoMode::getFullscreenModes()[0], "OpenGL", sf::Style::Fullscreen, sf::ContextSettings(24));
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "OpenGL", sf::Style::Fullscreen, sf::ContextSettings(24));

	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	width = window.getSize().x;
	height = window.getSize().y;

	// activate the window
	window.setActive(true);

	init();

	reshape(width, height);

	// run the main loop
	bool running =true;
	while (running)
	{
		//keyboard functions
	

	
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				running = false;
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

					running = false;

				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					//warpPointer = !warpPointer;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
				{
					sf::Texture t;
					t.create(1920,1080);
					t.update(window);
					sf::Image i = t.copyToImage();
					i.saveToFile("images/bruh.png");
				}
				break;
			case sf::Event::Resized:
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
				reshape(event.size.width, event.size.height);
			}
			
		
		}
		levelManager->currentLevel->currentScene->keyboardFunc(levelManager->currentLevel->currentScene);
		update();
		if (warpPointer)
		{
			sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2));
		}
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...

		display(&window);


		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}



