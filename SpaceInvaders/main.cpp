#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <chrono>
#include <random>
#include <array>
#include "Player.h"
#include "Alien.h"
#include "GlobalGame.h"
#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders!");
	sf::Event event;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	sf::Texture alienTexture;
	sf::Sprite alienSprite;
	sf::Sprite alienBulletSprite;
	sf::Texture alienBulletTexture;
	sf::Font fontTexture;

	backgroundTexture.loadFromFile("GameItems/Images/background.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	alienTexture.loadFromFile("GameItems/Images/alien2.png");
	alienSprite.setTexture(alienTexture);
	alienBulletTexture.loadFromFile("Gameitems/Images/AlienBullet.png");
	alienBulletSprite.setTexture(alienBulletTexture);
	fontTexture.loadFromFile("GameItems/Images/Tirto Writter.ttf");

	Player p;
	vector<Alien> aliens;
	vector<Bullet> alienBullets;
	vector<Alien>::iterator deadAliens;
	mt19937_64 randomManager;
	uniform_int_distribution<unsigned short> shootChance;

	unsigned short currentLevel = 1;
	int level = 1;
	chrono::microseconds lag(0);
	chrono::steady_clock::time_point lastTime;
	lastTime = chrono::steady_clock::now();

	bool moveDown = 0;
	bool reachedPlayer = false;
	unsigned short movePause = 2;
	shootChance = std::uniform_int_distribution<unsigned short>(0, std::max<short>(ALIEN_BULLET_CHANCE_MIN, ALIEN_BULLET_CHANCE - ALIEN_SHOOT_CHANCE_INCREASE * currentLevel));
	int score = 0;

	// Populates the container of Aliens with their X and Y coordinates
	for (unsigned short i = 0; i < ALIEN_COLS; i++)
	{
		for (unsigned short j = 0; j < ALIEN_ROWS; j++)
		{
			aliens.push_back(Alien((ALIEN_WIDTH + 50) * (1 + i), (ALIEN_HEIGHT + 40) * (1 + j)));
		}
	}

	while (window.isOpen())
	{
		// Attempt at making the game Frame Independent
		chrono::microseconds deltaTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - lastTime);
		lag += deltaTime;
		lastTime += deltaTime;
		while (FRAMES <= lag)
		{
			lag -= FRAMES;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			// Player has killed all aliens, Starts next level
			if (aliens.size() == 0)
			{
				currentLevel++;
				level++;
				for (unsigned short i = 0; i < ALIEN_COLS; i++)
				{
					for (unsigned short j = 0; j < ALIEN_ROWS; j++)
					{
						aliens.push_back(Alien((ALIEN_WIDTH + 50) * (1 + i), (ALIEN_HEIGHT + 40) * (1 + j)));
					}
				}
			}

			// Player has Died or Aliens have landed: Reset the level in terms of diffuculty and 
			if (p.getDead() == 1 || reachedPlayer == true)
			{
				p.reset();
				level = 1;
				score = 0;
				currentLevel = 1;
				shootChance = std::uniform_int_distribution<unsigned short>(0, std::max<short>(ALIEN_BULLET_CHANCE_MIN, ALIEN_BULLET_CHANCE - ALIEN_SHOOT_CHANCE_INCREASE * currentLevel));
				alienBullets.clear();
				aliens.clear();

				for (unsigned short i = 0; i < ALIEN_COLS; i++)
				{
					for (unsigned short j = 0; j < ALIEN_ROWS; j++)
					{
						aliens.push_back(Alien((ALIEN_WIDTH + 50) * (1 + i), (ALIEN_HEIGHT + 40) * (1 + j)));
					}
				}
			}
			// Drawing to screen Background and Player
			window.draw(backgroundSprite);
			p.draw(window);
			p.update(aliens, alienBullets);
		
			// Draws Alien to Screen, Updates Aliens Movements and check for aliens movement mechanics
			for (Alien& alien : aliens)
			{
				alien.draw(alienSprite, window);
				if (alien.update(movePause, aliens))
				{
					moveDown = 1;
				}

				// Check if Aliens have made it past player
				if (alien.getY() >= (p.getY() - PLAYER_HEIGHT))
				{
					reachedPlayer = true;
					break;
				}

				// Check if Player has been Shot
				for (Bullet& bullet : p.getBullets())
				{
					if (alien.checkBulletCollision(bullet))
					{
						score += 10;
					}
				}

				// Moves the ALiens down all as a single segment
				if (moveDown == 1)
				{
					for (Alien& alien2 : aliens)
					{
						alien2.moveDown();
						moveDown = 0;
					}
					moveDown = 0;
				}
			}

			if (reachedPlayer == true)
			{
				break;
			}

			// Randomly decides which alien should shoot based on the random manager
			for (Alien& alien : aliens)
			{
				if (shootChance(randomManager) == 0)
				{
					alien.shoot(alienBullets);
				}
			}

			// Get rid of Dead Aliens
			deadAliens = remove_if(aliens.begin(), aliens.end(), [](const Alien& alien)
				{
					return alien.getDead() == 1;
				});

			movePause = static_cast<unsigned short>(std::max(0, movePause - ALIEN_MOVE_PAUSE_DECREMENT * static_cast<unsigned short>(aliens.end() - deadAliens)));

			aliens.erase(deadAliens, aliens.end());

			// Draws ALien bullets to the screen
			for (const Bullet& bullet : alienBullets)
			{
				alienBulletSprite.setPosition(bullet.x, bullet.y);
				window.draw(alienBulletSprite);
			}


			// Sets the flag that checks if the alient bullet that was hsot has made it offscreen
			for (Bullet& bullet : alienBullets)
			{

				bullet.y += ALIEN_BULLET_SPEED;
				if (SCREEN_HEIGHT <= bullet.y)
				{
					bullet.offScreen = 1;
				}
			}

			// Removes the bullets that have made it offscreen so that I dont have to worry about it slowing down my framerate
			alienBullets.erase(remove_if(alienBullets.begin(), alienBullets.end(), [](const Bullet& bullet)
				{
					return bullet.offScreen == 1;
				}), alienBullets.end());
		}

		// Set UI for Level and Score
		sf::Text t;
		t.setFont(fontTexture);
		t.setString("Level: " + std::to_string(level));
		t.setCharacterSize(72);
		window.draw(t);

		sf::Text s;
		s.setFont(fontTexture);
		s.setString("Score: " + std::to_string(score));
		s.setCharacterSize(72);
		s.setPosition(350, 0);
		window.draw(t);
		window.draw(s);
		window.display();
	}
	return 0;
}