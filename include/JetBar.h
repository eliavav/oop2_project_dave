#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "macros.h"

const auto numofrec = 10;//the time of jet, each half second get a rectangle
const auto FRAME_SIZE = 60;

class JetBar {
public:
	JetBar();
	void setposition(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);
	bool isEmpty();
	void reduce();

private:
	std::vector<sf::RectangleShape> m_rectangles; //each half second get a rectangle
	sf::RectangleShape m_frame;
};
