#pragma once

#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include <iostream>
#include "Sounds.h"

class Player : public Moveable {
public:
	Player(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale);
	virtual void updateMovement(float dt) override;
	void playerDied();

	//---------set functions------------------------
	void setGun(bool status);
	void setGotTrophy(bool status);
	void setFinishLevel();
	void setScore(int score);
	void setJet(bool status);
	void setFlying(bool status);
	void setJetTime(float dt);
	void setLives(int numOfLifes);
	//---------get functions------------------------
	bool getGun() const;
	bool getGotTrophy()const;
	bool isLevelFinished() const;
	bool getJet() const;
	bool getFlying() const;
	int getLives() const;
	int getScore() const;
	float getJetTime() const;
	sf::Vector2f getStartPos() const;

private:
	int m_numOfLives;//daves
	int m_score;
	bool m_gun;
	bool m_playerGotTrophy;
	bool m_finishLevel;
	bool m_jet;
	bool m_flying;
	float m_JetTime;
	sf::Vector2f m_startPos;
};