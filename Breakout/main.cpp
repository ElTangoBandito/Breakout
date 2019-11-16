#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <random>
#include "Ball.h"

//global variable stuff
float globalBallRadius = 5.0f;
int windowSizeX = 800;
int windowSizeY = 800;
float globalBallVelocityX = -0.25f;
float globalBallVelocityY = 0.2f;
float PI = 3.14159265f;
float globalPaddleLength = 80.0f;
int globalTotalHitCounter = 0;
bool gameOver = false;
int globalPaddleHitLife = 15;
int globalBallCollisionLife = 10;
float deltaTimePrev = 0.0f;
float deltaTimeCurrent = 0.0f;
float deltaTime = 1.0f;

void updateDT(sf::Clock* clockIn) {
	deltaTimePrev = deltaTimeCurrent;
	deltaTimeCurrent = clockIn->getElapsedTime().asMilliseconds();
	deltaTime = deltaTimeCurrent - deltaTimePrev;

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "My Window!");
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;

	//Balls stuff
	Ball startingBall(
		globalBallRadius,
		sf::Vector2f(windowSizeX / 2, windowSizeY / 2),
		sf::Vector2f(globalBallVelocityX, globalBallVelocityY)
	);
	std::vector<Ball*> balls;
	balls.push_back(&startingBall);


	while (window.isOpen())
	{

		updateDT(&clock);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);

		balls.at(0)->update(deltaTime);
		balls.at(0)->draw(&window);
		window.display();
	}

	return 0;
}
