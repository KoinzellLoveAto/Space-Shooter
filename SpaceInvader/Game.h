#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Asset.h"
#include "Input.h"
#include "Projectile.h"
#include "PlayerShip.h"
#include "Enemie.h"
#include "Background.h"
#include "Bonus.h"
#include "Asteroid.h"
#include <list>

using namespace sf;
using std::cout;
using std::vector;


class Game
{
public:


	//Texture . . .
	Texture _blueShip;
	Texture _Redship_Boss_1;

	Texture _orangeShip;
	Texture _LaserBlue1;
	Texture _LaserBlue2;
	Texture _LaserRed1;
	Texture _LaserRed3;
	Texture _LaserRed4;

	Texture _enemyBlack1;
	Texture _MeteorBrownBig4;
	Texture _BackgroundBlack;

	Texture _PowerUpBlue_Star;
	Texture _PowerUpBlue_Bolt;
	// Sound 


	Music _background_music;
	SoundBuffer _projectileShoot;
	SoundBuffer _projectileImpact;
	vector<Sound*> list_sound_play;

	Font font;
	Text Timer;
	Text Score;
	int score = 0;

    


	enum e_texture
	{
		blueShip,
		LaserBlue,
		enemyBlack1,
		MeteorBrownBig4,
		BackgroundBlack,
	};

	//static int score;

	RenderWindow rw;

	void stopSound(string direction, Music musique);

	Game();
	~Game();
	
	Text TempsPasser(Clock &timer);
	Text TextScore();

	template <typename T, typename... Args> static T* createObject(const Args&... args)
	{

		return new T(args...);
	}

	void DeleteGameOject(Asset *obj)
	{
		delete obj;
	
	}

	




	static Texture& getTexture(e_texture choosenText);
	static void CreateProjectile(e_texture choosenText, Projectile::typeProjectile tp);

	static Game* Instance;
	static Game* getInstance();
	static vector<Asset*>  list_Asset;

	//2Background pour qu'il se suive l'un et l'autre
	Background* pBackground = nullptr;
	Background* pBackground2 = nullptr;


	PlayerShip* playerShip = nullptr;
	PlayerShip* playerShip2 = nullptr;

	PlayerShip* tab_Players[2] = { playerShip, playerShip2 };


	vector<Enemie*> list_Enemie;
	vector<Projectile*> list_Projectile;
	vector<Bonus*> list_Bonus;


	//PlayerShip _player2;

	void listenInput(Event* event);
	void InitBackground();
	void updateAssets();

	int nbEnemieInMap = 0;
	int nbEnemieInMapInitiale = 0;
	int nbShipToIncrease = 0;
	int ShipKilled= 0;
	void SpawnEnemiShip();
	void createRandomBonus(Enemie* ene);
	void createAsteroid(Texture& refText);

	void run();

	void trigger();
	void ActionGame();
	void ActionPlayer();
	void TimerPlayer();


private:
	void loadAllTexture();
	void loadSound();

	

};

