#pragma once
#include <SFML/Graphics.hpp>

enum TexturesType {
	PLAYER, WALL, STONE, FIRE, DIAMOND, TROPHY, FLAME, GUN,
	CIRCENEMY, CONSTENEMY, MENU_BACKGROUND, PLAYER_BULLET, ENEMY_BULLET,
	DOOR, JET, GAMEOVER_BACK, GAMEOVERSUCCESS, DEAD, HELP, SOUND_ON, SOUND_OFF
};

enum SoundsType { WALK, JUMP, EAT, JET_ACTIVE, FALL, BOOM };

enum ANIMATION_STATES { IDLE, MOVING_LEFT, MOVING_RIGHT, JUMPING, FLYING, ONPLACE, STATIC };

const auto CPLAYER = 'p';
const auto CCRENEMY = 'e';
const auto CCOENEMY = 'c';
const auto CDOOR = 'z';
const auto CWALL = 'w';
const auto CSTONE = 's';
const auto CFIRE = 'f';
const auto CFLAME = 'b';
const auto CWATER = 'h';
const auto CDIAMOND = 'd';
const auto CTROPHY = 't';
const auto CJET = 'j';
const auto CGUN = 'g';

//-----------------Controller Consts-------------------
const auto WINDOW_WIDTH = sf::VideoMode::getFullscreenModes()[0].width;
const auto WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;
const auto BPP = sf::VideoMode::getFullscreenModes()[0].bitsPerPixel;
const auto WINDOW_LONG = 4000;
const auto CUBESIZE = 80.f;

//---------------------Direction consts------------------
const auto LEFT = sf::Vector2f(-1, 0);
const auto RIGHT = sf::Vector2f(1, 0);
const auto UP = sf::Vector2f(0, -1);
const auto DOWN = sf::Vector2f(0, 1);
const auto STILL = sf::Vector2f(0, 0);

//---------------------Button consts---------------------
const auto BUTTON_X = 235.f;
const auto BUTTON_Y = 150.f;
const auto BUTTON_HEIGHT = 6.F;
const auto BUTTON_WIDTH = 13.F;
const auto BUTTON_DISTANCE = 200.f;

//----------------------game data consts----------------
const auto DIAMOND_SCORE = 100;
const auto TROPHY_SCORE = 1000;

const auto ENEMY_DISTANCE = 200.f;
const auto BULLET_DISTANCE = 1000.f;

const auto BAR_LOC = sf::Vector2f(((float)(WINDOW_WIDTH / 3) + 20.f), (float)WINDOW_HEIGHT - 140.f);
const auto BAR_LOC_CHANGE_X = 300.f;
const auto BAR_LOC_CHANGE_Y = 430.f;

const auto NUM_OF_LIVES = 3;

//----------------------moveable consts----------------
auto const MAX_VELOCITY = 70.f;
auto const MIN_VELOCITY = 1.f;
auto const WORLD_GRAVITY = 100.f;
auto const ACCELERATION = 100.f;
auto const DECELERATION = 0.8f;
auto const CIRCULAR_E_ACCELERATION = 80.f;
auto const BULLET_ACCELERATION = 200.f;;

//----------------------Sprites & scales consts----------------

const auto PLAYER_SIZE = sf::Vector2f(40, 50);
const auto PLAYER_SCALE = sf::Vector2f((CUBESIZE - 10.f) / PLAYER_SIZE.x, (CUBESIZE - 10.f) / PLAYER_SIZE.y);
const auto PLAYER_FRAME_END = sf::Vector2f(360, 50);
const auto PLAYER_JUMP_FRAME_END = sf::Vector2f(80, 100);
const auto PLAYER_FLYING_FRAME_END = sf::Vector2f(360, 50);

const auto CIRCENEMY_SIZE = sf::Vector2f(200, 200);
const auto CIRCENEMY_SCALE = sf::Vector2f(CUBESIZE / CIRCENEMY_SIZE.x, CUBESIZE / CIRCENEMY_SIZE.y);
const auto CIRCENEMY_FRAME_END = sf::Vector2f(1000, 0);

const auto CONSTENEMY_SIZE = sf::Vector2f(175, 150);
const auto CONSTENEMY_SCALE = sf::Vector2f(CUBESIZE / CONSTENEMY_SIZE.x, CUBESIZE / CONSTENEMY_SIZE.y);
const auto CONSTENEMY_FRAME_END = sf::Vector2f(525, 0);


const auto DEAD_RECT_SIZE = sf::Vector2f(100, 100);
const auto DEAD_SCALE = sf::Vector2f(CUBESIZE / DEAD_RECT_SIZE.x, CUBESIZE / DEAD_RECT_SIZE.y);
const auto DEAD_SIZE = sf::Vector2f(700, 300);

const auto STONE_SIZE = sf::Vector2f(50, 40);
const auto STONE_SCALE = sf::Vector2f(CUBESIZE / STONE_SIZE.x, CUBESIZE / STONE_SIZE.y);

const auto WALL_SIZE = sf::Vector2f(100, 100);
const auto WALL_SCALE = sf::Vector2f(CUBESIZE / WALL_SIZE.x, CUBESIZE / WALL_SIZE.y);

const auto FIRE_RECT_SIZE = sf::Vector2f(55, 55);
const auto FIRE_SCALE = sf::Vector2f(CUBESIZE / FIRE_RECT_SIZE.x, CUBESIZE / FIRE_RECT_SIZE.y);
const auto FIRE_SIZE = sf::Vector2f(440, 220);

const auto FLAME_RECT_SIZE = sf::Vector2f(112.5, 300);
const auto FLAME_SCALE = sf::Vector2f(CUBESIZE / FLAME_RECT_SIZE.x, CUBESIZE / FLAME_RECT_SIZE.y);
const auto FLAME_SIZE = sf::Vector2f(900, 300);

const auto DIAMOND_SIZE = sf::Vector2f(40, 30);
const auto DIAMOND_SCALE = sf::Vector2f(CUBESIZE / DIAMOND_SIZE.x, CUBESIZE / DIAMOND_SIZE.y);

const auto TROPHY_SIZE = sf::Vector2f(400, 400);
const auto TROPHY_SCALE = sf::Vector2f(CUBESIZE / TROPHY_SIZE.x, CUBESIZE / TROPHY_SIZE.y);

const auto DOOR_SIZE = sf::Vector2f(1200, 1200);
const auto DOOR_SCALE = sf::Vector2f(CUBESIZE / DOOR_SIZE.x, CUBESIZE / DOOR_SIZE.y);

const auto JET_SIZE = sf::Vector2f(200, 200);
const auto JET_SCALE = sf::Vector2f(CUBESIZE / JET_SIZE.x, CUBESIZE / JET_SIZE.y);

const auto GUN_SIZE = sf::Vector2f(65, 40);
const auto GUN_SCALE = sf::Vector2f(CUBESIZE / GUN_SIZE.x, CUBESIZE / GUN_SIZE.y);

const auto PLAYER_BULLET_SIZE = sf::Vector2f(100, 80);
const auto PLAYER_BULLET_SCALE = sf::Vector2f(30.f / PLAYER_BULLET_SIZE.x, 30.f / PLAYER_BULLET_SIZE.y);

const auto BULLET_FRAME_END = sf::Vector2f(0, 0);

const auto ENEMY_BULLET_SIZE = sf::Vector2f(50, 20);
const auto ENEMY_BULLET_SCALE = sf::Vector2f(30.f / ENEMY_BULLET_SIZE.x, 30.f / ENEMY_BULLET_SIZE.y);