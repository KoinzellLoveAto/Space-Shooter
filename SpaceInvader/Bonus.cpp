#include "Bonus.h"

Bonus::Bonus(Texture& text , Vector2f pos, typ_bonus bonus) :
	Asset(text),
	_typ_bonus(bonus)
{
	this->stats.speed_X = 0;
	this->stats.speed_Y = 0.3;
	this->stats.elapsedTime = 1;
	this->_type_asset = Asset::e_Bonus;

	this->setPosition(pos);

	switch (bonus)
	{
	case Bonus::speed:
		boost_speed = Vector2f(0.5, 0.5);
		break;
	case Bonus::attack:
		unlock_Next_LevelProj = true;
		break;
	default:
		break;
	}

}

Bonus::~Bonus()
{
}

void Bonus::Update(RenderWindow& rw)
{
	this->move(this->stats.speed_X, this->stats.speed_Y, this->stats.elapsedTime);
	Asset::Update(rw);
}

bool Bonus::onTriggerEnter(Asset* obj)
{
	if (obj->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		return true;
	}
	return false;
}
