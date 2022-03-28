#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "macros.h"
#include "Collision.h"

#include "Player.h"
#include "Wall.h"
#include "Stone.h"
#include "Fire.h"
#include "Flame.h"
#include "Gun.h"
#include "Door.h"
#include "Trophy.h"
#include "Bullet.h"
#include "Diamond.h"
#include "Enemy.h"
#include "CircularEnemy.h"
#include "ConstEnemy.h"
#include "Jet.h"


namespace // anonymous namespace — the standard way to make function "static"
{
	template <typename objRef1, typename objRef2>
	sf::Vector2f collisionDirection(objRef1 first, objRef2 second)
	{//check the direction of the collision

		auto firstBounds = first.getSprite().getGlobalBounds();
		auto secondBounds = second.getSprite().getGlobalBounds();

		float object1_bottom = first.getPosition().y + firstBounds.height;
		float object2_bottom = second.getPosition().y + secondBounds.height;
		float object1_right = first.getPosition().x + firstBounds.width;
		float object2_right = second.getPosition().x + secondBounds.width;

		float b_collision = object2_bottom - first.getPosition().y;
		float t_collision = object1_bottom - second.getPosition().y;
		float l_collision = object1_right - second.getPosition().x;
		float r_collision = object2_right - first.getPosition().x;


		if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
			return DOWN;
		if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
			return UP;
		if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
			return LEFT;
		if (r_collision < l_collision && r_collision < t_collision  && r_collision < b_collision)
			return RIGHT;
	}//end collisionDirection

	// primary collision-processing functions
	void playerWall(GameObj& playerobj, GameObj& wallobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		Wall& wall = dynamic_cast<Wall&>(wallobj);

		auto playerBounds = player.getSprite().getGlobalBounds();
		auto wallBounds = wall.getSprite().getGlobalBounds();

		if(f.width > f.height)
			if (player.getPosition().y > wall.getPosition().y)
			{
				if (f.width > f.height + 8.f && !player.getFlying())
					player.setGravity(WORLD_GRAVITY);
				player.setPosition(sf::Vector2f(player.getPosition().x, wall.getPosition().y + wall.getSprite().getGlobalBounds().height));

			}
			else
			{
				if (player.isGravity())
					player.setAbleToJump(true);
				player.setPosition(sf::Vector2f(player.getPosition().x, wall.getPosition().y - player.getSprite().getGlobalBounds().height));
			}
		else
			if (player.getPosition().x > wall.getPosition().x)
				player.setPosition(sf::Vector2f(wall.getPosition().x + wall.getSprite().getGlobalBounds().width, player.getPosition().y));
			else
				player.setPosition(sf::Vector2f(wall.getPosition().x - player.getSprite().getGlobalBounds().width, player.getPosition().y));
	}//end playerWall


	void playerStone(GameObj& playerobj, GameObj& stoneobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		Stone& stone = dynamic_cast<Stone&>(stoneobj);

		if (f.width > f.height)
			if (player.getPosition().y > stone.getPosition().y)
			{
				if (f.width > f.height + 8.f && !player.getFlying())
					player.setGravity(WORLD_GRAVITY);
				player.setPosition(sf::Vector2f(player.getPosition().x, stone.getPosition().y + stone.getSprite().getGlobalBounds().height));

			}
			else
			{
				if (player.isGravity())
					player.setAbleToJump(true);
				player.setPosition(sf::Vector2f(player.getPosition().x, stone.getPosition().y - player.getSprite().getGlobalBounds().height));
			}
		else
			if (player.getPosition().x > stone.getPosition().x)
				player.setPosition(sf::Vector2f(stone.getPosition().x + stone.getSprite().getGlobalBounds().width, player.getPosition().y));
			else
				player.setPosition(sf::Vector2f(stone.getPosition().x - player.getSprite().getGlobalBounds().width, player.getPosition().y));
	}//end playerStone

