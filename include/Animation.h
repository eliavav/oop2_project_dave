#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"


class Animation {
public:
	Animation(sf::Sprite& sprite, sf::Vector2f rectsize, sf::Vector2f scale);
	void updateAnimations();

	void setAnimState(ANIMATION_STATES state);
	void setSpriteSize(sf::Vector2f size);
	void setFrameEnd(sf::Vector2f frameEnd);
	void setJumpFrameEnd(sf::Vector2f jumpFrameEnd);
	bool getFinishAnimation() const;


private:
	sf::Clock m_timer;
	ANIMATION_STATES m_animState;
	ANIMATION_STATES m_facingTo;//to which direction the figure is facing
	sf::IntRect m_currentFrame;

	sf::Vector2f m_rectSize;//the size of each part of the sprite sheet
	sf::Vector2f m_scale;
	sf::Vector2f m_frameEnd;//left & right
	sf::Vector2f m_jumpFrameEnd;//left & right
	sf::Vector2f m_spriteSize;//the size of the whole sprite sheet

	bool m_finishAnimation;

	sf::Sprite& m_sprite;

};