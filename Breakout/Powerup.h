#include "Paddle.h"
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
class Powerup
{
public:
	float powerupRadius;
	sf::Vector2f position;
	sf::Vector2f origin;
	sf::Vector2f velocity;
	std::vector<sf::Sound*>* powerupSounds;
	std::vector<sf::Texture*>* powerupTextures;
	bool isTaken;
	bool isDead;
	int type;
	float windowSizeY;
	float rotation;
public:
	Powerup(sf::Vector2f positionIn, std::vector<sf::Sound*>* powerupSoundsIn, std::vector<sf::Texture*>* powerupTexturesIn, float windowSizeY);
	~Powerup();

	void determineType();
	void updateOrigin();
	void update(float deltaTimeIn, Paddle* paddleIn);
	void checkCollision(Paddle* paddleIn);
	void draw(sf::RenderWindow* windowIn);
};

