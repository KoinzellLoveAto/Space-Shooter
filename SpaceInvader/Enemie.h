#pragma once
#include "Asset.h"

class Enemie : public Asset
{
public :

	
	enum typEnemy
	{
		e_normalShip = 0,
		e_BossShip
	};




	typEnemy _typenemy;
	int BonusDrop = 10;
	

	tuple<float, float, bool> BornePos;
	tuple<float, float, bool> delayProjNormal;
	tuple<float, float, bool> delayProjHuge;
	tuple<float, float, bool> delayUltraFast;


	
	//1 = droite // -1 gauche
	float direction =  1;

	double initialPosY;

	Enemie(Texture& text);
	Enemie(Texture& text, typEnemy type, Vector2f pos);



	~Enemie();

	void timerShoot();
	bool canShoot();
	void shoot(Asset *obj, short numProj);
	void  Update(RenderWindow&) override;
	bool isDead();
	bool  onTriggerEnter(Asset* obj) override;

	void movePatern();
};

