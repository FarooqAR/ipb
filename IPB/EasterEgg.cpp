#include "pch.h"
#include "EasterEgg.h"
#include "constants.h"
#include "Player.h"
#include "Weapon.h"
#include "LTexture.h"

//Constructors
EasterEgg::EasterEgg()
{	
}

EasterEgg::EasterEgg(SDL_Renderer* gRenderer, LTexture* imagesSpriteSheet, int Type)
{
	this->renderer = gRenderer;
	disappear = false;
	this->objTexture = imagesSpriteSheet;
	this->type = Type;

	//updates width, height and scale according to the easteregg type
	if (type == 0)
	{
		this->width = constants::FOOD_WIDTH;
		this->height = constants::FOOD_HEIGHT;
		this->scale = 0.12;
	}
	else if (type == 1)
	{
		this->width = constants::FUELTANK_WIDTH;
		this->height = constants::FUELTANK_WIDTH;
		this->scale = 0.34;
	}
	else if (type == 2)
	{
		this->width = constants::ASTRONAUT_WIDTH;
		this->height = constants::ASTRONAUT_HEIGHT;
		this->scale = 0.60;
	}
	else if (type == 3)
	{
		this->width = constants::LAUNCHER_WIDTH;
		this->height = constants::LAUNCHER_HEIGHT;
		this->scale = 0.65;
	}
}

//Destructor
EasterEgg::~EasterEgg()
{	
	delete objTexture;
}


//Controls the movement of the easteregg 
void EasterEgg::move()
{
	angle = angle - 0.6;

	//rate at which they disappear
	if (type ==  2 || type == 3)
	{
		scale = scale - 0.0003 / scale;
	}
	else
	{
		scale = scale - 0.00001 / scale;
	}

	//scale = 0 implies that the egg has disappeared and the player has lost the ability to collect it
	if (scale <= 0)
	{
		alive = false;
		disappear = true;
	}
}

//implements the powerup once collected
void EasterEgg::HasCollected(Player * player)
{
	if (!disappear)
	{
		if (type == constants::HEALTH)
		{
			player->setHealth(100);
		}

		else if (type == constants::FUEL)
		{
			player->setFuel(100);
		}

		else if (type == constants::OXYGEN)
		{
			player->setOxygen(100);
		}

		else if (type == constants::WEAPON)
		{
			//randomly chooses between the three weapon types
			int weapontype = rand() % 3;
			if (weapontype == 0)
			{
				player->SetWeapon(new Weapon( 20, 0, 45));
			}
			else if (weapontype == 1)
			{
				player->SetWeapon(new Weapon(20, 1, 45));
			}
			else if (weapontype == 2)
			{
				player->SetWeapon(new Weapon( 20, 2, 45));

			}
			//increases players ammo
			player->SetAmmo(player->GetAmmo() + 20);
		}
	}
}