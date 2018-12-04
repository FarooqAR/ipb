#include "pch.h"
#include "constants.h"
#include "Player.h"
#include "Game.h"
#include <cmath>

Player::Player(SDL_Renderer* gRenderer, LTexture* imageSpriteSheet, int initialX, int initialY, float Angle)
{
	this->SetPosition(initialX, initialY);
	this->angle = Angle;
	this->objTexture = imageSpriteSheet;
	this->weapon = Game::GetInstance()->GetUnitFactory()->CreateWeapon(40, constants::SIMPLE_BULLET, 30);
 	this->SetDelay(-1);
	this->renderer = gRenderer;
	this->width = constants::PLAYER_WIDTH;
	this->height = constants::PLAYER_HEIGHT;
	this->health = 100;
	this->fuel = 100;
	this->oxygen = 100;
	this->shipCurrentClipIndex = 0;
	for (int i = 0; i < 11; i++)
	{
		shipSpriteClips[i] = {
			constants::PLAYER_SPRITE_START_POSITION.x + this->width * i,
			constants::PLAYER_SPRITE_START_POSITION.y,
			this->width,
			this->height
		};
	}
}

Player::~Player()
{
	delete weapon;
}

void Player::Render()
{
	this->objTexture->RenderTexture(
		position.x,
		position.y,
		renderer,
		&shipSpriteClips[this->shipCurrentClipIndex],
		SDL_FLIP_NONE,
		this->angle,
		nullptr,
		scale,
		scale,
		false
	);
}

Bullet* Player::Shoot(SDL_Renderer* gRenderer, LTexture* imagesSpriteSheet)
{
	return weapon->Fire(gRenderer, imagesSpriteSheet, this->position.x, this->position.y, this->angle);
}

void Player::SetShipCurrentClipIndex(int i)
{
	this->shipCurrentClipIndex = i;
}
void Player::ChangeShipCurrentClipIndex()
{
	if (shipCurrentClipIndex > 3 && shipCurrentClipIndex < 8)
		shipCurrentClipIndex++;
	else
		shipCurrentClipIndex = 4;
}
void Player::SetHealth(float health)
{
	if (this->health > 0 && this->health <= 100)
		this->health = health;
	else
	{
		this->health = 0;
	}
	if (this->health == 0)
		this->alive = false;
}

void Player::SetOxygen(float oxygen)
{
	if (this->oxygen > 0 && this->oxygen <= 100)
		this->oxygen = oxygen;
	else
	{
		this->oxygen = 0;
		this->alive = false;
	}
}

void Player::SetFuel(float fuel)
{
	if (this->fuel > 0 && this->fuel <= 100)
		this->fuel = fuel;
	else
	{
		this->fuel = 0;
		this->alive = false;
	}
}

void Player::SetAmmo(int bullets)
{
	weapon->SetAmmo(bullets);
}

void Player::SetDelay(int time)
{
	if (time >= 0)
		shootDelay = time;
	else
		shootDelay = 0;
}

void Player::SetWeapon(Weapon* weapon)
{
	this->weapon = weapon;
}


//--Getters

float Player::GetHealth()
{
	return health;
}
float Player::GetOxygen()
{
	return oxygen;
}

float Player::GetFuel()
{
	return fuel;
}

int Player::GetCurrentClipIndex()
{
	return shipCurrentClipIndex;
}

bool Player::GetIsThrusting()
{
	return isThrusting;
}

void Player::SetIsThrusting(bool b)
{
	isThrusting = b;
}
int Player::GetX()
{
	return position.x;
}

int Player::GetY()
{
	return position.y;
}

string Player::GetWeaponName()
{

	return weapon->GetWeaponName();
}

int Player::GetDelay()
{
	return shootDelay;
}

int Player::GetAmmo()
{
	return weapon->GetAmmo();
}


Weapon* Player::GetWeapon()
{
	return weapon;
}
void Player::SetWeaponType(int weaponType)
{
	weapon->SetWeaponType(weaponType);
}
