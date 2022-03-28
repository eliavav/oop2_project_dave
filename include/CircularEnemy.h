#pragma once

#include "Enemy.h"

class CircularEnemy : public Enemy {
public:
	CircularEnemy(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
	virtual void updateMovement(float dt) override;

private:
	sf::Vector2f m_lastPos;
};