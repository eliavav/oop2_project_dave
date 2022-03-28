#include "Bullet.h"

Bullet::Bullet(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale, short bulletKind)
	:Moveable(sprite, size, scale), m_bulletKind(bulletKind)
{//sets the gravity and acceleration of the bullet
	setGravity(0);
	setAcceleration(BULLET_ACCELERATION);
	m_startPos = getPosition();
	setFrameEnd(BULLET_FRAME_END);
}//end bullet constructor

void Bullet::updateMovement(float dt)
{
	(getDirection() == LEFT) ? setAnimState(MOVING_LEFT) : setAnimState(MOVING_RIGHT);
	move(dt);
}//end updateMovement

sf::Vector2f Bullet::getStartPos() const
{
	return m_startPos;
}//end getStartPos

short Bullet::getBulletKind() const
{
	return m_bulletKind;
}//end getBulletKind
