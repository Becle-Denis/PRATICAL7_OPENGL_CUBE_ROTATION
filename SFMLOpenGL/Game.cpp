#include "Game.h"

bool updatable = false;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	index = glGenLists(1);

	//setting the base cube

	//FACE
	cubePoints.push_back(db::Vector3(-2.0f, 2.0f, -10.0f));  //POINT A / 0 
	cubePoints.push_back(db::Vector3(2.0f, 2.0f, -10.0f));   //POINT B / 1 
	cubePoints.push_back(db::Vector3(2.0f, -2.0f, -10.0f));  //POINT C / 2 
	cubePoints.push_back(db::Vector3(-2.0f, -2.0f, -10.0f)); //POINT D / 3 

	//BACK 
	cubePoints.push_back(db::Vector3(-2.0f, 2.0f, -14.0f));  //POINT E / 4 
	cubePoints.push_back(db::Vector3(2.0f, 2.0f, -14.0f));   //POINT F / 5 
	cubePoints.push_back(db::Vector3(2.0f, -2.0f, -14.0f));  //POINT G / 6 
	cubePoints.push_back(db::Vector3(-2.0f, -2.0f, -14.0f)); //POINT H / 7 
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	if (updatable)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
	
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << endl;
	glLoadIdentity();
	//drawing the cube 
	glBegin(GL_TRIANGLES);
	{
		// ABD (0,1,3)
		glColor3f(0.0f, 0.0f, 0.8f);
		glVertex3f(cubePoints.at(0).x, cubePoints.at(0).y, cubePoints.at(0).z);
		glVertex3f(cubePoints.at(1).x, cubePoints.at(1).y, cubePoints.at(1).z);
		glVertex3f(cubePoints.at(3).x, cubePoints.at(3).y, cubePoints.at(3).z);

		// BCD (1,2,3)
		glColor3f(0.0f, 0.0f, 0.5f);
		glVertex3f(cubePoints.at(1).x, cubePoints.at(1).y, cubePoints.at(1).z);
		glVertex3f(cubePoints.at(2).x, cubePoints.at(2).y, cubePoints.at(2).z);
		glVertex3f(cubePoints.at(3).x, cubePoints.at(3).y, cubePoints.at(3).z);

		// CDG (2,3,6)
		glColor3f(0.5f, 0.0f, 0.0f);
		glVertex3f(cubePoints.at(2).x, cubePoints.at(2).y, cubePoints.at(2).z);
		glVertex3f(cubePoints.at(3).x, cubePoints.at(3).y, cubePoints.at(3).z); 
		glVertex3f(cubePoints.at(6).x, cubePoints.at(6).y, cubePoints.at(6).z);

		//DGH (3,6,7)
		glColor3f(0.8f, 0.0f, 0.0f);
		glVertex3f(cubePoints.at(3).x, cubePoints.at(3).y, cubePoints.at(3).z);
		glVertex3f(cubePoints.at(6).x, cubePoints.at(6).y, cubePoints.at(6).z);
		glVertex3f(cubePoints.at(7).x, cubePoints.at(7).y, cubePoints.at(7).z);

		//DEH (3,4,7)
		glColor3f(0.0f, 0.5f, 0.0f);
		glVertex3f(cubePoints.at(3).x, cubePoints.at(3).y, cubePoints.at(3).z);
		glVertex3f(cubePoints.at(4).x, cubePoints.at(4).y, cubePoints.at(4).z);
		glVertex3f(cubePoints.at(7).x, cubePoints.at(7).y, cubePoints.at(7).z);

		//ADE (0,3,4)
		glColor3f(0.0f, 0.8f, 0.0f);
		glVertex3f(cubePoints.at(0).x, cubePoints.at(0).y, cubePoints.at(0).z);
		glVertex3f(cubePoints.at(3).x, cubePoints.at(3).y, cubePoints.at(3).z);
		glVertex3f(cubePoints.at(4).x, cubePoints.at(4).y, cubePoints.at(4).z);

		//EGH (4,6,7)

		//EFG (4,5,6)

		//BCG (1,2,6)

		//BFG (1,5,6)

		//ABE (0,1,4)

		//BEF (1,4,5)


	}
	glEnd();

	/*
	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(cubePoints.at(0).x, cubePoints.at(0).y, cubePoints.at(0).z);
		glVertex3f(cubePoints.at(1).x, cubePoints.at(1).y, cubePoints.at(1).z);
		glVertex3f(cubePoints.at(2).x, cubePoints.at(2).y, cubePoints.at(2).z);
		glVertex3f(cubePoints.at(3).x, cubePoints.at(3).y, cubePoints.at(3).z);

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(cubePoints.at(4).x, cubePoints.at(4).y, cubePoints.at(4).z);
		glVertex3f(cubePoints.at(5).x, cubePoints.at(5).y, cubePoints.at(5).z);
		glVertex3f(cubePoints.at(6).x, cubePoints.at(6).y, cubePoints.at(6).z);
		glVertex3f(cubePoints.at(7).x, cubePoints.at(7).y, cubePoints.at(7).z);

	}
	glEnd();
	*/
	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

