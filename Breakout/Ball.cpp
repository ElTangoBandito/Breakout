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



Ball::Ball(
	float ballSizeIn,
	sf::Vector2f positionIn,
	sf::Vector2f velocityIn
) {
	this->ballSize = ballSizeIn;
	this->position = positionIn;
	this->velocity = velocityIn;
	this->isDeadBall = false;
	this->collisionColorLife = 0;
	this->wrapColor = sf::Color::White;
	this->isFired = false;
	this->collisionColorLife = 0;
	ballTexture.loadFromFile("Resources/Textures/Ball.png");
	updateOrigin();
}
Ball::~Ball() {

}
void Ball::updateOrigin() {
	this->origin.x = this->position.x + ballSize;
	this->origin.y = this->position.y + ballSize;
}

void Ball::update(float deltaTimeIn) {
	if (isFired && !isDeadBall) {
	this->position.x += this->velocity.x * deltaTimeIn;
	this->position.y += this->velocity.y * deltaTimeIn;
	}
	updateOrigin();
}

void Ball::draw(sf::RenderWindow* windowIn) {
	sf::CircleShape ball(ballSize);
	ball.setPosition(this->position.x, this->position.y);
	ball.setFillColor(sf::Color::White);
	//ball.setTexture(&ballTexture);
	if (collisionColorLife > 0) {
		ball.setFillColor(sf::Color(255, 255, 10, 255));
		collisionColorLife--;
	}
	windowIn->draw(ball);
}