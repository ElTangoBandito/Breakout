#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>


class Ball
{
public:
	float ballSize;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f origin;
	int hitCount;
	bool isDeadBall;
	int collisionColorLife;
	sf::Color wrapColor;

public:
	Ball(
		float ballSize,
		sf::Vector2f position,
		sf::Vector2f velocity
	);

	~Ball();
	void updateOrigin();
	void update(float deltaTime);
	void draw(sf::RenderWindow* windowIn);
};