	void playerFire(GameObj& playerobj, GameObj& fireobj, sf::FloatRect& f)
	{
		Fire& fire = dynamic_cast<Fire&>(fireobj);
		Player& player = dynamic_cast<Player&>(playerobj);
		if (Collision::PixelPerfectTest(player.getSprite(), fire.getSprite()))
		{
			player.setDead(true);
			Sounds::instance().PlaySound(BOOM);
		}
	}//end playerFire

	void playerFlame(GameObj& playerobj, GameObj& flameobj, sf::FloatRect& f)
	{
		Flame& flame = dynamic_cast<Flame&>(flameobj);
		Player& player = dynamic_cast<Player&>(playerobj);
		if (Collision::PixelPerfectTest(player.getSprite(), flame.getSprite()))
		{
			player.setDead(true);
			Sounds::instance().PlaySound(BOOM);
		}
	}//end playerFlame

	void playerGun(GameObj& playerobj, GameObj& gunobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		Gun& gun = dynamic_cast<Gun&>(gunobj);
		player.setGun(true);
		gun.setExistens(false);
	}//end playerGun

	void playerTrophy(GameObj& playerobj, GameObj& trophyobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		Trophy& trophy = dynamic_cast<Trophy&>(trophyobj);
		if (trophy.getExistens())
		{
			player.setGotTrophy(true);
			player.setScore(TROPHY_SCORE);
			trophy.setExistens(false);
		}
	}//end playerTrophy

	void playerDoor(GameObj& playerobj, GameObj& doorobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		player.setFinishLevel();
	}//end playerDoor

	void playerBullet(GameObj& playerobj, GameObj& bulletobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		Bullet& bullet = dynamic_cast<Bullet&>(bulletobj);
		if (bullet.getBulletKind() == PLAYER_BULLET)
			return;
		if (Collision::PixelPerfectTest(player.getSprite(), bullet.getSprite()))
		{
			player.setDead(true);
			Sounds::instance().PlaySound(BOOM);
		}
	}//end playerBullet

	void playerJet(GameObj& playerobj, GameObj& jetobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		Jet& jet = dynamic_cast<Jet&>(jetobj);
		if (jet.getExistens())
		{
			player.setJet(true);
			player.setJetTime(jet.getJetTime());
			jet.setExistens(false);
		}
	}//end playerJet

	void playerEnemy(GameObj& playerobj, GameObj& enemyobj, sf::FloatRect& f)
	{
		Enemy& enemy = dynamic_cast<Enemy&>(enemyobj);
		Player& player = dynamic_cast<Player&>(playerobj);
		if (Collision::PixelPerfectTest(player.getSprite(), enemy.getSprite()))
		{
			enemy.setDead(true);
			player.setDead(true);
			Sounds::instance().PlaySound(BOOM);
		}
	}//end playerEnemy

	void enemyBullet(GameObj& enemyobj, GameObj& bulletobj, sf::FloatRect& f)
	{
		Bullet& bullet = dynamic_cast<Bullet&>(bulletobj);
		Enemy& enemy = dynamic_cast<Enemy&>(enemyobj);
		if (bullet.getBulletKind() == ENEMY_BULLET)
			return;
		bullet.setNeed2BDelete();
		enemy.setDead(true);
		Sounds::instance().PlaySound(BOOM);
	}//end enemyBullet

	void playerDiamond(GameObj& playerobj, GameObj& diamondobj, sf::FloatRect& f)
	{
		Player& player = dynamic_cast<Player&>(playerobj);
		Diamond& diamond = dynamic_cast<Diamond&>(diamondobj);
		if (diamond.getExistens())
		{
			player.setScore(DIAMOND_SCORE);
			diamond.setExistens(false);
			Sounds::instance().PlaySound(EAT);

		}
	}//end playerDiamond

