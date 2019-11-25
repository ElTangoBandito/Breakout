#include "Powerup.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>

Powerup::Powerup(sf::Vector2f positionIn, std::vector<sf::Sound*>* powerupSoundsIn, std::vector<sf::Texture*>* powerupTexturesIn, float windowSizeYIn) {
	this->position = positionIn;
	this->powerupRadius = 25;
	this->velocity = sf::Vector2f(0.0f, 0.11f);
	this->powerupSounds = powerupSoundsIn;
	this->powerupTextures = powerupTexturesIn;
	this->isTaken = false;
	this->isDead = false;
	this->windowSizeY = windowSizeYIn;
	this->rotation = 0;
	determineType();
	updateOrigin();
}

Powerup::~Powerup(){}

void Powerup::determineType() {
	int randomType = rand() % 20;
	if (randomType == 20) {
		this->type = 4;
	} 
	else if (randomType < 20 && randomType >= 15) {
		this->type = 3;
	}
	else if (randomType < 15 && randomType >= 10) {
		this->type = 2;
	}
	else if (randomType < 10 && randomType >= 5) {
		this->type = 1;
	}
	else {
		this->type = 0;
	}
}

void Powerup::updateOrigin() {
	this->origin.x = this->position.x + this->powerupRadius;
	this->origin.y = this->position.y + this->powerupRadius;
}

void Powerup::update(float deltaTimeIn, Paddle* paddleIn) {
	this->position.y = this->position.y + (this->velocity.y * deltaTimeIn);
	updateOrigin();
	if (!this->isTaken) {
		checkCollision(paddleIn);
	}
	if (this->position.y > windowSizeY + 50) {
		this->isDead = true;
	}
}

void Powerup::checkCollision(Paddle* paddleIn) {
	if (this->origin.x + this->powerupRadius > paddleIn->origin.x - paddleIn->paddleWidth / 2 && this->origin.x - this->powerupRadius < paddleIn->origin.x + paddleIn->paddleWidth / 2 && this->origin.y + this->powerupRadius > paddleIn->origin.y - paddleIn->paddleLength / 2 && this->origin.y - this->powerupRadius < paddleIn->origin.y + paddleIn->paddleLength / 2) {
		this->isTaken = true;
		this->isDead = true;
		powerupSounds->at(type)->play();
	}
}
void Powerup::draw(sf::RenderWindow* windowIn) {
	sf::CircleShape powerupDonut(this->powerupRadius);
	powerupDonut.setPosition(this->position.x, this->position.y);
	powerupDonut.setFillColor(sf::Color::White);
	powerupDonut.setRotation(this->rotation);
	this->rotation += 5;
	switch (this->type) {
	case 0:
		powerupDonut.setTexture(this->powerupTextures->at(0));
		break;
	case 1:
		powerupDonut.setTexture(this->powerupTextures->at(1));
		break;
	case 2:
		powerupDonut.setTexture(this->powerupTextures->at(2));
		break;
	case 3:
		powerupDonut.setTexture(this->powerupTextures->at(3));
		break;
	case 4:
		powerupDonut.setTexture(this->powerupTextures->at(4));
		break;
	}
	windowIn->draw(powerupDonut);
}