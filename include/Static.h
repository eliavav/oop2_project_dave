#pragma once

#include "GameObj.h"

class Static : public GameObj {
public:
	Static(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
	virtual void update(float dt = 0) override;
	virtual void draw(sf::RenderWindow& window) override;
	bool getExistens() const;
	void setExistens(bool status);

private:
	bool m_exists;//true = display, false = do not display
};