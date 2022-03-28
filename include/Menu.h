#pragma once
#include <SFML/Graphics.hpp>
#include "textures.h"
#include "macros.h"
#include "Button.h"
#include <vector>
#include <map>
#include <string>
#include <memory>


enum ButtonName { Play, Exit, Help, Resume, Newgame, Gameover, Nothing };
enum MenuType { STARTM, DURINGM, GAMEOVERM };
enum overMenu { GameOver, Level, Score };

class Menu {
public:
	Menu(MenuType type);
	void handleMouse(const sf::Vector2f& location);
	void draw(sf::RenderWindow& window);//draw the open screen
	ButtonName whoIsPressed(const sf::Vector2f& location);
	//-------------------set functions--------------------------
	void setstring(Button button, std::string str);
	void updatePosition(const sf::Vector2f& pos);
	void setPosition(Button button, const sf::Vector2f& pos);
	void setDrawBackground(bool status);
	//-------------------get functions--------------------------
	sf::Vector2f getPosition(int place) const;

private:
	//-------------------private functions---------------------------
	void chooseType(MenuType type);
	void executeStartMenu();
	void executeDuringMenu();
	void executeGameovertMenu();
	//-------------------private members-----------------------------
	sf::RectangleShape m_menuBackground;//menu background(the gray buttons background)
	sf::Sprite m_background;//all screen background
	bool m_drawBackground;
	typedef std::pair<ButtonName, Button> buttons;
	std::vector<buttons> m_buttons;
};

