#include "Jet.h"

Jet::Jet(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	:Static(sprite, size, scale), m_jetTime(10.f)
{
}

float Jet::getJetTime() const
{
	return m_jetTime;
}
