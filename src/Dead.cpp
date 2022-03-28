#include "Dead.h"

Dead::Dead(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	:Static(sprite, size, scale)
{
	setAnimState(ONPLACE);
	setSpriteSize(DEAD_SIZE);
}
