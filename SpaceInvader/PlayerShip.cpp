#include "PlayerShip.h"
#include "Game.h"
#include <list>


void PlayerShip::InitStats()
{
	this->stats.current_health = 100;
	this->stats.nbProjectile = 1;
	this->stats.elapsedTime = 1;
	this->stats.speed_X = 0;
	this->stats.speed_Y = 0;
	this->stats.coeffSpeed_X = 2;
	this->stats.coeffSpeed_Y = 2;


}

void PlayerShip::shoot(Asset* obj, short proj)
{
	if (_state_player == e_Dead) return;
	Vector2f tmp = this->getPosition();

	if (proj == 0)
	{
		obj->sprite.scale(0.7, 0.7);
		tmp.x = tmp.x + this->getPixelSprite().x / 2 - 20;
		tmp.y = tmp.y - this->getPixelSprite().y;
	}
	else if (proj == 1)
	{
		obj->sprite.scale(0.3, 0.5);
		tmp.x = tmp.x + this->getPixelSprite().x / 2 - 40;
		tmp.y = tmp.y - this->getPixelSprite().y;
	}
	else if (proj == 2)
	{
		obj->sprite.scale(0.3, 0.5);
		tmp.x = tmp.x + this->getPixelSprite().x / 2 + 5;
		tmp.y = tmp.y - this->getPixelSprite().y;
	}
	obj->setPosition(tmp);

}

bool PlayerShip::onTriggerEnter(Asset* obj)
{
	if (obj->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		if (obj->_type_asset == Asset::e_Projectile)
		{
			Projectile* p = (Projectile*)obj;
			if (p->_teamSide != Projectile::players)
			{
			
				if (get<2>(frameInvulrabilite) == false)
				{
					get<2>(frameInvulrabilite) = true;
					takeDammage(p->dammage);
					cout << "take damamge" << endl;

				}
				else
				{
					cout << "immo" <<endl;
				}
				delete obj;
				return true;
			}
		}
		if (obj->_type_asset == Asset::e_Bonus)
		{
		Bonus* b = (Bonus*)obj;
			if (b->_typ_bonus == Bonus::attack)
			{
				this->_ProjUnlocked.fast = true;
				delete obj;
				return true;
			}
			if (b->_typ_bonus == Bonus::speed)
			{
				get<2>(durationSpeedBoost) = true;
				this->stats.coeffSpeed_X = 3;
				this->stats.coeffSpeed_Y = 3;

				delete obj;
				return true;
			}
		}

	}
	return false;
}

void PlayerShip::Dead()
{
	_state_player = statePlayer::e_Dead;
	this->texture = Texture();
	this->sprite = Sprite();
	
}

void PlayerShip::takeDammage(const float& dammage)
{
	cout << "my life :" << this->stats.current_health << endl;
	this->stats.current_health -= dammage;
	if (this->stats.current_health <= 0)
	{
		Dead();
	}
}



PlayerShip::PlayerShip(Texture& text, num_joueur j) :
	Asset(text),
	_moves{ false, false, false, false, false },
	delayProjNormal{ 0.7,0.7,true },
	delayProjHuge{ 3,3 ,true },
	delayProjFast{ 0.3,0.3,true },
	delayProjUltraFast{ 0.3,0.3,true },
	delayProjSpecial{ 5,5 ,true },
	frameInvulrabilite(1, 1, false),
	_ProjUnlocked{ true,false,false,false,false },
	_num_player(j),
	_state_player(statePlayer::e_Alive),
	_SpeedBoost(false),
	durationSpeedBoost{ 20,20,false }
{
	InitStats();
	this->gameObjectName = "player";
	this->sprite.scale(0.7, 0.7);
	this->sprite.setPosition((SCREEN_SIZE / 2) - this->getPixelSprite().y, SCREEN_SIZE - 200);
	this->_type_asset = Asset::e_PlayerShip;

}

PlayerShip::~PlayerShip()
{

}



void PlayerShip::Update(RenderWindow& rw)
{

	if (_state_player == statePlayer::e_Alive)
	{
		this->stats.speed_X = 0;
		this->stats.speed_Y = 0;

		if (_moves.backward)
			this->stats.speed_Y += 1 * this->stats.coeffSpeed_Y;
		if (_moves.forward)
			this->stats.speed_Y -= 1 * this->stats.coeffSpeed_Y;
		if (_moves.left)
			this->stats.speed_X -= 1 * this->stats.coeffSpeed_X;
		if (_moves.right)
			this->stats.speed_X += 1 * this->stats.coeffSpeed_X;

#pragma region -- TIMER JOUEUR --
		if (get<2>(delayProjNormal) == false)
		{
			get<0>(delayProjNormal) -= 0.01;
			if (get<0>(delayProjNormal) <= 0)
			{
				get<0>(delayProjNormal) = get<1>(delayProjNormal);
				get<2>(delayProjNormal) = true;
			}
		}

		if (get<2>(delayProjFast) == false)
		{
			get<0>(delayProjFast) -= 0.01;
			if (get<0>(delayProjFast) <= 0)
			{
				get<0>(delayProjFast) = get<1>(delayProjFast);
				get<2>(delayProjFast) = true;
			}
		}


		if (get<2>(frameInvulrabilite) == true)
		{
			get<0>(frameInvulrabilite) -= 0.01;
			if (get<0>(frameInvulrabilite) <= 0)
			{
				get<0>(frameInvulrabilite) = get<1>(frameInvulrabilite);
				get<2>(frameInvulrabilite) = false;
			}
		}

		if (get<2>(durationSpeedBoost) == true)
		{
			get<0>(durationSpeedBoost) -= 0.01;
			if (get<0>(durationSpeedBoost) <= 0)
			{
				get<0>(durationSpeedBoost) = get<1>(durationSpeedBoost);
				get<2>(durationSpeedBoost) = false;
				this->stats.coeffSpeed_X = 2;
				this->stats.coeffSpeed_Y = 2;
			}
		}
#pragma endregion -- decompte le timer des joueur dans ce bloc --


		this->move(this->stats.speed_X, this->stats.speed_Y, this->stats.elapsedTime);

		// COLISION FENETRE
		if (this->sprite.getPosition().x <= 0) //Collision Fenetre Gauche
		{
			this->sprite.setPosition(0.f, this->sprite.getPosition().y);
		}
		if (this->sprite.getPosition().x >= rw.getSize().x - this->sprite.getGlobalBounds().width) //Collision Fenetre Droite
		{
			this->sprite.setPosition(rw.getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getPosition().y);
		}
		if (this->sprite.getPosition().y <= 0) //Collision Fentre Haut
		{
			this->sprite.setPosition(this->sprite.getPosition().x, 0.f);
		}
		if (this->sprite.getPosition().y >= rw.getSize().y - this->sprite.getGlobalBounds().height) //Collision Fenetre Bas
		{
			this->sprite.setPosition(this->sprite.getPosition().x, rw.getSize().y - this->sprite.getGlobalBounds().height);
		}


		if (get<2>(frameInvulrabilite) == false)
		{

			Asset::Update(rw);



		}
		else
		{
			// fait clignoté le joueur a la prise de dégat
			countClignotement++;
			if (countClignotement % 5 == 0)
				Asset::Update(rw);
			if (countClignotement > 30)
				countClignotement = 0;
		}
	}
}


