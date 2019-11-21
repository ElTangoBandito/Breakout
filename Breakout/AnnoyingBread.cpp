#include "AnnoyingBread.h"
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

AnnoyingBread::AnnoyingBread(float positionXIn, float positionYIn, std::vector<sf::Sound*>* annoyingSoundsIn) {
	this->breadLength = 50.0f;
	this->breadWidth = 170.0f;
	this->position = sf::Vector2f(positionXIn, positionYIn);
	this->velocity = sf::Vector2f(-0.03f, 0.0f);
	updateOrigin();
	this->annoyingSounds = annoyingSoundsIn;
	this->annoyingTexture.loadFromFile("Resources/Textures/AnnoyingBread.jpg");
	this->annoyingHitTexture.loadFromFile("Resources/Textures/AnnoyingBreadHit.jpg");
	this->annoyingTexture.setSmooth(true);
	this->annoyingHitTexture.setSmooth(true);
	this->hitColor = sf::Color::Red;
	this->isHit = false;
	this->hitLife = 0;
	this->goalReached = true;
	this->acceleration = 0.001f;
}

AnnoyingBread::~AnnoyingBread() {};

void AnnoyingBread::update(float deltaTimeIn, Ball* ballIn, float windowSizeX) {
	if (!goalReached) {
		this->position.x += this->velocity.x * deltaTimeIn;
	}
	if (this->position.x < -this->breadWidth - 20) {
		this->goalReached = true;
		this->velocity.x = abs(this->velocity.x);
	}
	else if (this->position.x > windowSizeX + 20) {
		this->goalReached = true;
		this->velocity.x = -abs(this->velocity.x);
	}
	checkCollision(ballIn, deltaTimeIn);
	if (!goalReached) {
		this->position.x += this->velocity.x;
	}
	this->hitLife--;
	updateOrigin();
}
void AnnoyingBread::updateOrigin() {
	this->origin = sf::Vector2f(this->position.x + breadWidth/2, this->position.y + this->breadLength/2);
}

void AnnoyingBread::accelerateBall(Ball* ballIn, float deltaTimeIn) {
	float sum = abs(ballIn->velocity.x) + abs(ballIn->velocity.y);
	float xRatio = ballIn->velocity.x / sum;
	float yRatio = ballIn->velocity.y / sum;
	ballIn->velocity.x += this->acceleration * deltaTimeIn * xRatio;
	ballIn->velocity.y += this->acceleration * deltaTimeIn * yRatio;
}

void AnnoyingBread::checkCollision(Ball* ballIn, float deltaTimeIn) {
	this->isHit = false;
	bool collided = false;
	if (ballIn->origin.x + ballIn->ballSize > this->origin.x - this->breadWidth / 2 && ballIn->origin.x - ballIn->ballSize < this->origin.x + this->breadWidth / 2 && ballIn->origin.y + ballIn->ballSize > this->origin.y - this->breadLength / 2 && ballIn->origin.y - ballIn->ballSize < this->origin.y + this->breadLength / 2) {
		collided = true;
		this->isHit = true;
		this->hitLife = 15;
		int random = rand() % 4;
		this->annoyingSounds->at(random)->play();
	}
	if (collided) {
		accelerateBall(ballIn, deltaTimeIn);
		ballIn->collisionColorLife = 10;
		float ballBottom = ballIn->origin.y + ballIn->ballSize;
		float ballRight = ballIn->origin.x + ballIn->ballSize;
		float brickBottom = this->origin.y + this->breadLength / 2;
		float brickRight = this->origin.x + this->breadWidth / 2;

		float bottomCollision = brickBottom - ballIn->position.y;
		float topCollision = ballBottom - this->position.y;
		float leftCollision = ballRight - this->position.x;
		float rightCollision = brickRight - ballIn->position.x;

		if (topCollision < bottomCollision && topCollision < leftCollision && topCollision < rightCollision) {
			//collision at top
			//if (ballIn->velocity.y < 0) {
			//	ballIn->velocity.x = ballIn->velocity.x * -1;
			//}
			ballIn->position.y -= 1;
			ballIn->velocity.y = abs(ballIn->velocity.y) * -1;
		}

		if (bottomCollision < topCollision && bottomCollision < leftCollision && bottomCollision < rightCollision) {
			//if (ballIn->velocity.y > 0) {
			//	ballIn->velocity.x = ballIn->velocity.x * -1;
			//}
			ballIn->position.y += 1;
			ballIn->velocity.y = abs(ballIn->velocity.y);

		}

		if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < bottomCollision) {
			//if (ballIn->velocity.x < 0) {
			//	ballIn->velocity.y = ballIn->velocity.y * -1;
			//}
			ballIn->position.x -= 1;
			ballIn->velocity.x = abs(ballIn->velocity.x) * -1;
		}

		if (rightCollision < topCollision && rightCollision < leftCollision && rightCollision < bottomCollision) {
			//if (ballIn->velocity.x > 0) {
			//	ballIn->velocity.y = ballIn->velocity.y * -1;
			//}
			ballIn->position.x += 1;
			ballIn->velocity.x = abs(ballIn->velocity.x);
		}
	}
}

void AnnoyingBread::draw(sf::RenderWindow* windowIn) {
	sf::RectangleShape rect(sf::Vector2f(this->breadWidth, this->breadLength));
	rect.setPosition(this->position.x, this->position.y);
	if (this->hitLife > 0) {
		rect.setTexture(&this->annoyingHitTexture);
		//rect.setFillColor(hitColor);
	}
	else {
		rect.setTexture(&this->annoyingTexture);
	}
	windowIn->draw(rect);
}
