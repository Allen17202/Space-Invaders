#include "Alien.h"
#include <iostream>

Alien::Alien(unsigned short alienX, unsigned short alienY) :
	x(alienX), y(alienY), direction(0), moveTimer(0), dead(0)
{
}

// Draws an Alien to the screen
void Alien::draw(sf::Sprite sprite, sf::RenderWindow& alienShip)
{
	sprite.setPosition(x, y);
	alienShip.draw(sprite);

}

// Update Enemy mechanics
bool Alien::update(unsigned short movePause, std::vector<Alien>& aliens)
{
	// Flag lets me know whether or not I need to move down
	bool flag = 0;
	// Movetime limits ALiens moveement spped
	if (moveTimer == 0)
	{
		// Allows aliens to move faster based on remaining number of aliens
		moveTimer = ALIEN_MOVE_PAUSE_START;
		if (aliens.size() <= 10)
		{
			moveTimer = movePause;
		}
		else
		{
			moveTimer = ALIEN_MOVE_PAUSE_START;
		}

		// Moves Alien
		if (direction == 0)
		{
			flag = (x >= (SCREEN_WIDTH - ALIEN_WIDTH_TOTAL));
			if (aliens.size() < 5)
			{
				x += ALIEN_MOVEMENT_SPEED - movePause;
			}
			else
			{
				x += ALIEN_MOVEMENT_SPEED;
			}

		}
		else
		{
			flag = (x <= ALIEN_WIDTH);
			if (aliens.size() < 5)
			{
				x -= ALIEN_MOVEMENT_SPEED - movePause;
			}
			else
			{
				x -= ALIEN_MOVEMENT_SPEED;
			}
		}
	}
	else
	{
		moveTimer--;
	}

	return flag;
}

// Move a single Alien downward
void Alien::moveDown()
{
	direction = 1 - direction;
	y += ALIEN_HEIGHT;
}

// Add a Alien bullet to vector to keep track 
void Alien::shoot(std::vector<Bullet>& alienBullets)
{
	alienBullets.push_back(Bullet((x + (ALIEN_WIDTH / 2)), (y + (ALIEN_HEIGHT))));
}

// Check if Alien got shot by Player
bool Alien::checkBulletCollision(Bullet& bullet)
{
	if (dead == 0 && bullet.offScreen == 0 && get_hitbox().intersects(bullet.get_hitbox()))
	{
		dead = 1;
		bullet.offScreen = 1;
		return true;
	}
	return false;
}

// Getter for Alien X Position
unsigned short Alien::getX() const
{
	return x;
}

// Getter for Alien Y Position
unsigned short Alien::getY() const
{
	return y;
}

// Getter for death state of Alien
unsigned short Alien::getDead() const
{
	return dead;
}

// Getter for Alien Hitbox
sf::IntRect Alien::get_hitbox() const
{
	return sf::IntRect(static_cast<int>(x + 0.125f * ALIEN_WIDTH), static_cast<int>(y + 0.125 * ALIEN_HEIGHT), static_cast <int>(0.75 * ALIEN_WIDTH), static_cast <int>(0.75 * ALIEN_HEIGHT));
}

