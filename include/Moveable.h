#pragma once

#include "GameObj.h"
#include "Animation.h"
#include "macros.h"
#include "Sounds.h"
#include <iostream>

class Moveable : public GameObj {
public:
	Moveable(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
	void                setDirection(sf::Vector2f dic);
	const sf::Vector2f& getDirection() const;
	void virtual		draw(sf::RenderWindow& window) override;
	virtual void        updateMovement(float dt) = 0;
	virtual void		update(float dt) override;
	void                updatePhysics(float dt);
	void                move(float dt);
	void                setJump(bool jump);
	sf::Vector2f        getVelocity() const;
	void                setVelocityX(float x);
	void                setVelocityY(float y);
	void                setAcceleration(float ac);
	void                setGravity(float g);
	bool isGravity() const;
	float               distance(sf::Vector2f vec1, sf::Vector2f vec2);
	bool virtual		getDead() const;
	void setDead(bool status);
	void setAbleToJump(bool status);

	bool getAbleToJump() const;

	sf::Clock& getClock();

private:
	void initPhysics();
	sf::Vector2f m_direction;
	sf::Vector2f m_velocity;
	float m_acceleration;
	float m_deccelaration;
	float m_gravity;
	bool m_jumping;
	bool m_ableToJump;
	bool m_dead;
	sf::Clock m_jumpClock;
};