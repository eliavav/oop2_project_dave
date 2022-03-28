#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "Textures.h"
#include "macros.h"
#include "Static.h"
#include "Player.h"
#include "Wall.h"
#include "Fire.h"
#include "Stone.h"
#include "Diamond.h"
#include "Trophy.h"
#include "CollisionHandling.h"
#include "Flame.h"
#include "Gun.h"
#include "Bullet.h"
#include "CircularEnemy.h"
#include "Door.h"
#include "Jet.h"
#include "JetBar.h"
#include "Dead.h"
#include "ConstEnemy.h"
#include "Enemy.h"

const auto NUMOFLEVELPLACE = 5;

class Controller;

class Board {
public:
	Board();
	bool    loadLevel(int numOfLevel, bool loadFile);
	bool    loadLevelFromFile(int numOfLevel);
	void    draw(sf::RenderWindow& window);
	void    restartLevel();
	void    update(float dt = 0);
	Player& getPlayer();
	void    playerShoot(const sf::Event& event);
	void    enemyShoot(sf::Clock& clock);
	void    addDeads();
	void    deleteNeed2BDeleteObjects();
	void    playerJet(const sf::Event& event, sf::Clock& clock);
	void    updateJetTime(sf::Clock& clock, JetBar& bar, sf::Vector2f pos);
	bool    hasDeadObjEnded();
	void    handleCollisions();
	void    clearVectors();

	sf::Sprite createSprite(TexturesType type, sf::Vector2f objectIndex);

private:

	std::ifstream                         m_file;
	sf::RectangleShape                    m_backGroundRec;
	std::unique_ptr <Player>              m_player;
	std::vector <std::unique_ptr<Static>> m_static;
	std::vector <std::unique_ptr<Enemy>>  m_enemies;
	std::vector <std::unique_ptr<Bullet>> m_bullets;
	std::vector <std::vector<char>>       m_levelBoard;//to load the level once, and than we will be able to restart level from vector
	std::vector <std::unique_ptr<Dead>>   m_deadObj;
};

