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

class AnnoyingBread
{
public:
	float breadLength;
	float breadWidth;
	sf::Vector2f position;
	sf::Vector2f origin;
	sf::Vector2f velocity;
	std::vector<sf::Sound*>* annoyingSounds;
	sf::Texture annoyingTexture;
	sf::Texture annoyingHitTexture;
	sf::Color hitColor;
	float hitLife;
	bool isHit;
	bool goalReached;
	float acceleration;
public:
	AnnoyingBread(float positionXIn, float positionYIn, std::vector<sf::Sound*>* annoyingSoundsIn);
	~AnnoyingBread();

	void updateOrigin();
	void update(float deltaTimeIn, Ball* ballIn, float windowSizeX);
	void checkCollision(Ball* ballIn, float deltaTimeIn);
	void accelerateBall(Ball* ballIn, float deltaTimeIn);
	void draw(sf::RenderWindow* windowIn);
};