	void bulletWall(GameObj& bulletobj, GameObj& wallobj, sf::FloatRect& f)
	{
		Bullet& bullet = dynamic_cast<Bullet&>(bulletobj);
		Wall& wall = dynamic_cast<Wall&>(wallobj);
		if (Collision::PixelPerfectTest(bullet.getSprite(), wall.getSprite()))
			bullet.setNeed2BDelete();
	}//end bulletWall

	void bulletStone(GameObj& bulletobj, GameObj& stoneobj, sf::FloatRect& f)
	{
		Bullet& bullet = dynamic_cast<Bullet&>(bulletobj);
		Stone& stone = dynamic_cast<Stone&>(stoneobj);
		if (Collision::PixelPerfectTest(bullet.getSprite(), stone.getSprite()))
			bullet.setNeed2BDelete();
	}//end bulletWall

	void enemyWall(GameObj& enemyobj, GameObj& wallobj, sf::FloatRect& f)
	{
		Enemy& enemy = dynamic_cast<Enemy&>(enemyobj);
		Wall& wall = dynamic_cast<Wall&>(wallobj);
		if (enemy.getDirection() == LEFT)
		{
			enemy.setPosition(sf::Vector2f(wall.getPosition().x + wall.getSprite().getGlobalBounds().width + 5.f, enemy.getPosition().y));
			enemy.setDirection(RIGHT);
			enemy.setVelocityX(0.f);
		}
		else
		{
			enemy.setPosition(sf::Vector2f(wall.getPosition().x - enemy.getSprite().getGlobalBounds().width - 5.f, enemy.getPosition().y));
			enemy.setDirection(LEFT);
			enemy.setVelocityX(0.f);
		}
		
	}//end enemyWall

	void enemyStone(GameObj& enemyobj, GameObj& stoneobj, sf::FloatRect& f)
	{
		Enemy& enemy = dynamic_cast<Enemy&>(enemyobj);
		if (enemy.getDirection() == LEFT)
		{
			enemy.setDirection(RIGHT);
			enemy.setVelocityX(10.f);
		}
		else
		{
			enemy.setDirection(LEFT);
			enemy.setVelocityX(-10.f);
		}
	}//end enemyStone

	using HitFunctionPtr = void (*)(GameObj&, GameObj&, sf::FloatRect&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Player), typeid(Wall))] = &playerWall;
		phm[Key(typeid(Player), typeid(Stone))] = &playerStone;
		phm[Key(typeid(Player), typeid(Fire))] = &playerFire;
		phm[Key(typeid(Player), typeid(Flame))] = &playerFlame;
		phm[Key(typeid(Player), typeid(Gun))] = &playerGun;
		phm[Key(typeid(Player), typeid(Trophy))] = &playerTrophy;
		phm[Key(typeid(Player), typeid(Door))] = &playerDoor;
		phm[Key(typeid(Player), typeid(Diamond))] = &playerDiamond;
		phm[Key(typeid(Player), typeid(Bullet))] = &playerBullet;
		phm[Key(typeid(CircularEnemy), typeid(Bullet))] = &enemyBullet;
		phm[Key(typeid(ConstEnemy), typeid(Bullet))] = &enemyBullet;
		phm[Key(typeid(ConstEnemy), typeid(Wall))] = &enemyWall;
		phm[Key(typeid(ConstEnemy), typeid(Stone))] = &enemyStone;
		phm[Key(typeid(Player), typeid(CircularEnemy))] = &playerEnemy;
		phm[Key(typeid(Player), typeid(ConstEnemy))] = &playerEnemy;
		phm[Key(typeid(Bullet), typeid(Wall))] = &bulletWall;
		phm[Key(typeid(Bullet), typeid(Stone))] = &bulletStone;
		phm[Key(typeid(Player), typeid(Jet))] = &playerJet;

		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

void processCollision(GameObj& object1, GameObj& object2, sf::FloatRect& f)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (phf)
	{
		phf(object1, object2, f);
	}
}



