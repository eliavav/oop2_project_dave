#include "Player.h"


Player::Player(const sf::Sprite& sprite, sf::Vector2f size, sf::Vector2f scale)
	:Moveable(sprite, size, scale), m_numOfLives(NUM_OF_LIVES), m_score(0), m_gun(false),
	m_playerGotTrophy(false), m_finishLevel(false), m_flying(false), m_jet(false)
{
	m_startPos = getPosition();
	setFrameEnd(PLAYER_FRAME_END);
	setJumpFrameEnd(PLAYER_JUMP_FRAME_END);
}

void Player::updateMovement(float dt)
{
	static bool released = true;
	bool keyPressed = false;//for the sounds - stop sound if nothing pressed
	setAnimState(ANIMATION_STATES::IDLE);
	setDirection(STILL);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		keyPressed = true;
		Sounds::instance().PlaySound(WALK);
		setDirection(LEFT);
		setAnimState(MOVING_LEFT);
		move(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		keyPressed = true;
		Sounds::instance().PlaySound(WALK);
		setDirection(RIGHT);
		setAnimState(MOVING_RIGHT);
		move(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		keyPressed = true;
		setDirection(DOWN);
		move(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (released)
		{
			released = false;
			keyPressed = true;
			if (getAbleToJump() && isGravity())
			{
				setJump(true);
				setAbleToJump(false);
				Sounds::instance().PlaySound(JUMP);
			}
			else
				setJump(false);

			setDirection(UP);
			setAnimState(JUMPING);
			move(dt);
		}
	}
	else
		released = true;
	if (m_flying)
	{
		released = true;
		keyPressed = true;
		setAnimState(FLYING);
		Sounds::instance().PlaySound(JET_ACTIVE);
	}
	if (!keyPressed)
		Sounds::instance().stopPlaying(false);
	if (getClock().getElapsedTime().asSeconds() > 0.35f && !m_flying)
	{
		setGravity(WORLD_GRAVITY);
	}
}//end updateMovement

void Player::playerDied()
{
	--m_numOfLives;
	this->setFlying(false);
	this->setGravity(WORLD_GRAVITY);
	this->setAbleToJump(false);
}//end playerDied


void Player::setGun(bool status)
{
	m_gun = status;
}//end setGun

bool Player::getGun() const
{
	return m_gun;
}//end getGun

void Player::setGotTrophy(bool status)
{
	m_playerGotTrophy = status;
}//end setGotTrophy

bool Player::getGotTrophy() const
{
	return m_playerGotTrophy;
}//end getGotTrophy

void Player::setFinishLevel()
{
	if (m_playerGotTrophy)//player able to finish level only after got trophy
		m_finishLevel = true;
}//end setFinishLevel

bool Player::isLevelFinished() const
{
	return m_finishLevel;
}//end isLevelFinished

bool Player::getJet() const
{
	return m_jet;
}//end getJet

bool Player::getFlying() const
{
	return m_flying;
}
//end getFlying

void Player::setScore(int score)
{
	m_score += score;
}//end setScore

void Player::setJet(bool status)
{
	m_jet = status;
}//end setJet

void Player::setFlying(bool status)
{
	m_flying = status;
}//end setFlying

void Player::setJetTime(float dt)
{
	m_JetTime = dt;
}//end setJetTime

void Player::setLives(int numOfLifes)
{
	m_numOfLives = numOfLifes;
}//end setLives

float Player::getJetTime() const
{
	return m_JetTime;
}//end getJetTime

sf::Vector2f Player::getStartPos() const
{
	return m_startPos;
}//end getStartPos

int Player::getLives() const
{
	return m_numOfLives;
}//end getLives

int Player::getScore() const
{
	return m_score;
}//end getScore
