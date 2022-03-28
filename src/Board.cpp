#include "Board.h"
#include "Controller.h"

Board::Board()
{
	loadLevel(FIRSTLEVEL, true);
}//end board constructor

bool Board::loadLevelFromFile(int numOfLevel)
{//load the level into char vector for easy restoration of the level - if needed
	m_levelBoard.clear();//to clear the previous level
	std::string fileName = "level#.txt";
	fileName[NUMOFLEVELPLACE] = numOfLevel + '0';//change the text file number, every new load
									//each new level goes up in the number to the next 
	m_file.open(fileName);
	if (!m_file.is_open())
		return false;
	for (std::string line; std::getline(m_file, line);)
	{
		std::vector<char>  temp;//to read each line separately
		for (int k = 0; k < line.size(); k++)
		{
			temp.push_back(line[k]);
		}
		m_levelBoard.push_back(temp);
	}
	m_file.close();
	return true;
}//end loadLevelFromFile

bool Board::loadLevel(int numOfLevel, bool loadFile)
{//initiate all board members according to the char vector, gets Boolean argument to know if need to initiate the char vector first
	if (loadFile)
		if (!loadLevelFromFile(numOfLevel))
			return false;

	for (auto i = 0; i < m_levelBoard.size(); ++i)//build the SFML representation from the board representation
	{
		for (auto j = 0; j < m_levelBoard[i].size(); ++j)//creating all objects---------------
		{
			sf::Vector2f objectIndex(j, i);//x = j, y = i
			char Symbol = m_levelBoard[i][j];
			switch (Symbol)
			{
			case CPLAYER:
				m_player = std::make_unique<Player>(createSprite(PLAYER, objectIndex), PLAYER_SIZE, PLAYER_SCALE);
				break;
			case CCRENEMY:
				m_enemies.emplace_back(std::make_unique<CircularEnemy>(createSprite(CIRCENEMY, objectIndex), CIRCENEMY_SIZE, CIRCENEMY_SCALE));
				break;
			case CCOENEMY:
				m_enemies.emplace_back(std::make_unique<ConstEnemy>(createSprite(CONSTENEMY, objectIndex), CONSTENEMY_SIZE, CONSTENEMY_SCALE));
				break;
			case CWALL:
				m_static.emplace_back(std::make_unique<Wall>(createSprite(WALL, objectIndex), WALL_SIZE, WALL_SCALE));
				break;
			case CSTONE:
				m_static.emplace_back(std::make_unique<Stone>(createSprite(STONE, objectIndex), STONE_SIZE, STONE_SCALE));
				break;
			case CFIRE:
				m_static.emplace_back(std::make_unique<Fire>(createSprite(FIRE, objectIndex), FIRE_RECT_SIZE, FIRE_SCALE));
				break;
			case CFLAME:
				m_static.emplace_back(std::make_unique<Flame>(createSprite(FLAME, objectIndex), FLAME_RECT_SIZE, FLAME_SCALE));
				break;
			case CDIAMOND:
				m_static.emplace_back(std::make_unique<Diamond>(createSprite(DIAMOND, objectIndex), DIAMOND_SIZE, DIAMOND_SCALE));
				break;
			case CTROPHY:
				m_static.emplace_back(std::make_unique<Trophy>(createSprite(TROPHY, objectIndex), TROPHY_SIZE, TROPHY_SCALE));
				break;
			case CDOOR:
				m_static.emplace_back(std::make_unique<Door>(createSprite(DOOR, objectIndex), DOOR_SIZE, DOOR_SCALE));
				break;
			case CJET:
				m_static.emplace_back(std::make_unique<Jet>(createSprite(JET, objectIndex), JET_SIZE, JET_SCALE));
				break;
			case CGUN:
				m_static.emplace_back(std::make_unique<Gun>(createSprite(GUN, objectIndex), GUN_SIZE, GUN_SCALE));
				break;
			}
		}
	}
	return true;
}//end loadLevel


template <typename FwdIt, typename FzdIt, typename Fn>
void for_each_pair(FwdIt begin1, FwdIt end1, FzdIt begin2, FzdIt end2, Fn fn)
{//template function checking each object from the first iterator sent, collision with all second iterator sent
	for (; begin1 != end1; ++begin1)
	{
		auto it = begin1;
		for (auto second2 = begin2; second2 != end2; ++second2)
			fn(*begin1, *second2);
	}
}//end for_each_pair

