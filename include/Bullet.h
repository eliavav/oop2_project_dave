#pragma once

#include "Moveable.h"

class Bullet : public Moveable {
public:
	Bullet(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale, short bulletKind);
	virtual void updateMovement(float dt) override;
	sf::Vector2f getStartPos() const;
	short        getBulletKind() const;

private:
	sf::Vector2f m_startPos;
	short m_bulletKind;//enemy || player
};