#include "Projectile.h"


Projectile::Projectile(Texture& text, typeProjectile typeproj, team _team) :
	Asset(text),
	_teamSide(_team),
	_typeProjectile(typeproj)
{

	this->stats.elapsedTime = 1;
	this->stats.speed_X = 0;
	this->stats.speed_Y = 2.5;
	this->gameObjectName = "projectiles";
	this->_type_asset = Asset::e_Projectile;
	
	Vector2f origin;
	switch (typeproj)
	{
	case normal:
		this->dammage = 10;
		break;
	case fast:
		this->dammage = 5;
		break;
	case Huge:
		this->dammage = 30;
		origin = this->sprite.getOrigin() + Vector2f(this->getPixelSprite().x /2, this->getPixelSprite().y / 2);
		this->sprite.setOrigin(origin);
	default:
		this->dammage = 1;
		break;
	}

	switch (_team)
	{
	case Projectile::players:
		break;
	case Projectile::Enemies:
		this->sprite.rotate(180);
		break;
	default:
		break;
	}
	
}

Projectile::~Projectile()
{
	Asset::~Asset();
}

void Projectile::Update(RenderWindow& rw)
{
	
	if (this->_typeProjectile == Huge)
	{

		this->sprite.rotate(2);
	}


	switch (_teamSide)
	{
	case players:
		this->move(this->stats.speed_X, -1 * this->stats.speed_Y, this->stats.elapsedTime);
		break;
	case Enemies:
		this->move(this->stats.speed_X, 1 * this->stats.speed_Y, this->stats.elapsedTime);
		break;
	}
	Asset::Update(rw);
}

bool Projectile::onTriggerEnter(Asset* obj)
{
	if (obj->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

