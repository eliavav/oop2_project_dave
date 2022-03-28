#include "ConstEnemy.h"

ConstEnemy::ConstEnemy(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	:Enemy(sprite, size, scale)
{
	setFrameEnd(CONSTENEMY_FRAME_END);
}//end CircularEnemy constructor

void ConstEnemy::updateMovement(float dt)
{//movement according to collision - only update animation direction
	if(getDirection() == RIGHT)
		setAnimState(MOVING_RIGHT);
	else
		setAnimState(MOVING_LEFT);
	move(dt);
}//end updateMovement
