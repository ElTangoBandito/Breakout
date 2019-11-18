#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <random>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

//wrapped bread for extra hit life


int windowSizeX = 800;
int windowSizeY = 800;
bool gameOver = false;

//game state varibles;
int gameScore = 0;
int gameLives = 3;
int comboHit = 0;

//ball variables
float globalBallRadius = 6.0f;
float globalBallVelocityX = 0.04f;
float globalBallVelocityY = -0.5f;

//paddle variables
float globalPaddleLength = 20.0f;
float globalPaddleWidth = 81.3f;
float globalPaddleSpeed = 0.5f;

//brick variables
float globalBrickWidth = 80.0f;
float globalBrickLength = 20.0f;

//collision variables
int globalPaddleHitLife = 15;
int globalBallCollisionLife = 10;
int globalTotalHitCounter = 0;
float perHitForce = 0.0f;
float PI = 3.14159265f;

//delta time variables
float deltaTimePrev = 0.0f;
float deltaTimeCurrent = 0.0f;
float deltaTime = 1.0f;

void updateDT(sf::Clock* clockIn) {
	deltaTimePrev = deltaTimeCurrent;
	deltaTimeCurrent = clockIn->getElapsedTime().asMilliseconds();
	deltaTime = deltaTimeCurrent - deltaTimePrev;

}

void checkCollisionPaddle(Ball* ballIn, Paddle* paddleIn) {
	float safetyNet = abs(ballIn->velocity.y) * 50; //prevents ball from going through paddle when its too fast. Ball will still go through eventually.
	bool collided = false;
	if (ballIn->origin.x + ballIn->ballSize > paddleIn->origin.x - paddleIn->paddleWidth / 2 && ballIn->origin.x - ballIn->ballSize < paddleIn->origin.x + paddleIn->paddleWidth / 2 && ballIn->origin.y + ballIn->ballSize > paddleIn->origin.y - paddleIn->paddleLength / 2 && ballIn->origin.y - ballIn->ballSize < paddleIn->origin.y + paddleIn->paddleLength / 2 + safetyNet) {
		collided = true;
		paddleIn->hitLife = 15;
		if (ballIn->velocity.y > 0) {
			ballIn->velocity.y = abs(ballIn->velocity.y) * -1;
		}
	}

	if (collided) {
		float maxAngle = 260.0f;
		float xForce = ballIn->velocity.x;
		float yForce = ballIn->velocity.y;
		float hitLocation = ballIn->origin.x - paddleIn->origin.x;
		bool isLeft = true;
		if (hitLocation > 0) {
			isLeft = false;
		}
		float angleScale = abs(hitLocation) / (paddleIn->paddleWidth) / 2;
		angleScale = angleScale * maxAngle;
		float hypoforce = sqrt(pow(xForce, 2) + pow(yForce, 2)) + perHitForce;
		perHitForce = 0;
		float newVelocityX = sin(angleScale * PI / 180.0) * hypoforce;
		float newVelocityY = cos(angleScale * PI / 180.0) * hypoforce;

		if (isLeft) {
			if (newVelocityX > 0) {
				newVelocityX = newVelocityX * -1;
			}
		}
		comboHit = 0;
		ballIn->velocity.x = newVelocityX;
		ballIn->velocity.y = abs(newVelocityY) * -1;
	}
	else if (ballIn->origin.y > windowSizeY + safetyNet && !ballIn->isDeadBall) {
		ballIn->isDeadBall = true;
		comboHit = 0;
		gameLives--;
		if (gameLives < 1) {
			gameOver = true;
		}
		else {
			ballIn->isFired = false;
			ballIn->velocity = sf::Vector2f(globalBallVelocityX, globalBallVelocityY);
		}
	}

	if (ballIn->origin.x > windowSizeX - ballIn->ballSize) {
		if (ballIn->velocity.x > 0) {
			ballIn->position.x = windowSizeX - ballIn->ballSize*2;
			ballIn->velocity.x = abs(ballIn->velocity.x) * -1;
		}
	}
	else if (ballIn->origin.x < 0 + ballIn->ballSize) {
		if (ballIn->velocity.x < 0) {
			ballIn->position.x = 0;
			ballIn->velocity.x = abs(ballIn->velocity.x);
		}
	}

	if (ballIn->origin.y < 0) {
		if (ballIn->velocity.y < 0) {
			ballIn->position.y = 0;
			ballIn->velocity.y = abs(ballIn->velocity.y);
		}
	}
}

