#include "Ball.h"
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>

class Brick
{
public:
	float brickLength;
	float brickWidth;
	sf::Vector2f position;
	sf::Vector2f origin;
	std::vector<sf::Texture*>* brickTextures;
	sf::Texture* brickTexture;
	sf::Color brickColor;
	int brickLife;
	int brickType;
	int fadeLife;
	int scoreMultiplier;
	float clockTime;
	bool isDestroyed;
	bool hitScoreAwarded;
	bool isHit;
public:
	Brick(
		float brickLengthIn,
		float brickWidthIn,
		sf::Vector2f positionIn,
		std::vector<sf::Texture*>* brickTexturesIn,
		int lifeIn,
		int randomIn
	);
	~Brick();

	void updateOrigin();
	void generateBreadTexture();
	void update(Ball* ballIn);
	void checkCollision(Ball* ballIn);
	void draw(sf::RenderWindow* windowIn);
};

