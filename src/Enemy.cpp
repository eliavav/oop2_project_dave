#include "Enemy.h"

Enemy::Enemy(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	:Moveable(sprite, size, scale)
{
	setGravity(0);
	setDirection(RIGHT);
	setAnimState(MOVING_RIGHT);
}


