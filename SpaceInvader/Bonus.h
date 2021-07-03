#pragma once
#include "Asset.h"
class Bonus : public Asset
{
public :
	enum typ_bonus
	{
		speed = 0,
		attack,
	};

	Bonus(Texture &Text, Vector2f pos, typ_bonus bonus);
	~Bonus();

	void  Update(RenderWindow&) override;
	 bool   onTriggerEnter(Asset* obj) override;

	bool unlock_Next_LevelProj;

	Vector2f boost_speed;

	typ_bonus _typ_bonus;
};

