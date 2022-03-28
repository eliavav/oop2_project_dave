#include "Stats.h"

Stats::Stats()//stats constructor
	: m_score(100.f, 0, "Score: "), m_level(500.f, 0, "Level: ")
	, m_daves(900.f, 0, "Daves: "), m_drawTrophy(false), m_drawGun(false),
	m_drawJet(false), m_drawGameover(false), m_soundStat(true), m_drawSoundStatus(true)
{
	m_trophy.setTexture(Textures::instance().getTexture(TROPHY));
	m_trophy.setScale(sf::Vector2f((BUTTON_WIDTH + 100.f) / 800, (BUTTON_HEIGHT + 100.f) / 800));
	m_gun.setTexture(Textures::instance().getTexture(GUN));
	m_gun.setScale(sf::Vector2f(1.2, 1.7));
	m_jet.setTexture(Textures::instance().getTexture(JET));
	m_jet.setScale(JET_SCALE);
	m_gameover.setTexture(Textures::instance().getTexture(GAMEOVER_BACK));
	m_gameover.setScale((WINDOW_WIDTH / m_gameover.getGlobalBounds().width) / 1.5,
		(WINDOW_HEIGHT / m_gameover.getGlobalBounds().height) / 1.5);
	m_soundStatus.setTexture(Textures::instance().getTexture(SOUND_ON));
	m_soundStatus.setScale(0.25, 0.25);
}//end stats constructor

void Stats::draw(sf::RenderWindow& window)
{
	if (m_drawTrophy)
		window.draw(m_trophy);
	if (m_drawGun)
		window.draw(m_gun);
	if (m_drawGameover)
		window.draw(m_gameover);
	if (m_drawJet)
		window.draw(m_jet);
	if(m_drawSoundStatus)
		window.draw(m_soundStatus);
	m_score.draw(window);
	m_level.draw(window);
	m_daves.draw(window);
}//end draw

void Stats::setString(std::string str, int data, StatsKind kind)
{
	switch (kind)
	{
	case SCORES:
		str.append(std::to_string(data));//attach int data to the string
		m_level.setText(str);
		break;
	case LEVELS:
		str.append(std::to_string(data));//attach int data to the string
		m_score.setText(str);
		break;
	case LIFES:
		str.append(std::to_string(data));//attach int data to the string
		m_daves.setText(str);
		break;
	}
}//end setString

void Stats::updateData(sf::Vector2f pos, int score, int level, int life, bool trophy, bool gun,
						bool jet, bool gameover, bool drawSound)
{
	setString("Score: ", score, SCORES);
	setString("Level: ", level, LEVELS);
	setString("Daves: ", life, LIFES);
	(trophy) ? m_drawTrophy = true : m_drawTrophy = false;
	(gun) ? m_drawGun = true : m_drawGun = false;
	(jet) ? m_drawJet = true : m_drawJet = false;
	(drawSound) ? m_drawSoundStatus = true : m_drawSoundStatus = false;
	if (gameover)
	{
		m_drawGameover = true;
		setGameoverpos(pos);
	}
	else
		setDurinGamePos(pos);
}//end updateData

void Stats::setGameoverStatus(bool status)
{
	if (status)
		m_gameover.setTexture(Textures::instance().getTexture(GAMEOVERSUCCESS));
	else
		m_gameover.setTexture(Textures::instance().getTexture(GAMEOVER_BACK));
}//end setGameoverStatus

void Stats::handleSoundStatus(sf::Vector2f location)
{
	if (m_soundStatus.getGlobalBounds().contains(location))
	{
		if (!m_soundStat)//if sound on change it to off, and if its on change to on 
		{
			m_soundStatus.setTexture(Textures::instance().getTexture(SOUND_ON));
			m_soundStat = true;
			Sounds::instance().setMute(false);
		}
		else
		{
			m_soundStatus.setTexture(Textures::instance().getTexture(SOUND_OFF));
			m_soundStat = false;
			Sounds::instance().setMute(true);
		}
	}
}//end handleSoundStatus

void Stats::setGameoverpos(sf::Vector2f pos)
{
	m_score.setPosition(sf::Vector2f(pos.x + 350, pos.y - 100));
	m_level.setPosition(sf::Vector2f(pos.x + 350, pos.y));
	m_daves.setPosition(sf::Vector2f(pos.x + 350, pos.y + 100));
	m_gameover.setPosition(pos.x - 400.f, pos.y - 400.f);
}//end setGameoverpos
void Stats::setDurinGamePos(sf::Vector2f pos)
{
	m_score.setPosition(sf::Vector2f(pos.x - 950, 0));
	m_level.setPosition(sf::Vector2f(pos.x - 500.f, 0));
	m_daves.setPosition(sf::Vector2f(pos.x - 50.f, 0));
	m_soundStatus.setPosition(sf::Vector2f(pos.x + 650.f, 10.f));
	m_trophy.setPosition(sf::Vector2f(pos.x + 850.f, 15.f));
	m_gun.setPosition(sf::Vector2f(pos.x + 770.f, 7.f));
	m_jet.setPosition(sf::Vector2f(pos.x - 400.f, pos.y + BAR_LOC_CHANGE_Y - 15.f));
}//end setDurinGamePos

sf::Vector2f Stats::getButtonPosition(Button but) const
{
	return but.getPosition();
}//end getButtonPosition
sf::Vector2f Stats::getSpritePosition(sf::Sprite sprite) const
{
	return sprite.getPosition();
}//end getSpritePosition
