#include "CircularEnemy.h"

CircularEnemy::CircularEnemy(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	:Enemy(sprite, size, scale), m_lastPos(getPosition())
{//sets the acceleration of the enemy
	setAcceleration(CIRCULAR_E_ACCELERATION);
	setFrameEnd(CIRCENEMY_FRAME_END);
}//end CircularEnemy constructor

void CircularEnemy::updateMovement(float dt)
{//changing direction each const distance
	if (distance(m_lastPos, getPosition()) >= ENEMY_DISTANCE)
	{
		if (getDirection() == UP)
		{
			setDirection(RIGHT);
			setAnimState(MOVING_RIGHT);
		}
		else if (getDirection() == RIGHT)
		{
			setDirection(DOWN);

		}
		else if (getDirection() == DOWN)
		{
			setDirection(LEFT);
			setAnimState(MOVING_LEFT);

		}
		else if (getDirection() == LEFT)
		{
			setDirection(UP);

		}
		m_lastPos = getPosition();
	}
	move(dt);
}//end updateMovement
