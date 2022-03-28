#pragma once

#include "Static.h"

class Jet : public Static {
public:
	Jet(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
	float getJetTime() const;

private:
	float m_jetTime;
};