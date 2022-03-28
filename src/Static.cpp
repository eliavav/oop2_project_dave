#include "Static.h"

Static::Static(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	:GameObj(sprite, size, scale), m_exists(true)
{//default animation is static = no movement at all
	setAnimState(STATIC);
}//end constructor 

void Static::update(float dt)
{
	updateAnomations();
}//end update

void Static::draw(sf::RenderWindow& window)
{
	if(m_exists)
		window.draw(getSprite());
}//end draw

bool Static::getExistens() const
{
	return m_exists;
}//end getExistens

void Static::setExistens(bool status)
{
	m_exists = status;
}//end setExistens
