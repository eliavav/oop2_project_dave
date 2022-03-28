#include "Textures.h"

Textures::Textures()
{//constructor - load all Textures into the vector

	m_font.loadFromFile("font.ttf");

	m_textures[PLAYER].loadFromFile("Player.png");
	m_textures[WALL].loadFromFile("wall.png");
	m_textures[STONE].loadFromFile("Stone.png");
	m_textures[FIRE].loadFromFile("dynamicFire.png");
	m_textures[DIAMOND].loadFromFile("Diamond.png");
	m_textures[TROPHY].loadFromFile("Trophy.png");
	m_textures[FLAME].loadFromFile("Flame.png");
	m_textures[GUN].loadFromFile("Gun.png");
	m_textures[CIRCENEMY].loadFromFile("CircEnemy.png");
	m_textures[CONSTENEMY].loadFromFile("ConstEnemy.png");
	m_textures[MENU_BACKGROUND].loadFromFile("MenuBackground.png");
	m_textures[PLAYER_BULLET].loadFromFile("Bullet.png");
	m_textures[ENEMY_BULLET].loadFromFile("EnemyBullet.png");
	m_textures[DOOR].loadFromFile("Door.png");
	m_textures[JET].loadFromFile("Jet.png");
	m_textures[GAMEOVER_BACK].loadFromFile("Gameover.png");
	m_textures[GAMEOVERSUCCESS].loadFromFile("GameoverSuccess.png");
	m_textures[DEAD].loadFromFile("Dead.png");
	m_textures[HELP].loadFromFile("help.png");
	m_textures[SOUND_ON].loadFromFile("SoundOn.png");
	m_textures[SOUND_OFF].loadFromFile("SoundOff.png");

}//end constructor 

Textures& Textures::instance()
{//get the single Textures object
	static Textures tex;
	return tex;
}//end instance

const sf::Texture& Textures::getTexture(TexturesType kind)
{//return the texture according to sent simbolIndex
	if (int(kind) >= m_textures.size())
		throw std::out_of_range("getTexture is out of range");
	return m_textures[kind];
}//end getTexture


const sf::Font& Textures::getFont() const
{
	return m_font;
}//end getFont