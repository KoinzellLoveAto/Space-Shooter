#pragma once
#include "Asset.h"

class Asteroid : public Asset
{
public :
	Asteroid(Texture &text);
	~Asteroid();

	void  Update(RenderWindow&) override;
	bool  onTriggerEnter(Asset* obj) override;


};

