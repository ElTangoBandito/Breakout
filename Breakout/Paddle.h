#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

class Paddle
{
public:
	float paddleLength;
	float paddleWidth;
	sf::Vector2f position;
	sf::Vector2f origin;
	float paddleSpeed;
	int hitLife;
	sf::Texture paddleTexture;
	sf::Texture paddleHitTexture;

public:
	Paddle(
		float lengthIn,
		float widthIn,
		float speedIn,
		sf::Vector2f positionIn
	);
	~Paddle();

	void updateOrigin();
	void update(float deltaTime, int windowSizeXIn);
	void draw(sf::RenderWindow* windowIn);
};

