#pragma once

#include "Moveable.h"

class Enemy : public Moveable {
public:
	Enemy(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
private:
};