template <typename unique, typename FzdIt, typename Fn>
void for_each_pair_with_one(unique one, FzdIt begin2, FzdIt end2, Fn fn)
{//template function checking one object collision with iterator
	for (auto second2 = begin2; second2 != end2; ++second2)
		fn(one, *second2);
}


bool collide(GameObj& a, GameObj& b, sf::FloatRect& f)
{
	if (a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds(), f))
		return true;
	return false;
}//end collide


void Board::restartLevel()
{
	m_player->setDead(false);
	m_bullets.clear();
	m_player->setPosition(m_player->getStartPos());

}//end restartLevel

sf::Sprite Board::createSprite(TexturesType type, sf::Vector2f objectIndex)
{//creating a sprite with TexturesType and position
	auto sprite = sf::Sprite(Textures::instance().getTexture(type));
	sprite.setPosition(objectIndex.x * CUBESIZE, objectIndex.y * CUBESIZE);
	return sprite;
}//end createSprite


void Board::update(float dt)
{//update all movement(movable) and animation(movable/static)
	for (auto& staticobj : m_static)
		staticobj->update();

	for (auto& enemy : m_enemies)
		enemy->update(dt);

	for (auto& bullet : m_bullets)
		bullet->update(dt);

	m_player->update(dt);

	for (auto& dead : m_deadObj)
		dead->update();
}//end update

Player& Board::getPlayer()
{
	return *(m_player.get());
}//end getPlayer

void Board::playerShoot(const sf::Event& event)
{//shooting a bullet if the player can do so
	if (event.key.code == sf::Keyboard::Space && m_player->getGun())
	{
		for (const auto& bullet : m_bullets)//so the player could shoot only one bullet at a time
		{
			if (bullet->getBulletKind() == PLAYER_BULLET)
				return;
		}
		m_bullets.emplace_back(std::make_unique<Bullet>(createSprite(PLAYER_BULLET, sf::Vector2f(m_player->getPosition().x / CUBESIZE, m_player->getPosition().y / CUBESIZE)),
			PLAYER_BULLET_SIZE, PLAYER_BULLET_SCALE, PLAYER_BULLET));
		//set the bullet direction according to the player direction
		(m_player->getSprite().getScale().x < 0) ? m_bullets.back()->setDirection(LEFT) : m_bullets.back()->setDirection(RIGHT);
	}
}//end playerShoot

void Board::enemyShoot(sf::Clock& clock)
{//making the enemies shoot a bullet according to the clock
	if (clock.getElapsedTime().asSeconds() > 2.f)
	{
		clock.restart();
		for (auto i = 0; i < m_enemies.size(); ++i)
		{
			auto enemy = m_enemies[i].get();
			m_bullets.emplace_back(std::make_unique<Bullet>(createSprite(ENEMY_BULLET, sf::Vector2f(enemy->getPosition().x / CUBESIZE, enemy->getPosition().y / CUBESIZE)),
				ENEMY_BULLET_SIZE, ENEMY_BULLET_SCALE, ENEMY_BULLET));
			//set the bullet direction according to the player location
			(enemy->getPosition().x >= m_player->getPosition().x) ? m_bullets.back()->setDirection(LEFT) : m_bullets.back()->setDirection(RIGHT);
		}
	}
}//end enemyShoot

void Board::addDeads()
{//adding deadobj if enemy/player had died
	for (const auto& enemy : m_enemies)
	{
		if (!enemy->getDead())
			continue;
		m_deadObj.emplace_back(std::make_unique<Dead>(createSprite(DEAD, sf::Vector2f(enemy->getPosition().x / CUBESIZE, enemy->getPosition().y / CUBESIZE)), DEAD_RECT_SIZE, DEAD_SCALE));
	}

	if (m_player->getDead())
		m_deadObj.emplace_back(std::make_unique<Dead>(createSprite(DEAD, sf::Vector2f(m_player->getPosition().x / CUBESIZE, m_player->getPosition().y / CUBESIZE)), DEAD_RECT_SIZE, DEAD_SCALE));
}//end addDeads

