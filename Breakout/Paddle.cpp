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

Paddle::Paddle(
	float lengthIn,
	float widthIn,
	float speedIn,
	sf::Vector2f positionIn
) {
	this->paddleLength = lengthIn;
	this->paddleWidth = widthIn;
	this->paddleSpeed = speedIn;
	this->position = positionIn;
	this->hitLife = 0;
	paddleTexture.loadFromFile("Resources/Textures/Paddle.jpg");
	paddleHitTexture.loadFromFile("Resources/Textures/PaddleHit.jpg");
	paddleTexture.setSmooth(true);
	paddleHitTexture.setSmooth(true);
	updateOrigin();
}

Paddle::~Paddle() {

}

void Paddle::updateOrigin() {
	this->origin.x = this->position.x + this->paddleWidth/2;
	this->origin.y = this->position.y + this->paddleLength/2;
}

void Paddle::update(float deltaTimeIn, int windowSizeXIn) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		if (this->origin.x > this->paddleWidth / 2) {
			this->position.x -= paddleSpeed * deltaTimeIn;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		if (this->origin.x < windowSizeXIn - this->paddleWidth / 2) {
			this->position.x += paddleSpeed * deltaTimeIn;
		}
	}
	updateOrigin();
}

void Paddle::draw(sf::RenderWindow* windowIn) {
	sf::RectangleShape rect(sf::Vector2f(this->paddleWidth, this->paddleLength));
	rect.setPosition(this->position.x, this->position.y);
	//rect.setFillColor(sf::Color::White);
	if (this->hitLife > 0) {
		rect.setTexture(&paddleHitTexture);
		this->hitLife--;
	}
	else {
		rect.setTexture(&paddleTexture);
	}
	windowIn->draw(rect);
}