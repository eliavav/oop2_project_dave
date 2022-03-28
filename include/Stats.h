#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "macros.h"
#include "Sounds.h"

enum StatType { GAMES, GAMEOVERS };//games static during game or during gameover
enum StatsKind { SCORES, LEVELS, LIFES, GUNS, TROPHYS, JETS, GAMEOVER };

class Stats {
public:
	Stats();
	void draw(sf::RenderWindow& window);
	void handleSoundStatus(sf::Vector2f location);
	void updateData(sf::Vector2f pos, int score, int level,
		int life, bool trophy, bool gun, bool jet, bool gameover, bool drawSound);
	//-------------------set functions--------------------------
	void setString(std::string str, int data, StatsKind kind);
	void setGameoverStatus(bool status);

private:
	//-------------------private functions--------------------------
	void setGameoverpos(sf::Vector2f pos);
	void setDurinGamePos(sf::Vector2f pos);
	sf::Vector2f getButtonPosition(Button but) const;
	sf::Vector2f getSpritePosition(sf::Sprite sprite) const;
	//-------------------private members----------------------------
	bool m_drawGameover;
	bool m_drawTrophy;
	bool m_drawGun;
	bool m_drawJet;
	bool m_drawSoundStatus;
	bool m_soundStat;

	Button m_score;
	Button m_level;
	Button m_daves;//lives

	sf::Sprite m_trophy;
	sf::Sprite m_gun;
	sf::Sprite m_jet;
	sf::Sprite m_gameover;
	sf::Sprite m_soundStatus;
};