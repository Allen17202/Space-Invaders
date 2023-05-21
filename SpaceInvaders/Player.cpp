#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Alien.h"

Player::Player()
{
	dead = 0;
	x = static_cast<short>(0.5f * (SCREEN_WIDTH - PLAYER_WIDTH));
	Player::y = PLAYER_Y;
	image.loadFromFile("GameItems/Images/ship.png");
	sprite.setTexture(image);
	bulletTexture.loadFromFile("GameItems/Images/missile.png");
	bulletSprite.setTexture(bulletTexture);
}

// Hit Box for Player character
sf::IntRect Player::getHitbox() const
{
	return sf::IntRect(static_cast<int>(x + 0.5f * PLAYER_WIDTH), static_cast<int>(y + 0.3 * PLAYER_HEIGHT), static_cast <int>(0.5 * PLAYER_WIDTH), static_cast <int>(0.8 * PLAYER_HEIGHT));
}

// Draw Player to the screen
void Player::draw(sf::RenderWindow& ship)
{
	sprite.setPosition(x, SCREEN_HEIGHT - 2 * PLAYER_HEIGHT);

	// Draw the ship shooting Bullets
	for (const Bullet& bullet : bullets)
	{
		bulletSprite.setPosition(bullet.x, bullet.y);
		ship.draw(bulletSprite);
	}

	ship.draw(sprite);
}

// Getter for flag for Player Death
bool Player::getDead()
{
	return dead;
}

// Resets the players stats
void Player::reset()
{
	dead = 0;
	bulletReloadTimer = 0;
	bullets.clear();
	x = static_cast<short>(0.5f * (SCREEN_WIDTH - BASE_SIZE));
	y = PLAYER_Y;
}

// Getter for X position of Player
unsigned short Player::getX() const
{
	return x;
}

// Getter for Y position of Player
unsigned short Player::getY() const
{
	return y;
}

// Updates Players Informaion
void Player::update(std::vector<Alien> aliens, std::vector<Bullet>& alienBullets)
{
	std::vector<Bullet>::iterator deadBullets;

	// Check for userInput and move based on it
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		x = std::min<unsigned short>(x + SHIP_MOVEMENT_SPEED, SCREEN_WIDTH - 2 * BASE_SIZE);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		x = std::max<unsigned short>(x - SHIP_MOVEMENT_SPEED, BASE_SIZE);
	}

	// Apples a reload timer to the Player so that they can't spam shots
	if (bulletReloadTimer == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			bulletReloadTimer = BULLET_TIMER_DURATION;
			bullets.push_back({ static_cast<short>(x + BULLET_X_OFFSET), SCREEN_HEIGHT - (BASE_SIZE + BULLET_Y_OFFSET) });
		}

	}
	else
	{
		bulletReloadTimer--;
	}

	// Sets flag of Players bullers that are offscreen to true
	for (Bullet& bullet : bullets)
	{
		bullet.y -= PLAYER_BULLET_SPEED;
		if (-BASE_SIZE >= bullet.y)
		{
			bullet.offScreen = true;
		}
	}

	// Checks if Player has been hit by ALien Bullet, also gets rid of Alien bullet
	for (Bullet& alienBullet : alienBullets)
	{
		if (getHitbox().intersects(alienBullet.get_hitbox()))
		{
			dead = true;
			alienBullet.offScreen = 1;
			break;
		}
	}

	// Removes Offscreen bullets
	std::vector<Bullet>::iterator offscreenBullets = remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet)
		{
			return bullet.offScreen == true;
		});
	bullets.erase(offscreenBullets, bullets.end());
}

// Getter for Player Bullets
std::vector<Bullet>& Player::getBullets()
{
	return bullets;
}
