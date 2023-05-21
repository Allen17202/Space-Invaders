#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "GlobalGame.h"
class Alien
{
	unsigned short x;
	unsigned short y;
	unsigned short direction;
	unsigned short moveTimer;
	bool dead;

public:
	Alien(unsigned short alienX, unsigned short alienY);
	void draw(sf::Sprite sprite, sf::RenderWindow& alienShip);
	bool update(unsigned short movePause, std::vector<Alien>& aliens);
	void moveDown();
	void shoot(std::vector<Bullet>& alienBullets);
	bool checkBulletCollision(Bullet& bullet);
	unsigned short getX() const;
	unsigned short getY() const;
	unsigned short getDead() const;
	sf::IntRect get_hitbox() const;
};