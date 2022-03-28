#include "Menu.h"


Menu::Menu(MenuType type)//Menu constructor
	:m_drawBackground(false)
{
	chooseType(type);
	m_background.setTexture(Textures::instance().getTexture(MENU_BACKGROUND));
	m_background.setScale(WINDOW_WIDTH / m_background.getGlobalBounds().width,
		WINDOW_HEIGHT / m_background.getGlobalBounds().height);

	m_menuBackground.setSize(sf::Vector2f(WINDOW_WIDTH / 4, WINDOW_HEIGHT + 100));
	m_menuBackground.setFillColor(sf::Color(10, 10, 10, 220));
	m_menuBackground.setPosition(sf::Vector2f(100, 0));
}//end menu constructor


void Menu::handleMouse(const sf::Vector2f& location)
{
	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].second.update(location);
}//end handleMouse

void Menu::draw(sf::RenderWindow& window)
{
	if (m_drawBackground)
		window.draw(m_background);
	window.draw(m_menuBackground);
	for (int i = 0; i < m_buttons.size(); ++i)
		m_buttons[i].second.draw(window);
}//end draw

ButtonName Menu::whoIsPressed(const sf::Vector2f& location)
{
	for (int i = 0; i < m_buttons.size(); ++i)
	{
		if (m_buttons[i].second.boundContains(location))
			return m_buttons[i].first;
	}
	return Nothing;
}//end whoIsPressed

void Menu::setstring(Button button, std::string str)
{
	button.setText(str);
}//end setstring

void Menu::updatePosition(const sf::Vector2f& pos)
{
	m_menuBackground.setPosition(pos.x - 80, pos.y + 80);
	for (int i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i].second.setPosition(sf::Vector2f(pos.x, m_buttons[i].second.getPosition().y));
	}
}//end updatePosition

void Menu::setPosition(Button button, const sf::Vector2f& pos)
{
	button.setPosition(sf::Vector2f(pos.x, button.getPosition().y));
}//end setPosition

void Menu::setDrawBackground(bool status)
{
	m_drawBackground = status;
}//end setDrawBackground

sf::Vector2f Menu::getPosition(int place) const
{
	if (place < m_buttons.size())
		return m_buttons[place].second.getPosition();
}//end getPosition

void Menu::chooseType(MenuType type)
{
	switch (type)
	{
	case STARTM:
		executeStartMenu();
		break;
	case DURINGM:
		executeDuringMenu();
		break;
	case GAMEOVERM:
		executeGameovertMenu();
		break;
	};
}//end chooseType
//----------------------------------------------------------------------
//if we want to add new kind of menu we just need to add another execute function, and initialize it to 
//the menu we need
void Menu::executeStartMenu()
{//initialize the menu to be start menu
	m_drawBackground = true;
	auto tempButton = Button(BUTTON_X, BUTTON_Y, "Play");
	m_buttons.emplace_back(buttons(Play, tempButton));
	m_buttons[0].second.setPosition(sf::Vector2f(BUTTON_X, BUTTON_Y));

	tempButton = Button(BUTTON_X, BUTTON_Y, "Help");
	m_buttons.emplace_back(buttons(Help, tempButton));
	m_buttons[1].second.setPosition(sf::Vector2f(BUTTON_X, BUTTON_Y + BUTTON_DISTANCE));

	tempButton = Button(BUTTON_X, BUTTON_Y, "Exit");
	m_buttons.emplace_back(buttons(Exit, tempButton));
	m_buttons[2].second.setPosition(sf::Vector2f(BUTTON_X, BUTTON_Y + BUTTON_DISTANCE + 550));
}//end executeStartMenu 

void Menu::executeDuringMenu()
{//initiliaze the menu to be during Menu
	auto tempButton = Button(BUTTON_X, BUTTON_Y, "Resume");
	m_buttons.emplace_back(buttons(Resume, tempButton));
	m_buttons[0].second.setPosition(sf::Vector2f(BUTTON_X - 60, BUTTON_Y));

	tempButton = Button(BUTTON_X, BUTTON_Y, "Newgame");
	m_buttons.emplace_back(buttons(Newgame, tempButton));
	m_buttons[1].second.setPosition(sf::Vector2f(BUTTON_X - 60, BUTTON_Y + BUTTON_DISTANCE));

	tempButton = Button(BUTTON_X, BUTTON_Y, "Help");
	m_buttons.emplace_back(buttons(Help, tempButton));
	m_buttons[2].second.setPosition(sf::Vector2f(BUTTON_X, BUTTON_Y + (BUTTON_DISTANCE * 2)));

	tempButton = Button(BUTTON_X, BUTTON_Y, "Exit");
	m_buttons.emplace_back(buttons(Exit, tempButton));
	m_buttons[3].second.setPosition(sf::Vector2f(BUTTON_X, BUTTON_Y + BUTTON_DISTANCE + 600));
}//end executeDuringtMenu

void Menu::executeGameovertMenu()
{//initiliaze the menu to be gameover Menu
	auto tempButton = Button(BUTTON_X, BUTTON_Y, "Newgame");
	m_buttons.emplace_back(buttons(Newgame, tempButton));
	m_buttons[0].second.setPosition(sf::Vector2f(BUTTON_X - 60, BUTTON_Y));

	tempButton = Button(BUTTON_X, BUTTON_Y, "Help");
	m_buttons.emplace_back(buttons(Help, tempButton));
	m_buttons[1].second.setPosition(sf::Vector2f(BUTTON_X, BUTTON_Y + (BUTTON_DISTANCE)));

	tempButton = Button(BUTTON_X, BUTTON_Y, "Exit");
	m_buttons.emplace_back(buttons(Exit, tempButton));
	m_buttons[2].second.setPosition(sf::Vector2f(BUTTON_X, BUTTON_Y + BUTTON_DISTANCE + 600));
}//end executeGameovertMenu
