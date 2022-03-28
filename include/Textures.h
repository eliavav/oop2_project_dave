#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "macros.h"

//singleton class
class Textures  {
public:
	~Textures() = default;
	static Textures& instance();
	const sf::Texture& getTexture(TexturesType symbol);
	const sf::Font& getFont() const;

private:
	Textures();
	Textures(const Textures&) = default;
	Textures& operator=(const Textures&) = default;
	std::map <TexturesType, sf::Texture> m_textures;
	sf::Font m_font;
};