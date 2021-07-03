#include "Asset.h"
#include "Game.h"

Asset::Asset(Texture& text) : texture(text)
{

	//	this->texture = text;

	this->sprite.setTexture(text);
	//this->sprite.setPosition(50, 50);
	Game::list_Asset.push_back(this);
	this->stats.max_health = this->stats.current_health;
}




Asset::~Asset()
{
 	int index = 0;

	for (auto& it : Game::list_Asset)
	{
		if (it == this) {

		    Game::list_Asset.erase(Game::list_Asset.begin() + index);

			continue;
		}
		index++;
	}

}

void Asset::setPosition(Vector2f position)
{
	this->sprite.setPosition(position);
}

void Asset::move(float speed_X, float speed_Y, float ElapsedTime)
{
	this->sprite.move(speed_X * ElapsedTime, speed_Y * ElapsedTime);
}

Vector2f Asset::getPosition()
{
	return this->sprite.getPosition();
}

bool Asset::killWhenOutOfScreen()
{
	Vector2f pos = getPosition();

	if (pos.x < 0 || pos.y < 0 || pos.x > SCREEN_SIZE || pos.y > SCREEN_SIZE)
	{
		delete this;

		return true;

	}
	return false;
}

void Asset::Update(RenderWindow& window)
{

	window.draw(this->sprite);
	//cout << this->gameObjectName << endl;


}


Vector2u Asset::getPixelSprite()
{
	return this->texture.getSize();
}

bool Asset::onTriggerEnter(Asset* obj)
{
	return false;
}


