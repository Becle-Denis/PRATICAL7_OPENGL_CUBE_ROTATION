#include "Game.h"

bool updatable = false;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
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

	rotationCLock.restart();
}

void Game::update()
{
	cout << "Update up" << endl;

	//---------------TRANSLATE ----------------------------------------------
	//moving far
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (db::Vector3& v : cubePoints)
		{
			v.z -= 0.01;
		}
	}

	//moving near 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (db::Vector3& v : cubePoints)
		{
			v.z += 0.01;
		}
	}

	//moving left 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (db::Vector3& v : cubePoints)
		{
			v.x -= 0.01;
		}
	}

	//moving right 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (db::Vector3& v : cubePoints)
		{
			v.x += 0.01;
		}
	}

	//moving up 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (db::Vector3& v : cubePoints)
		{
			v.y += 0.01;
		}
	}

	//moving down 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (db::Vector3& v : cubePoints)
		{
			v.y -= 0.01;
		}
	}


	//ROTATION 
	if (rotationCLock.getElapsedTime() > sf::milliseconds(10))
	{
		rotationCLock.restart();
		db::Vector3 center;
		center.x = (cubePoints.at(0).x + cubePoints.at(1).x + cubePoints.at(2).x + cubePoints.at(3).x + cubePoints.at(4).x + cubePoints.at(5).x + cubePoints.at(6).x + cubePoints.at(7).x) / 8;
		center.y = (cubePoints.at(0).y + cubePoints.at(1).y + cubePoints.at(2).y + cubePoints.at(3).y + cubePoints.at(4).y + cubePoints.at(5).y + cubePoints.at(6).y + cubePoints.at(7).y) / 8;
		center.z = (cubePoints.at(0).z + cubePoints.at(1).z + cubePoints.at(2).z + cubePoints.at(3).z + cubePoints.at(4).z + cubePoints.at(5).z + cubePoints.at(6).z + cubePoints.at(7).z) / 8;
		db::Matrix3 matrix;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			for (db::Vector3& v : cubePoints)
			{
				v = v - center;
				v = v * matrix.rotationX(1);
				v = v + center;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			for (db::Vector3& v : cubePoints)
			{
				v = v - center;
				v = v * matrix.rotationY(1);
				v = v + center;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			for (db::Vector3& v : cubePoints)
			{
				v = v - center;
				v = v * matrix.rotationZ(1);
				v = v + center;
			}
		}
	}

	
	
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
		glColor3f(0.5f, 0.5f, 0.0f);
		glVertex3f(cubePoints.at(4).x, cubePoints.at(4).y, cubePoints.at(4).z);
		glVertex3f(cubePoints.at(6).x, cubePoints.at(6).y, cubePoints.at(6).z);
		glVertex3f(cubePoints.at(7).x, cubePoints.at(7).y, cubePoints.at(7).z);

		//EFG (4,5,6)
		glColor3f(0.8f, 0.8f, 0.0f);
		glVertex3f(cubePoints.at(4).x, cubePoints.at(4).y, cubePoints.at(4).z);
		glVertex3f(cubePoints.at(5).x, cubePoints.at(5).y, cubePoints.at(5).z);
		glVertex3f(cubePoints.at(6).x, cubePoints.at(6).y, cubePoints.at(6).z);

		//BCG (1,2,6)
		glColor3f(0.0f, 0.5f, 0.5f);
		glVertex3f(cubePoints.at(1).x, cubePoints.at(1).y, cubePoints.at(1).z);
		glVertex3f(cubePoints.at(2).x, cubePoints.at(2).y, cubePoints.at(2).z);
		glVertex3f(cubePoints.at(6).x, cubePoints.at(6).y, cubePoints.at(6).z);

		//BFG (1,5,6)
		glColor3f(0.0f, 0.8f, 0.8f);
		glVertex3f(cubePoints.at(1).x, cubePoints.at(1).y, cubePoints.at(1).z);
		glVertex3f(cubePoints.at(5).x, cubePoints.at(5).y, cubePoints.at(5).z);
		glVertex3f(cubePoints.at(6).x, cubePoints.at(6).y, cubePoints.at(6).z);

		//ABE (0,1,4)
		glColor3f(0.5f, 0.0f, 0.5f);
		glVertex3f(cubePoints.at(0).x, cubePoints.at(0).y, cubePoints.at(0).z);
		glVertex3f(cubePoints.at(1).x, cubePoints.at(1).y, cubePoints.at(1).z);
		glVertex3f(cubePoints.at(4).x, cubePoints.at(4).y, cubePoints.at(4).z);

		//BEF (1,4,5)
		glColor3f(0.8f, 0.0f, 0.8f);
		glVertex3f(cubePoints.at(1).x, cubePoints.at(1).y, cubePoints.at(1).z);
		glVertex3f(cubePoints.at(4).x, cubePoints.at(4).y, cubePoints.at(4).z);
		glVertex3f(cubePoints.at(5).x, cubePoints.at(5).y, cubePoints.at(5).z);

	}
	glEnd();

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

