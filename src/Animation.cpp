#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, sf::Vector2f rectsize, sf::Vector2f scale)
	: m_sprite(sprite), m_rectSize(rectsize), m_scale(scale), m_animState(STATIC), m_facingTo(IDLE), m_finishAnimation(false)
{//Animation constructor - load the first rect to the sprite
	m_timer.restart();
	m_currentFrame = sf::IntRect(0, 0, m_rectSize.x, m_rectSize.y);
	m_sprite.setTextureRect(m_currentFrame);
	m_sprite.setScale(m_scale.x, m_scale.y);
}//end Animation constructor

void Animation::setAnimState(ANIMATION_STATES state)
{
	if(state != IDLE && state != JUMPING && state != FLYING)//so when jumping/flying/idle it will face the right direction
		m_facingTo = state;
	m_animState = state;
}//end setAnimState

void Animation::updateAnimations()
{//update the rect of the sprite according to the clock
	if (m_animState == STATIC)//still sprite
		return;
	if (m_animState == ONPLACE)//animation without movement
	{
		if (m_timer.getElapsedTime().asSeconds() >= 0.1f)
		{
			m_currentFrame.left += m_rectSize.x;
			if (m_currentFrame.left > m_spriteSize.x - m_rectSize.x)//reached to the end of the sprite(width)
			{
				m_currentFrame.left = 0;
				m_currentFrame.top += m_rectSize.y;
				if (m_currentFrame.top > m_spriteSize.y - m_rectSize.y)//reached to the end of the sprite(height)
				{
					m_currentFrame.top = 0.f;
					m_finishAnimation = true;//so object that only needed to be draw once would know when to stop
				}
			}
			m_timer.restart();
			m_sprite.setTextureRect(m_currentFrame);
		}
	}
	else if (m_animState == IDLE)
	{
		if (m_timer.getElapsedTime().asSeconds() >= 0.2f)
		{
			m_currentFrame.top = 0.f;
			m_currentFrame.left += m_rectSize.x;
			if (m_currentFrame.left > 160.f)
				m_currentFrame.left = 0;

			m_timer.restart();
			m_sprite.setTextureRect(m_currentFrame);
		}
	}
	else if (m_animState == MOVING_RIGHT)
	{
		if (m_timer.getElapsedTime().asSeconds() >= 0.1f)
		{
			m_currentFrame.top = m_frameEnd.y;
			m_currentFrame.left += m_rectSize.x;
			if (m_currentFrame.left > m_frameEnd.x)
				m_currentFrame.left = 0;

			m_timer.restart();
			m_sprite.setTextureRect(m_currentFrame);
		}
		m_sprite.setScale(m_scale.x, m_scale.y);
		m_sprite.setOrigin(0.f, 0.f);
	}
	else if (m_animState == MOVING_LEFT)
	{
		if (m_timer.getElapsedTime().asSeconds() >= 0.1f)
		{
			m_currentFrame.top = m_frameEnd.y;
			m_currentFrame.left += m_rectSize.x;
			if (m_currentFrame.left > m_frameEnd.x)
				m_currentFrame.left = 0;

			m_timer.restart();
			m_sprite.setTextureRect(m_currentFrame);
		}

		m_sprite.setScale(-m_scale.x, m_scale.y);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / m_scale.x, m_scale.y);
	}
	else if (m_animState == JUMPING)
	{
		if (m_timer.getElapsedTime().asSeconds() >= 0.2f)
		{
			m_currentFrame.top = m_jumpFrameEnd.y;
			m_currentFrame.left += m_rectSize.x;
			if (m_currentFrame.left > m_jumpFrameEnd.x)
				m_currentFrame.left = 0;

			m_timer.restart();
			m_sprite.setTextureRect(m_currentFrame);

			if (m_facingTo == MOVING_RIGHT)//so the character will face the right direction 
			{
				m_sprite.setScale(m_scale.x, m_scale.y);
				m_sprite.setOrigin(0.f, 0.f);
			}
			else
			{
				m_sprite.setScale(-m_scale.x, m_scale.y);
				m_sprite.setOrigin(m_sprite.getGlobalBounds().width / m_scale.x, m_scale.y);
			}
		}
	}
	else if (m_animState == FLYING)
	{
		if (m_timer.getElapsedTime().asSeconds() >= 0.2f)
		{
			m_currentFrame.top = 150;
			m_currentFrame.left += m_rectSize.x;
			if (m_currentFrame.left > 240.f)
				m_currentFrame.left = 0;

			m_timer.restart();
			m_sprite.setTextureRect(m_currentFrame);

			if (m_facingTo == MOVING_RIGHT)//so the character will face the right direction 
			{
				m_sprite.setScale(m_scale.x, m_scale.y);
				m_sprite.setOrigin(0.f, 0.f);
			}
			else
			{
				m_sprite.setScale(-m_scale.x, m_scale.y);
				m_sprite.setOrigin(m_sprite.getGlobalBounds().width / m_scale.x, m_scale.y);
			}
		}
	}
}//end updateAnimations

void Animation::setSpriteSize(sf::Vector2f size)
{
	m_spriteSize = size;
}//end setSpriteSize

void Animation::setFrameEnd(sf::Vector2f frameEnd)
{
	m_frameEnd = frameEnd;
}//end setFrameEnd

void Animation::setJumpFrameEnd(sf::Vector2f jumpFrameEnd)
{
	m_jumpFrameEnd = jumpFrameEnd;
}//end setJumpFrameEnd

bool Animation::getFinishAnimation() const
{
	return m_finishAnimation;
}//end getFinishAnimation


