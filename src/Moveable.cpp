#include "Moveable.h"

Moveable::Moveable(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	: GameObj(sprite, size, scale), m_jumping(false), m_dead(false)
{
	initPhysics();
}//end constructor

void Moveable::setDirection(sf::Vector2f dic)
{
	m_direction = dic;
}//end setDirection

const sf::Vector2f& Moveable::getDirection() const
{
	return m_direction;
}//end getDirection

void Moveable::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}//end draw

void Moveable::setJump(bool jump)
{
	m_jumping = jump;
}//end setJump

sf::Vector2f Moveable::getVelocity() const
{
	return m_velocity;
}//end getVelocity

void Moveable::setVelocityX(float x)
{
	m_velocity.x = x;
}//end setVelocityX

void Moveable::setVelocityY(float y)
{
	m_velocity.y = y;
}//end setVelocityY

void Moveable::setAcceleration(float ac)
{
	m_acceleration = ac;
}//end setAcceleration

void Moveable::setGravity(float g)
{
	m_gravity = g;
}//end setGravity

bool Moveable::isGravity() const
{
	return m_gravity > 0.f;
}//end isGravity


float Moveable::distance(sf::Vector2f vec1, sf::Vector2f vec2)
{//calculate distance between 2 points
	return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}//end distance

bool Moveable::getDead() const
{
	return m_dead;
}//end getDead

void Moveable::setDead(bool status)
{
	m_dead = status;
}
void Moveable::setAbleToJump(bool status)
{
	m_ableToJump = status;
}
bool Moveable::getAbleToJump() const
{
	return m_ableToJump;
}
sf::Clock& Moveable::getClock()
{
	return m_jumpClock;
}
//end setDead

void Moveable::move(float dt)
{
	m_velocity.x += m_acceleration * m_direction.x * dt;

	if (m_gravity == 0.f)//for the enemies
	{
		m_velocity.y += m_acceleration * m_direction.y * dt;
	}

	if (m_jumping)//for the player
	{
		m_jumpClock.restart();
		setGravity(-150.f);
		m_jumping = false;
		setAbleToJump(false);
	}
}//end move

void Moveable::initPhysics()
{
	m_acceleration = ACCELERATION;
	m_deccelaration = DECELERATION;
	m_gravity = WORLD_GRAVITY;
}//end initPhysics

void Moveable::update(float dt)
{
	updateMovement(dt);
	updateAnomations();
	updatePhysics(dt);
}//end update

void Moveable::updatePhysics(float dt)
{
	m_velocity.y += m_gravity * dt;

	m_velocity *= m_deccelaration;

	if(std::fabsf(m_velocity.x) < MIN_VELOCITY)
		m_velocity.x = 0.f;

	getSprite().move(m_velocity);
}//end updatePhysics
