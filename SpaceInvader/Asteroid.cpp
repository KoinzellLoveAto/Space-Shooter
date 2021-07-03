#include "Asteroid.h"
#include "Projectile.h"

Asteroid::Asteroid(Texture& text) : Asset(text)
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(RenderWindow&)
{
}

bool Asteroid::onTriggerEnter(Asset* obj)
{
	if (obj->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		if (obj->_type_asset == Asset::e_Projectile)
		{
			Projectile* p = (Projectile*)obj;


				delete obj;
				return true;
			
		}
		

	}
	return false;
}
