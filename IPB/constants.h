#pragma once
#include "Point.h"

namespace constants
{
	const double PI = 3.14159265358979323846;
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 700;
	const int CHARACTER_WIDTH = 60;
	const int CHARACTER_HEIGHT = 77;
	const int PLANET_WIDTH = 200;
	const int PLANET_HEIGHT = 200;
	const int BUTTON_WIDTH = 300;
	const int STATUS_WIDTH = 5;
	const int STATUS_HEIGHT = 10;
	const int BULLET_WIDTH = 30;
	const int BULLET_HEIGHT = 137;
	const int MISSILE_HEIGHT = 114;
	const int LASER_HEIGHT = 195;
	const int WORMHOLE_WIDTH = 150;
	const int WORMHOLE_HEIGHT = 150;
	const int PLAYER_WIDTH = 36;
	const int PLAYER_HEIGHT = 75;
	const int ENEMY_WIDTH = 93;
	const int ENEMY_HEIGHT = 57;
	const int FADE_SCREEN_BG_WIDTH = 980;
	const int FADE_SCREEN_BG_HEIGHT = 560;

	const Point HEALTH_SPRITE_START_POSITION = {1024, 0};
	const Point FADE_SCREEN_BG_START_POSITION = {1024 + STATUS_WIDTH * 3, 0};
	const Point PLANETS_SPRITE_START_POSITION = {0, 786};
	const Point PLAYER_SPRITE_START_POSITION = {0, 986};
	const Point EXPLOSION_SPRITE_START_POSITION = {0, 1061};
	const Point BUTTONS_SPRITE_START_POSITION = {0, 1157};
	const Point ALPHABETS_SPRITE_START_POSITION = {0, 1322};
	const Point BULLETS_SPRITE_START_POSITION = {0, 1399};
	const Point WORMHOLE_SPRITE_START_POSITION = {0, 1594};
	const Point ENEMY_SPRITE_START_POSITION = {152, 1596};
	enum SCREEN_TYPES
	{
		SPLASH_SCREEN,
		MAIN_MENU_SCREEN,
		LOAD_GAME_SCREEN,
		SELECT_LEVEL_SCREEN,
		BATTLE_SCREEN,
		GAME_OVER_SCREEN,
		SAVE_GAME_SCREEN,
		PAUSE_SCREEN
	};
	enum PLANETS_TYPES
	{
		MERCURY,
		VENUS,
		EARTH,
		MARS,
		JUPITER,
		NEPTUNE,
		URANUS
	};
	enum BULLETS_TYPES
	{
		SIMPLE_BULLET,
		MISSILE,
		LASER
	};
}
