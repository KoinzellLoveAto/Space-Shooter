#include "Background.h"

Background::Background(Texture &text) : Asset(text)
{
	this->gameObjectName = "background";
	this->sprite.scale(4.5, 4.5);
	
	this->speed_y = 0.5;
	this->speed_x = 0;
	this->elapsedTime = 1;

	this->_type_asset = Asset::e_Background;
}

Background::~Background()
{
}

void Background::Update(RenderWindow& rw)
{
	Vector2f tmp = this->getPosition();
	if (tmp.y >= SCREEN_SIZE)
		this->sprite.setPosition(0, -SCREEN_SIZE);


	this->move(speed_x, speed_y, elapsedTime);
	Asset::Update(rw);
}

bool Background::onTriggerEnter(Asset* obj)
{
	if (obj->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

