#include "Button.h"

Button::Button(float x, float y, const std::string& text)
{
	m_text.setFont(Textures::instance().getFont());
	m_buttonState = BTN_IDLE;

	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setSize(sf::Vector2f(BUTTON_WIDTH + 250.f, BUTTON_HEIGHT + 75.f));
	m_shape.setFillColor(sf::Color(70, 70, 70, 0));
	m_shape.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Transparent);

	m_text.setString(text);
	m_text.setFillColor(sf::Color(200, 200, 200, 200));
	m_text.setCharacterSize(60);
	m_text.setPosition(
		m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f) - m_text.getGlobalBounds().width / 2.f,
		m_shape.getPosition().y
	);

	m_textIdleColor = sf::Color(200, 200, 200, 200);
	m_textHoverColor = sf::Color(255, 255, 255, 255);
	m_textActiveColor = sf::Color(20, 20, 20, 50);

	m_idleColor = sf::Color(70, 70, 70, 0);
	m_hoverColor = sf::Color(150, 150, 150, 0);
	m_activeColor = sf::Color(20, 20, 20, 0);

	m_outlineIdleColor = sf::Color::Transparent;
	m_outlineHoverColor = sf::Color::Transparent;
	m_outlineActiveColor = sf::Color::Transparent;
}
Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (m_buttonState == BTN_ACTIVE)
		return true;
	return false;
}

//const short unsigned& Button::getKind() const
//{
//	return m_kind;
//}

const bool Button::boundContains(sf::Vector2f location)
{
	return m_shape.getGlobalBounds().contains(location);
}

void Button::setText(const std::string text)
{
	m_text.setString(text);
}

void Button::setPosition(sf::Vector2f pos)
{
	m_shape.setPosition(pos);
	m_text.setPosition(pos);
}

void Button::setSize(sf::Vector2f size)
{
	m_shape.setSize(size);
}

void Button::setCharacterSize(unsigned int size)
{
	m_text.setCharacterSize(size);
}

//void Button::setKind(const short unsigned id)
//{
//}

void Button::update(const sf::Vector2f& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	m_buttonState = BTN_IDLE;

	//Hover
	if (m_shape.getGlobalBounds().contains(mousePosWindow))
	{
		m_buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttonState = BTN_ACTIVE;
		}
	}

	switch (m_buttonState)
	{
	case BTN_IDLE:
		m_shape.setFillColor(m_idleColor);
		m_text.setFillColor(m_textIdleColor);
		m_shape.setOutlineColor(m_outlineIdleColor);
		break;

	case BTN_HOVER:
		m_shape.setFillColor(m_hoverColor);
		m_text.setFillColor(m_textHoverColor);
		m_shape.setOutlineColor(m_outlineHoverColor);
		break;

	case BTN_ACTIVE:
		m_shape.setFillColor(m_activeColor);
		m_text.setFillColor(m_textActiveColor);
		m_shape.setOutlineColor(m_outlineActiveColor);
		break;

		//default:
		//	m_shape.setFillColor(sf::Color::Red);
		//	m_text.setFillColor(sf::Color::Blue);
		//	m_shape.setOutlineColor(sf::Color::Green);
		//	break;
	}
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
	window.draw(m_text);
}

sf::Vector2f Button::getPosition() const
{
	return m_shape.getPosition();
}


