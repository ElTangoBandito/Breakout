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
	this->hitCount = 0;
	this->collisionColorLife = 0;
	this->wrapColor = sf::Color::White;
	updateOrigin();
}
Ball::~Ball() {

}
void Ball::updateOrigin() {
	this->origin.x = this->position.x + ballSize;
	this->origin.y = this->position.y + ballSize;
}

void Ball::update(float deltaTimeIn) {
	this->position.x += this->velocity.x * deltaTimeIn;
	this->position.y += this->velocity.y * deltaTimeIn;
	updateOrigin();
}

void Ball::draw(sf::RenderWindow* windowIn) {
	sf::CircleShape ball(ballSize);
	ball.setPosition(this->position.x, this->position.y);
	ball.setFillColor(sf::Color::White);
	windowIn->draw(ball);
}