#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "macros.h"

class GameObj {
public:
	GameObj(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
	~GameObj() = default;
	sf::Sprite& getSprite();
	const sf::Sprite& getSprite() const;
	sf::Vector2f getPosition() const;
	virtual void draw(sf::RenderWindow& window) = 0;

	void setPosition(sf::Vector2f pos);

	void setNeed2BDelete();

	bool getNeed2BDelete() const;
	bool getFinishAnimation() const;

	virtual void update(float dt = 0) = 0;
	void updateAnomations();
	void setAnimState(ANIMATION_STATES state);
	void setSpriteSize(sf::Vector2f size);
	void setFrameEnd(sf::Vector2f frameEnd);
	void setJumpFrameEnd(sf::Vector2f jumpFrameEnd);

private:
	sf::Sprite m_sprite;
	Animation m_animation;
	bool m_need2BDelete;
};