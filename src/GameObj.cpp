#include "GameObj.h"

GameObj::GameObj(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	: m_sprite(sprite), m_animation(m_sprite, size, scale), m_need2BDelete(false)
{
}//end constructor

sf::Sprite& GameObj::getSprite()
{
	return m_sprite;
}//end getSprite

const sf::Sprite& GameObj::getSprite() const
{
	return m_sprite;
}//end getSprite

sf::Vector2f GameObj::getPosition() const
{
	return m_sprite.getPosition();
}//end getPosition

void GameObj::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}//end setPosition

void GameObj::setNeed2BDelete()
{
	m_need2BDelete = true;
}//end setNeed2BDelete

bool GameObj::getNeed2BDelete() const
{
	return m_need2BDelete;
}//end getNeed2BDelete

bool GameObj::getFinishAnimation() const
{
	return m_animation.getFinishAnimation();
}//end getFinishAnimation

void GameObj::updateAnomations()
{
	m_animation.updateAnimations();
}//end updateAnomations

void GameObj::setAnimState(ANIMATION_STATES state)
{
	m_animation.setAnimState(state);
}//end setAnimState

void GameObj::setSpriteSize(sf::Vector2f size)
{
	m_animation.setSpriteSize(size);
}//end setSpriteSize

void GameObj::setFrameEnd(sf::Vector2f frameEnd)
{
	m_animation.setFrameEnd(frameEnd);
}//end setFrameEnd

void GameObj::setJumpFrameEnd(sf::Vector2f jumpFrameEnd)
{
	m_animation.setJumpFrameEnd(jumpFrameEnd);
}//end setJumpFrameEnd
