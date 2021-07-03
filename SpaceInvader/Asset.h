#pragma once
#include <SFML/Graphics.hpp>
#include "assetPath.h"
#include <iostream>
#include "Stats.h"

using namespace std;
using namespace sf;

class  Asset
{

public:
	Asset(Texture &text);
	
	~Asset();

	void  setPosition(Vector2f position);
	void move(float speed_X, float speed_Y, float ElapsedTime);
	Vector2f   getPosition();
	bool killWhenOutOfScreen();
	Vector2u getPixelSprite();

	// event sur la collision d'un objet
	virtual bool   onTriggerEnter(Asset* obj);


	enum type_asset
	{
		e_Projectile = 0,
		e_PlayerShip,
		e_EnemieShip,
		e_Bonus,
		e_Meteor,
		e_Background
	};

	type_asset _type_asset;

	//#Unity
	virtual void Update(RenderWindow&) = 0;

	string gameObjectName;
	Sprite sprite;
	Texture &texture;
	Stats stats;
};
