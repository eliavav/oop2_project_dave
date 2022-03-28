#include "JetBar.h"

JetBar::JetBar()
{//sets the frame size and num of rectangles
	m_frame.setSize(sf::Vector2f(FRAME_SIZE * numofrec + 5, 50));
	m_frame.setFillColor(sf::Color::Transparent);
	m_frame.setOutlineThickness(3.f);
	m_frame.setOutlineColor(sf::Color::Yellow);

	auto rec = sf::RectangleShape(sf::Vector2f(25, 40));
	rec.setFillColor(sf::Color::White);

	for (auto i = 0; i < numofrec * 2; ++i)
	{
		m_rectangles.push_back(rec);
	}
}//end constructor 

void JetBar::setposition(sf::Vector2f pos)
{
	float x = pos.x - BAR_LOC_CHANGE_X;
	float y = pos.y + BAR_LOC_CHANGE_Y;
	m_frame.setPosition(sf::Vector2f(x, y));
	for (auto& rectangl : m_rectangles)
	{
		rectangl.setPosition(sf::Vector2f(x + 5.f, y + 5.f));
		x += 30.f;
	}
}//end setposition 

void JetBar::draw(sf::RenderWindow& window)
{
	window.draw(m_frame);
	for (auto& rec : m_rectangles)
		window.draw(rec);
}//end draw 

bool JetBar::isEmpty()
{
	return m_rectangles.empty();
}//end isEmpty 

void JetBar::reduce()
{
	if(!m_rectangles.empty())
		m_rectangles.pop_back();
}//end reduce 
