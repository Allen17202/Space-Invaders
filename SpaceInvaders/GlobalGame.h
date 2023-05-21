#pragma once
#include <cmath>
#include <chrono>

constexpr unsigned short SCREEN_WIDTH = 1600;
constexpr unsigned short SCREEN_HEIGHT = 1014;
constexpr unsigned short BASE_SIZE = 84;
constexpr unsigned short SHIP_MOVEMENT_SPEED = 3;
constexpr unsigned short ALIEN_MOVEMENT_SPEED = 2;
constexpr unsigned short PLAYER_BULLET_SPEED = 2;
constexpr unsigned short SHIP_X_OFFSET = 4;
constexpr unsigned short BULLET_X_OFFSET = 37;
constexpr unsigned short BULLET_Y_OFFSET = 75;
constexpr unsigned short BULLET_TIMER_DURATION = 100;
constexpr unsigned short PLAYER_X = 800;
constexpr unsigned short PLAYER_Y = 850;
constexpr unsigned short PLAYER_WIDTH = 84;
constexpr unsigned short PLAYER_HEIGHT = 92;
constexpr unsigned short ALIEN_WIDTH_OFFSET = 40;
constexpr unsigned short ALIEN_HEIGHT_OFFSET = 50;
constexpr unsigned short ALIEN_WIDTH = 63;
constexpr unsigned short ALIEN_HEIGHT = 45;
constexpr unsigned short BULLET_WIDTH = 63;
constexpr unsigned short BULLET_HEIGHT = 45;
constexpr unsigned short ALIEN_COLS = 8;
constexpr unsigned short ALIEN_ROWS = 6;
constexpr unsigned short ALIEN_MOVE_PAUSE = 2;
constexpr unsigned short ALIEN_MOVE_PAUSE_START = 3;
constexpr unsigned short ENEMY_HIT_TIMER_DURATION = 2;
constexpr unsigned short ALIEN_TYPES = 1;
constexpr unsigned short ALIEN_MOVE_PAUSE_DECREMENT = 2;
constexpr unsigned short ALIEN_BULLET_SPEED = 2;
constexpr unsigned short ALIEN_BULLET_CHANCE_MIN = 1024;
constexpr unsigned short ALIEN_BULLET_CHANCE = 4096;
constexpr unsigned short ALIEN_SHOOT_CHANCE_INCREASE = 64;
constexpr unsigned short ALIEN_WIDTH_TOTAL = 100;


constexpr std::chrono::microseconds FRAMES(5000);

struct Bullet
{
	short x;
	short y;
	bool offScreen{};

	sf::IntRect get_hitbox() const
	{
		return sf::IntRect(static_cast<int>(x + 0.125f * BULLET_WIDTH), static_cast<int>(y + 0.125 * BULLET_HEIGHT), static_cast <int>(0.75 * BULLET_WIDTH), static_cast <int>(0.75 * BULLET_HEIGHT));
	}
};
