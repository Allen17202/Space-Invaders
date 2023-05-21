#pragma once
#include "GlobalGame.h"
#include "Alien.h"
class Player
{
	bool dead;
	unsigned short x;
	unsigned short y = PLAYER_Y;
	sf::Sprite sprite;
	sf::Texture image;
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;
	unsigned char bulletReloadTimer = 0;
	std::vector<Bullet> bullets;

public:
	Player();
	std::vector<Bullet>& getBullets();
	void draw(sf::RenderWindow& ship);
	bool getDead();
	void reset();
	unsigned short getX() const;
	unsigned short getY() const;;
	void update(std::vector<Alien> aliens, std::vector<Bullet>& alienBullets);
	sf::IntRect getHitbox() const;
};