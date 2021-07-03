#pragma once

#include "asset.h"
class PlayerShip: public Asset
{


	



public :
	
	vector<Asset*> list_projectile;
	
	//Texture& AllyProjBlue ;
	//Texture* AllyProjRed = nullptr;
	//
	enum statePlayer
	{
		e_Alive = 0,
		e_Dead
	};


	enum num_joueur
	{
		Joueur1 = 0,
		Joueur2,

	};

	struct Moves
	{
		bool forward;
		bool backward;
		bool right;
		bool left;
		bool shoot;
	};

	struct projectileUnlocked
	{
		bool normal;
		bool fast;
		bool ultraFast;
		bool Huge;
		bool special;
	};

	statePlayer _state_player;
	num_joueur _num_player;
	projectileUnlocked _ProjUnlocked;
	bool _SpeedBoost;
	Moves _moves;

	
	float delayShootProjectileDefault = 0;
	float delayShootProjectile = 0;


	//1st default 2nd real;
	tuple<float, float, bool> delayProjNormal;
	tuple<float, float, bool> delayProjHuge;
	tuple<float, float, bool> delayProjFast;
	tuple<float, float, bool> delayProjUltraFast;
	tuple<float, float, bool> delayProjSpecial;

	tuple<float, float, bool> frameInvulrabilite; // invulnérabilité joueur
	tuple<float, float, bool> durationSpeedBoost; //SPEED BOOST DUREE /ETAT


	int countClignotement = 0;

	void InitStats();
	void shoot(Asset* obj, short proj); // asset et numéro du tir ( pour geré plusieurs cannon )
	PlayerShip(Texture& text, num_joueur j);
	~PlayerShip();

	void takeDammage( const float&);
	void Dead();
	void  Update(RenderWindow&) override;
	bool   onTriggerEnter(Asset* obj) override;

};

