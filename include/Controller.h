#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "CollisionHandling.h"
#include "Menu.h"
#include "Stats.h"
#include <vector>
#include <string>
#include "JetBar.h"
#include "Sounds.h"

const auto FIRSTLEVEL = 1;
enum gameStatus { Failed, Finish };//if game is finish succesfull or died during.

class Controller {
public:
	Controller();
	void run();
private:
	//------------private function-------------------------
	void runGame();
	void draw();
	void handleView();
	void runMenu();
	void menuDuring();
	void runGameoverMenu(gameStatus status);
	void checkLevelFinish();
	void restartLevel();
	void restartGame();
	void handleButtonsPress(ButtonName button);
	void clocksResrtart();
	void help();
	void menuEventHandle(Menu& menuKind);
	void gameEventHandle();
	//------------privat members-------------------------
	sf::RenderWindow m_window;
	std::unique_ptr<Board> m_board;
	Menu m_menu;
	Menu m_duringMenu;
	Menu m_gameoverMenu;
	std::unique_ptr<Stats> m_gameoverStats;
	std::unique_ptr<Stats> m_stats;
	sf::View m_playerView;
	int m_numOfLevel;
	sf::Vector2f m_currentView;
	std::unique_ptr<JetBar> m_bar;
	sf::Sprite m_help;
	bool m_exitMenu;
	bool m_levelended;
	sf::Clock m_move;
	sf::Clock m_enemyShot;
	sf::Clock m_jet;
};