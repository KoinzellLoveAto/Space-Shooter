#pragma once
#include "Asset.h"

class Projectile : public Asset
{
public :

	enum team
	{
		players = 0,
		Enemies
	};

	enum typeProjectile
	{
		normal = 0,
		fast,
		ultraFast,
		Huge,
		special
	
	};

	team _teamSide;
	typeProjectile _typeProjectile;

	unsigned short  dammage;


	Projectile(Texture& text, typeProjectile typeproj, team _team);
	~Projectile();
	void  Update(RenderWindow&) override;
	bool   onTriggerEnter(Asset* obj) override;





};