void setupStageOne(std::vector<Brick*>* bricksIn, std::vector<sf::Texture*>* brickTexturesIn) {
	float xGapDistance = 7.0f;
	float yGapDistance = 20.0f;
	int colBlocksNeeded = floor(windowSizeX / (globalBrickWidth + xGapDistance));
	int rowsNeeded = 9;
	float edgeDistance = (windowSizeX - (colBlocksNeeded * (globalBrickWidth + xGapDistance)))/2;
	float xPosition = edgeDistance;
	float yPosition = 35.0f;
	int brickLife = 1;
	for (int i = 0; i < rowsNeeded; i++) {
		for (int j = 0; j < colBlocksNeeded; j++) {
			switch (i) {
			case 0:
				if (j % 2 == 0) {
					brickLife = 3;
				}
				else if (i == 0 && j % 2 == 1) {
					brickLife = 2;
				}
				break;
			case 1:
				break;
			case 2:
				if (j == 1 || j == 4 || j == 7) {
					brickLife = 2;
				}
				break;
			case 3:
				if (j == 0 || j == 1 || j == 3 || j == 4 || j == 6 || j == 7) {
					brickLife = 2;
				}
				break;
			case 4: 
				if (j == 0 || j == 2 || j == 3 || j == 5 || j == 6 || j == 8) {
					brickLife = 2;
				}
				if (j == 1 || j == 4||j == 7) {
					brickLife = 3;
				}
				break;
			case 5:
				if (j == 0 || j == 1 || j == 3 || j == 4 || j == 6 || j == 7) {
					brickLife = 2;
				}
				break;
			case 6:
				if (j == 1 || j == 4 || j == 7) {
					brickLife = 2;
				}
				break;
			case 7:
				break;
			case 8:
				if (j % 2 == 0) {
					brickLife = 2;
				}
				else if (j % 2 == 1) {
					brickLife = 3;
				}
				break;
			}
			Brick* newBrick;
			newBrick = new Brick(globalBrickLength, globalBrickWidth, sf::Vector2f(xPosition, yPosition), brickTexturesIn, brickLife);
			xPosition = xPosition + globalBrickWidth + xGapDistance;
			bricksIn->push_back(newBrick);
			brickLife = 1;
		}
		xPosition = edgeDistance;
		colBlocksNeeded = floor(windowSizeX / (globalBrickWidth + xGapDistance));
		if (i % 2 == 0) {
			xPosition = globalBrickWidth/2;
			colBlocksNeeded -= 1;
		}
		yPosition = yPosition + globalBrickLength + yGapDistance;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "My Window!");
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;

	//Balls stuff
	Ball startingBall(
		globalBallRadius,
		sf::Vector2f(windowSizeX / 2, windowSizeY / 2),
		sf::Vector2f(globalBallVelocityX, globalBallVelocityY)
	);
	std::vector<Ball*> balls;
	balls.push_back(&startingBall);

	//Paddle stuff
	Paddle playerPaddle(globalPaddleLength, globalPaddleWidth, globalPaddleSpeed, sf::Vector2f(windowSizeX/2 - globalPaddleWidth / 2, windowSizeY - globalPaddleLength));

	//Brick Textures
	std::vector<sf::Texture*> brickTextures;
	sf::Texture paperBagTexture;
	sf::Texture brick1Texture;
	sf::Texture brick1BagTexture;
	sf::Texture brick1HitTexture;
	paperBagTexture.loadFromFile("Resources/Textures/Paperbag.png");
	brick1Texture.loadFromFile("Resources/Textures/Brick1.jpg");
	brick1BagTexture.loadFromFile("Resources/Textures/Brick1Bag.jpg");
	brick1HitTexture.loadFromFile("Resources/Textures/Brick1Hit.jpg");
	paperBagTexture.setSmooth(true);
	brick1Texture.setSmooth(true);
	brick1BagTexture.setSmooth(true);
	brick1HitTexture.setSmooth(true);
	brickTextures.push_back(&paperBagTexture);
	brickTextures.push_back(&brick1BagTexture);
	brickTextures.push_back(&brick1Texture);
	brickTextures.push_back(&brick1HitTexture);

	//Brick stuff
	std::vector<Brick*> bricks;
	setupStageOne(&bricks, &brickTextures);

	//font stuff
	sf::Font font;
	if (!font.loadFromFile("Resources/Fonts/Mister Pumpkins Aged.ttf"))
		return -1;
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(20);
	scoreText.setPosition(sf::Vector2f(62, 0));
	sf::Text scoreStringText;
	scoreStringText.setFont(font);
	scoreStringText.setFillColor(sf::Color::White);
	scoreStringText.setCharacterSize(20);
	scoreStringText.setString("Score :");

	sf::Text livesText;
	livesText.setFont(font);
	livesText.setFillColor(sf::Color::White);
	livesText.setString("Lives :");
	livesText.setPosition(sf::Vector2f(windowSizeX - 150, 0));
	livesText.setCharacterSize(20);
	sf::Text livesDisplay;
	livesDisplay.setFont(font);
	livesDisplay.setFillColor(sf::Color::White);

	while (window.isOpen())
	{

		updateDT(&clock);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(15,15,25,255));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			balls.at(0)->isFired = true;
			balls.at(0)->isDeadBall = false;
		}
		checkCollisionPaddle(balls.at(0), &playerPaddle);
		if (!balls.at(0)->isFired) {
			balls.at(0)->position.x = playerPaddle.origin.x - balls.at(0)->ballSize;
			balls.at(0)->position.y = playerPaddle.origin.y - balls.at(0)->ballSize*2 - playerPaddle.paddleLength/2;
		}
		balls.at(0)->update(deltaTime);
		balls.at(0)->draw(&window);
		playerPaddle.update(deltaTime, windowSizeX);
		playerPaddle.draw(&window);

		for (int i = 0; i < bricks.size(); i++) {
			bricks.at(i)->update(balls.at(0));
			bricks.at(i)->draw(&window);
			if (bricks.at(i)->isHit) {
				comboHit++;
				bricks.at(i)->isHit = false;
				if (!bricks.at(i)->hitScoreAwarded && bricks.at(i)->brickLife == 0) {
					bricks.at(i)->hitScoreAwarded = true;
					int awardedScore = 0;
					int blockScore = 10 * bricks.at(i)->scoreMultiplier;
					int comboBonus = 0;
					if (comboHit > 1) {
						comboBonus = 2 * (comboHit - 1);
						if (comboHit > 6) {
							comboBonus = blockScore;
						}
					}
					awardedScore = blockScore + comboBonus;
					gameScore += awardedScore;
				}
			}
			if (bricks.at(i)->isDestroyed) {
				bricks.erase(bricks.begin() + i);
			}
		}


		//score text stuff
		std::ostringstream ss;
		ss << gameScore;
		std::string printMe(ss.str());
		scoreText.setString(printMe);
		window.draw(scoreText);
		window.draw(scoreStringText);
		window.draw(livesText);
		window.display();
	}

	return 0;
}
