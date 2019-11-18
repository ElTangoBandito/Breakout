#include "Brick.h"
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

Brick::Brick(
	float brickLengthIn,
	float brickWidthIn,
	sf::Vector2f positionIn,
	std::vector<sf::Texture*>* brickTexturesIn,
	int lifeIn
) {
	this->brickLength = brickLengthIn;
	this->brickWidth = brickWidthIn;
	this->position = positionIn;
	this->brickTextures = brickTexturesIn;
	this->fadeLife = 0;
	this->isDestroyed = false;
	this->hitScoreAwarded = false;
	this->isHit = false;
	this->brickColor = sf::Color::White;
	this->brickLife = lifeIn;
	this->scoreMultiplier = this->brickLife;
	generateBreadTexture();
	updateOrigin();
}

Brick::~Brick(){}

void Brick::updateOrigin() {
	this->origin.x = this->position.x + this->brickWidth / 2;
	this->origin.y = this->position.y + this->brickLength / 2;
}

void Brick::generateBreadTexture() {
	switch (this->brickLife) {
		case 3:
			this->brickTexture = this->brickTextures->at(0);
			break;
		case 2:
			this->brickTexture = this->brickTextures->at(1);
			break;
		case 1:
			this->brickTexture = this->brickTextures->at(2);
			break;
		case 0:
			this->brickTexture = this->brickTextures->at(3);
			break;
	}
}

void Brick::update(Ball* ballIn) {
	if (this->fadeLife == 0) {
		checkCollision(ballIn);
	}
	else if (fadeLife > 1) {
		this->fadeLife--;
		if (this->fadeLife == 1) {
			this->isDestroyed = true;
		}
	}
}

void Brick::checkCollision(Ball* ballIn) {
	bool collided = false;
	if (ballIn->origin.x + ballIn->ballSize > this->origin.x - this->brickWidth / 2 && ballIn->origin.x - ballIn->ballSize < this->origin.x + this->brickWidth / 2 && ballIn->origin.y + ballIn->ballSize > this->origin.y - this->brickLength / 2 && ballIn->origin.y - ballIn->ballSize < this->origin.y + this->brickLength / 2) {
		collided = true;
	}
	if (collided) {
		//code concept sourc https://stackoverflow.com/questions/5062833/detecting-the-direction-of-a-collision
		float ballBottom = ballIn->origin.y + ballIn->ballSize;
		float ballRight = ballIn->origin.x + ballIn->ballSize;
		float brickBottom = this->origin.y + this->brickLength / 2;
		float brickRight = this->origin.x + this->brickWidth / 2;

		float bottomCollision = brickBottom - ballIn->position.y;
		float topCollision = ballBottom - this->position.y;
		float leftCollision = ballRight - this->position.x;
		float rightCollision = brickRight - ballIn->position.x;

		if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision) {
			//collision at top
			if (ballIn->velocity.y < 0) {
				ballIn->velocity.x = ballIn->velocity.x * -1;
			}
			ballIn->velocity.y = abs(ballIn->velocity.y) * -1;
		}

		if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision) {
			if (ballIn->velocity.y > 0) {
				ballIn->velocity.x = ballIn->velocity.x * -1;
			}
			ballIn->velocity.y = abs(ballIn->velocity.y);
		}

		if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision) {
			if (ballIn->velocity.x < 0) {
				ballIn->velocity.y = ballIn->velocity.y * -1;
			}
			ballIn->velocity.x = abs(ballIn->velocity.x) * -1;
		}

		if (rightCollision < topCollision && rightCollision < leftCollision && rightCollision < bottomCollision) {
			if (ballIn->velocity.x > 0) {
				ballIn->velocity.y = ballIn->velocity.y * -1;
			}
			ballIn->velocity.x = abs(ballIn->velocity.x);
		}
		this->brickLife--;
		this->isHit = true;
		if (brickLife == 0) {
			this->fadeLife = 10;
		}
		generateBreadTexture();
		
	}
}

void Brick::draw(sf::RenderWindow* windowIn) {
	sf::RectangleShape rect(sf::Vector2f(this->brickWidth, this->brickLength));
	rect.setPosition(this->position.x, this->position.y);
	//rect.setFillColor(brickColor);
	rect.setTexture(this->brickTexture);
	windowIn->draw(rect);
}