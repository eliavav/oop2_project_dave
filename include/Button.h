#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "macros.h"
#include "Textures.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button {

public:
	Button(float x, float y, const std::string& text);
	~Button();

	const bool isPressed() const;
	const bool boundContains(sf::Vector2f location);
	void setText(const std::string text);
	void setPosition(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setCharacterSize(unsigned int size);
	void update(const sf::Vector2f& mousePosWindow);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;



private:
	short unsigned m_buttonState;

	sf::RectangleShape m_shape;
	sf::Text m_text;

	sf::Color m_textIdleColor;
	sf::Color m_textHoverColor;
	sf::Color m_textActiveColor;

	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	sf::Color m_activeColor;

	sf::Color m_outlineIdleColor;
	sf::Color m_outlineHoverColor;
	sf::Color m_outlineActiveColor;


};