bool Board::hasDeadObjEnded()
{//checking if no dead objects are exists - return true, else return false
	bool ended = true;
	if (m_deadObj.empty())
		return true;
	else
	{
		for (auto i = 0; i < m_deadObj.size(); ++i)
		{
			if (!m_deadObj[i]->getFinishAnimation())
				ended = false;
			else
				m_deadObj.erase(m_deadObj.begin() + i);//remove dead object if it's animation ended
		}
	}
	return ended;
}//end hasDeadObjEnded

void Board::deleteNeed2BDeleteObjects()
{//delete enemies/bullets that needed to be delete
	auto checkDelete1 = [](auto const& del) -> bool {return del->getDead(); };

	m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), checkDelete1), m_enemies.end());

	auto checkDelete2 = [](auto const& x) -> bool
	{
		if (x->distance(x->getStartPos(), x->getPosition()) >= BULLET_DISTANCE || x->getNeed2BDelete())
			return true;
		else
			return false;
	};
	m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), checkDelete2), m_bullets.end());
}//end deleteNeed2BDeleteObjects

void Board::playerJet(const sf::Event& event, sf::Clock& clock)
{//start/stop player jet
	if (event.key.code == sf::Keyboard::LControl && m_player->getJet())
	{
		if (!m_player->getFlying())//so start
		{
			clock.restart();
			m_player->setFlying(true);
			m_player->setGravity(0.f);
		}
		else//stop
		{
			m_player->setFlying(false);
			m_player->setGravity(75.f);
			m_player->setAbleToJump(false);//so the player couldn't jump until it hits the ground
		}
	}
}//end playerJet

void Board::updateJetTime(sf::Clock& clock, JetBar& bar, sf::Vector2f pos)
{//updating the player remaining jet time
	static float time;
	if (m_player->getFlying())
	{
		auto dt = clock.restart().asSeconds();

		auto jetTime = m_player->getJetTime() - dt;

		m_player->setJetTime(jetTime);

		time += dt;
		bar.setposition(pos);
		if (time >= 0.5f)
		{
			bar.reduce();
			time = 0;
		}
		if (m_player->getJetTime() <= 0)
		{
			m_player->setJet(false);
			m_player->setFlying(false);
			m_player->setGravity(75.f);
			m_player->setAbleToJump(false);
			bar.reduce();
		}
	}
}//end updateJetTime

void Board::handleCollisions()
{//check collision of board objects
	static sf::FloatRect f;
	for_each_pair(m_enemies.begin(), m_enemies.end(), m_static.begin(), m_static.end(),
		[](auto& a, auto& b) {//enemies vs statics
		if (collide(*a, *b, f))
			processCollision(*a, *b, f);
	});

	for_each_pair_with_one(m_player.get(), m_enemies.begin(), m_enemies.end(),
		[](auto& a, auto& b) {//check player vs moveables
		if (collide(*a, *b, f))
			processCollision(*a, *b, f);
	});

	for_each_pair_with_one(m_player.get(), m_static.begin(), m_static.end(),
		[](auto& a, auto& b) {//check player vs static
		if (collide(*a, *b, f))
			processCollision(*a, *b, f);
	});

	for_each_pair_with_one(m_player.get(), m_bullets.begin(), m_bullets.end(),
		[](auto& a, auto& b) {//check player vs bullets
		if (collide(*a, *b, f))
			processCollision(*a, *b, f);
	});

	for_each_pair(m_enemies.begin(), m_enemies.end(), m_bullets.begin(), m_bullets.end(),
		[](auto& a, auto& b) {//check enemies vs bullets
		if (collide(*a, *b, f))
			processCollision(*a, *b, f);
	});

	for_each_pair(m_bullets.begin(), m_bullets.end(), m_static.begin(), m_static.end(),
		[](auto& a, auto& b) {//check bullets vs static
		if (collide(*a, *b, f))
			processCollision(*a, *b, f);
	});
}//end handleCollisions

void Board::clearVectors()
{
	m_bullets.clear();
	m_enemies.clear();
	m_static.clear();
}//end clearVectors

void Board::draw(sf::RenderWindow& window)
{
	for (auto& staticobj : m_static)
		staticobj->draw(window);

	for (auto& moveableobj : m_enemies)
		moveableobj->draw(window);

	for (auto& bullet : m_bullets)
		bullet->draw(window);

	for (auto& dead : m_deadObj)
		dead->draw(window);

	if (!m_player->getDead())
		m_player->draw(window);
}//end draw