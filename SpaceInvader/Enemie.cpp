#include "Enemie.h"
#include "Projectile.h"
Enemie::Enemie(Texture& text) : Asset(text)
{

}

Enemie::Enemie(Texture& text, typEnemy type, Vector2f pos) :
	Asset(text),
	_typenemy(type),
	delayProjNormal{ 2,2,true },
	delayProjHuge{ 7,7,true },
	delayUltraFast{ 0.7,0.7,true },
	BornePos(50, 1030, true),
	initialPosY(pos.y)

{
	this->stats.speed_X = 1;
	this->stats.speed_Y = 1;
	this->stats.elapsedTime = 1;

	this->stats.current_health = 100;
	this->stats.max_health = 100;
	this->_type_asset = Asset::e_EnemieShip;

	this->setPosition(pos);

	Vector2f origin = this->sprite.getOrigin() + Vector2f(this->getPixelSprite().x / 2, this->getPixelSprite().y / 2);

	switch (this->_typenemy)
	{
	case e_normalShip:
		this->gameObjectName = "normalShip_enemie";
		this->stats.current_health = 100;
		this->stats.max_health = 100;
		break;

	case e_BossShip:
		this->gameObjectName = "BossShip_enemie";
		this->sprite.setOrigin(origin);
		this->stats.current_health = 300;
		this->stats.max_health = 300;
		this->sprite.scale(2, 2);

		break;
	default:
		break;
	}
}

Enemie::~Enemie()
{
}




void Enemie::timerShoot()
{
	get<0>(delayProjNormal) -= 0.01;
	if (get<0>(delayProjNormal) <= 0)
	{
		get<0>(delayProjNormal) = get<1>(delayProjNormal);
		get<2>(delayProjNormal) = true;
	}

	if (_typenemy == e_normalShip) return;

	if (get<2>(delayProjHuge) == false)
	{

		get<0>(delayProjHuge) -= 0.01;
		if (get<0>(delayProjHuge) <= 0)
		{
			get<0>(delayProjHuge) = get<1>(delayProjHuge);
			get<2>(delayProjHuge) = true;

		}
	}

	if (get<2>(delayUltraFast) == false)
	{

		get<0>(delayUltraFast) -= 0.01;
		if (get<0>(delayUltraFast) <= 0)
		{
			get<0>(delayUltraFast) = get<1>(delayUltraFast);
			get<2>(delayUltraFast) = true;

		}
	}
}

bool Enemie::canShoot()
{
	return get<2>(delayProjNormal);
}
// num proj : 0 middle 1 left / 2 right
void Enemie::shoot(Asset* obj, short numProj)
{
	Vector2f tmp = this->getPosition();
	Vector2f origin = this->sprite.getOrigin();;

	switch (_typenemy)
	{
	case Enemie::e_normalShip:
		get<2>(delayProjNormal) = false;
		obj->sprite.scale(0.7, 0.7);

		tmp.x = tmp.x + this->getPixelSprite().x / 2;
		tmp.y = tmp.y + this->getPixelSprite().y + 20;
		obj->setPosition(tmp);
		break;
	case Enemie::e_BossShip:
		switch (numProj)
		{
		case 0:
			if (get<2>(delayProjHuge))
			{
				get<2>(delayProjHuge) = false;
				obj->sprite.scale(1.4, 1.4);
				tmp.x = tmp.x + this->getPixelSprite().x / 2 - 45;
				tmp.y = tmp.y + this->getPixelSprite().y + 50;
				obj->setPosition(tmp);
			}
			break;
		case 1:
			if (get<2>(delayUltraFast))
			{
				// on remet par a false car : on change l'état au deuxieme projectile tiré
				// (oui c'est bizarre)
				obj->sprite.scale(0.5, 1);
				tmp.x = tmp.x + this->getPixelSprite().x / 2 + 25;
				tmp.y = tmp.y + this->getPixelSprite().y + 50;
				obj->setPosition(tmp);
			}
			break;
		case 2:
			if (get<2>(delayUltraFast))
			{
				get<2>(delayUltraFast) = false;
				obj->sprite.scale(0.5, 1);
				tmp.x = tmp.x + this->getPixelSprite().x / 2 -100;
				tmp.y = tmp.y + this->getPixelSprite().y + 40;
				obj->setPosition(tmp);
			}
			break;

		}
		break;
	default:
		break;
	}



}

void Enemie::Update(RenderWindow& rw)
{
	movePatern();
	timerShoot();
	//isTrigger()
	Asset::Update(rw);
}

bool Enemie::isDead()
{


	if (this->stats.current_health <= 0)
	{

		return true;
	}
	return false;
}

bool Enemie::onTriggerEnter(Asset* obj)
{

	if (obj->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		if (obj->_type_asset == Asset::e_Projectile)
		{
			Projectile* p = (Projectile*)obj;
			if (p->_teamSide != Projectile::Enemies)
			{
				this->stats.current_health -= p->dammage;

				cout << "health ennemie : " << this->stats.current_health << endl;
				delete obj;
				return true;
			}
		}
	}
	return false;
}

void Enemie::movePatern()
{


	if (this->sprite.getPosition().y < initialPosY + SCREEN_SIZE)
		this->move(0, 1, stats.elapsedTime);
	else
		this->move(direction * stats.speed_X, 0, stats.elapsedTime);

	if (getPosition().x + getPixelSprite().x < get<0>(BornePos))
	{
		direction = 1;
	}
	else if (getPosition().x + getPixelSprite().x > get<1>(BornePos))
	{
		direction = -1;

	}

}

