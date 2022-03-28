#pragma once

#include "Enemy.h"

class ConstEnemy : public Enemy {
public:
	ConstEnemy(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
	virtual void updateMovement(float dt) override;

private:
};