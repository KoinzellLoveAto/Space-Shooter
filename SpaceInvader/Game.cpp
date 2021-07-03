#include "Game.h"
#include "MainMenu.h"
#include "GameOver.h"
#include <SFML/Audio.hpp>

//Membre STATIQUE 

vector<Asset*>  Game::list_Asset{};

Game* Game::Instance{
Instance = nullptr
};



Texture& Game::getTexture(e_texture choosenText)
{
	switch (choosenText)
	{

	case LaserBlue:
		return Instance->_blueShip;
		break;


	}
}

void Game::CreateProjectile(e_texture choosenText, Projectile::typeProjectile tp)
{



	switch (choosenText)
	{
	case MeteorBrownBig4:
		break;
	case LaserBlue:

		break;

	default:
		//Instance->p = new Projectile(Instance->_LaserBlue, tp);
		break;
	}
}


void Game::createRandomBonus(Enemie* ene)
{
	int randChanceSpawn;
	randChanceSpawn = rand() % ene->BonusDrop;

	if (randChanceSpawn < 9)
	{
		Bonus* pBonus = nullptr;
		int rdm_type_bonus = rand() % 2;

		switch (rdm_type_bonus)
		{
		case Bonus::attack:
			pBonus = new Bonus(_PowerUpBlue_Star, ene->getPosition(), Bonus::attack);
			break;

		case Bonus::speed:
			pBonus = new Bonus(_PowerUpBlue_Bolt, ene->getPosition(), Bonus::speed);
			break;

		default:
			break;
		}
		list_Bonus.push_back(pBonus);
	}
}

void Game::createAsteroid(Texture& refText)
{

}


void Game::stopSound(string direction, Music musique)
{
	musique.stop();
}


Game::Game() : rw(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Space Invaders")
{
	// def max fps
	//score = 0;
	nbEnemieInMapInitiale = 3;
	rw.setFramerateLimit(FRAME_LIMIT);
	rw.setKeyRepeatEnabled(false);

	loadAllTexture();
	loadSound();
	InitBackground();
	tab_Players[0] = new PlayerShip(_blueShip, PlayerShip::Joueur1);
	tab_Players[1] = new PlayerShip(_orangeShip, PlayerShip::Joueur2);


}

Game::~Game()
{
}

Text Game::TempsPasser(Clock& timer)
{
	// Démarrer le timer
	float temps = timer.getElapsedTime().asSeconds();

	font.loadFromFile("Font/Kenney Pixel.ttf");
	Timer.setFont(font);
	Timer.setFillColor(Color::Green);
	Timer.setString("Temps Passé : " + to_string(temps));

	Timer.setCharacterSize(30);
	/*Timer.setPosition(Timer.getLocalBounds().width / 2.f + 200, Timer.getLocalBounds().height / 2.0f - 5);*/
	Timer.setPosition(Vector2f(rw.getSize().x / 16 - 50, rw.getSize().y / 16 - 20));
	return Timer;

}

Text Game::TextScore()
{
	font.loadFromFile("Font/Kenney Pixel.ttf");
	Score.setFont(font);
	Score.setFillColor(Color::White);
	Score.setString("Score : " + to_string(score));
	Score.setCharacterSize(35);
	Score.setPosition(Vector2f(rw.getSize().x / 16 - 50, rw.getSize().y / 16 - 50));
	return Score;
}



Game* Game::getInstance()
{
	if (Instance == nullptr)
		Instance = new Game();
	return Instance;
}

void Game::listenInput(Event* event)
{
	switch (event->type)
	{

	case Event::KeyPressed:
		switch (event->key.code)
		{
			/* Player ONE  */
		case  Keyboard::Z:
			tab_Players[0]->_moves.forward = true;
			break;

		case  Keyboard::Q:
			tab_Players[0]->_moves.left = true;
			break;

		case   Keyboard::S:
			tab_Players[0]->_moves.backward = true;
			break;

		case   Keyboard::D:
			tab_Players[0]->_moves.right = true;
			break;

		case Keyboard::Space:
			tab_Players[0]->_moves.shoot = true;
			break;

			/* Player TWO  */
		case  Keyboard::Up:
			tab_Players[1]->_moves.forward = true;
			break;

		case  Keyboard::Left:
			tab_Players[1]->_moves.left = true;
			break;

		case   Keyboard::Down:
			tab_Players[1]->_moves.backward = true;
			break;

		case   Keyboard::Right:
			tab_Players[1]->_moves.right = true;
			break;

		case Keyboard::Numpad0:
			tab_Players[1]->_moves.shoot = true;
			break;
		}
		break;


	case Event::KeyReleased:
		switch (event->key.code)
		{
		case Keyboard::Q:
			tab_Players[0]->_moves.left = false;
			break;

		case Keyboard::D:
			tab_Players[0]->_moves.right = false;
			break;

		case Keyboard::Z:
			tab_Players[0]->_moves.forward = false;
			break;

		case Keyboard::S:
			tab_Players[0]->_moves.backward = false;;
			break;

		case Keyboard::Space:
			tab_Players[0]->_moves.shoot = false;

			/* Player TWO  */
		case  Keyboard::Up:
			tab_Players[1]->_moves.forward = false;
			break;

		case  Keyboard::Left:
			tab_Players[1]->_moves.left = false;
			break;

		case   Keyboard::Down:
			tab_Players[1]->_moves.backward = false;
			break;

		case   Keyboard::Right:
			tab_Players[1]->_moves.right = false;
			break;

		case Keyboard::Numpad0:
			tab_Players[1]->_moves.shoot = false;
			break;

		}

	default:
		break;
	}




}

void Game::InitBackground()
{
	this->pBackground = new Background(_BackgroundBlack);
	this->pBackground->sprite.setPosition(0, 0);
	this->pBackground2 = new Background(_BackgroundBlack);
	this->pBackground2->sprite.setPosition(0, -SCREEN_SIZE);

}

void Game::updateAssets()
{


	for (auto asset : list_Asset)
	{

		asset->Update(rw);


	}


}

void Game::SpawnEnemiShip()
{
	if (nbEnemieInMap > nbEnemieInMapInitiale + nbShipToIncrease)return;


	double random_x = rand() % SCREEN_SIZE;

	double random_y = rand() % SCREEN_SIZE / 2;
	// on fait spawner en dehors de l'écran
	Enemie* ptrEnemie = nullptr;
	if (ShipKilled % 10 == 0 && ShipKilled != 0)
	{
		ptrEnemie = new Enemie(_Redship_Boss_1, Enemie::e_BossShip, Vector2f(random_x, random_y - SCREEN_SIZE));
	}
	else
	{
		ptrEnemie = new Enemie(_enemyBlack1, Enemie::e_normalShip, Vector2f(random_x, random_y - SCREEN_SIZE));

	}
	list_Enemie.push_back(ptrEnemie);



	nbEnemieInMap++;

}

void Game::run()
{
	MainMenu menu(rw);
	
	Music musique;
	Clock timer;
	
	
	while (rw.isOpen())
	{

		sf::Event event;
		while (rw.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				rw.close();
			listenInput(&event);

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					menu.EventHaut();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					menu.EventBas();
					break;
				}
				if (event.key.code == Keyboard::Enter && menu.MenuSelectionne == 0)
				{
					
					menu.enJeu = true;
					
					
				}
				if (event.key.code == Keyboard::Enter && menu.MenuSelectionne == 1)
				{
					rw.close();
				}
			}
		}
		TimerPlayer();
		ActionGame();
		ActionPlayer();
		trigger();
		rw.clear();
		menu.MenuSelectionne;
		if (menu.enJeu == false)
		{
			menu.InitMenu(rw);
		}
		if (menu.enJeu == true)
		{

			this->updateAssets();

			//Temps & Score
			rw.draw(TempsPasser(timer));
			rw.draw(TextScore());
			if (tab_Players[0]->_state_player && tab_Players[1]->_state_player == 1)
			{
				/*Clock temps;
				tempsmoins = timer.getElapsedTime().asSeconds() - temps.getElapsedTime().asMicroseconds();
				GameOver gameover(rw, score, tempsmoins);
				gameover.InitOver(rw);*/
				Instance = nullptr;
				delete this;
				return;
			}
		}
		rw.display();



	}
}

// detectee les collision
void Game::trigger()
{
	int indexProj = -1;
	for (auto& projectile : list_Projectile)
	{

		if (projectile != nullptr)
		{
			indexProj++;
			try {
				Vector2f pos = projectile->getPosition();
				if (pos.x < 0 || pos.x > SCREEN_SIZE || pos.y > SCREEN_SIZE)
				{

					delete projectile;
					list_Projectile.erase(list_Projectile.begin() + indexProj);
					return;


				}




				int indexEnnemi = 0;
				for (auto& ennemi : list_Enemie)
				{

					int indexEnnProj = 0;

					if (ennemi->onTriggerEnter(projectile))
					{
						list_Projectile.erase(list_Projectile.begin() + indexProj);
						score = score + 10;
						return;

					}


					indexEnnemi++;
				}


				int indexPlayer = 0;
				for (auto& player : tab_Players)// pas de raison que l'un des deux joeuur soir un pointeur null
				{

					if (player->onTriggerEnter(projectile))
					{

						list_Projectile.erase(list_Projectile.begin() + indexProj);
						return;



					}

					indexPlayer++;
				}
			}
			catch (...) {
				cout << " crahs évité" << endl;
			}
		}

	}

	int indexPlayer = 0;
	for (auto& player : tab_Players)// pas de raison que l'un des deux joeuur soir un pointeur null
	{

		int indexBonus = 0;
		for (auto& bonus : list_Bonus)
		{
			//if(bonus->killWhenOutOfScreen())
			//{
			//	list_Bonus.erase(list_Bonus.begin() + indexBonus);
			//
			//}

			if (player->onTriggerEnter(bonus))
			{

				list_Bonus.erase(list_Bonus.begin() + indexBonus);
				continue;

			}

			indexBonus++;

		}
		indexPlayer++;

	}

}





void Game::ActionGame()
{
	SpawnEnemiShip();
	for (auto& ennemi : list_Enemie)
	{

			Projectile* p = nullptr;
			switch (ennemi->_typenemy)
			{
				
			case Enemie::e_normalShip: // tire des projectile normal 
				if (get<2>(ennemi->delayProjNormal))
				{
					p = new Projectile(_LaserRed1, Projectile::normal, Projectile::Enemies);
					ennemi->shoot(p, 0); // nombre n'a pas d'importance pour un normalship
					list_Projectile.push_back(p);
				}
				break;

			case Enemie::e_BossShip:
				if (get<2>(ennemi->delayProjHuge))
				{
					p = new Projectile(_LaserRed3, Projectile::Huge, Projectile::Enemies);
					ennemi->shoot(p, 0);
					list_Projectile.push_back(p);
				}

				if (get<2>(ennemi->delayUltraFast))
				{
					p = new Projectile(_LaserRed4, Projectile::ultraFast, Projectile::Enemies);
					ennemi->shoot(p, 1);
					list_Projectile.push_back(p);

					p = new Projectile(_LaserRed4, Projectile::ultraFast, Projectile::Enemies);
					ennemi->shoot(p, 2);
					list_Projectile.push_back(p);
				}
				break;

			
		}


	}

	int indexEnnemi = 0;
	for (auto& ennemi : list_Enemie)
	{
		if (ennemi->isDead())
		{
			createRandomBonus(ennemi);
			delete ennemi;
			list_Enemie.erase(list_Enemie.begin() + indexEnnemi);
			score = score + 100;
			nbEnemieInMap--;
			ShipKilled++;
			if (ShipKilled % 3 == 0)
			{
				nbShipToIncrease++;
			}
		}
		indexEnnemi++;
	}
}

void Game::ActionPlayer()
{
	/* player 1 */
	for (auto& player : tab_Players)
	{
		if (player->_moves.shoot)
		{
			
			if (get<2>(player->delayProjNormal))
			{
				Sound* shoot_sound = new Sound();
				shoot_sound->setBuffer(_projectileShoot);
				shoot_sound->play();
				//list_sound_play.push_back(shoot_sound);
				Projectile* p;
				get<2>(player->delayProjNormal) = false;
				p = new Projectile(_LaserBlue1, Projectile::normal, Projectile::players);
				list_Projectile.push_back(p);
				player->shoot(p, 0); // center shoot

			}
			if (get<2>(player->delayProjFast) && player->_ProjUnlocked.fast)
			{
				Projectile* p;

				get<2>(player->delayProjFast) = false;

				p = new Projectile(_LaserBlue2, Projectile::fast, Projectile::players);
				player->shoot(p, 1);
				list_Projectile.push_back(p);

				p = new Projectile(_LaserBlue2, Projectile::fast, Projectile::players);
				player->shoot(p, 2);
				list_Projectile.push_back(p);


			}
		}
	}



}

void Game::TimerPlayer()
{

	/* player 1*/



}

void Game::loadAllTexture()
{
	if (!this->_blueShip.loadFromFile(BLUE_SHIP))
	{
		cout << "texture_BlueShip_Not_Found !" << endl;
	}
	else cout << "_BlueShip_found" << endl;

	if (!this->_orangeShip.loadFromFile(ORANGE_SHIP))
	{
		cout << "texture_OrangeShip_Not_Found !" << endl;
	}
	else cout << "_OrangeShip_found" << endl;

	if (!this->_LaserBlue1.loadFromFile(LASER_BLUE1))
	{
		cout << "texture_LaserBlue1_Not_Found !" << endl;
	}
	else cout << "_LaserBlue1_found" << endl;

	if (!this->_LaserBlue2.loadFromFile(LASER_BLUE2))
	{
		cout << "texture_LaserBlue2_Not_Found !" << endl;
	}
	else cout << "_LaserBlue2_found" << endl;

	if (!this->_LaserRed1.loadFromFile(LASER_RED1))
	{
		cout << "texture_LaserRed1_Not_Found !" << endl;
	}
	else cout << "_LaserRed1_found" << endl;

	if (!this->_enemyBlack1.loadFromFile(ENEMY_BLACK_1))
	{
		cout << "texture_enemyBlack1_Not_Found !" << endl;
	}
	else cout << "_enemyBlack1_found" << endl;

	if (!this->_MeteorBrownBig4.loadFromFile(METEOR_BROWN_BIG4))
	{
		cout << "texture_MeteorBrownBig4_Not_Found !" << endl;
	}
	else cout << "_MeteorBrownBig4_found" << endl;

	if (!this->_BackgroundBlack.loadFromFile(BG_COLOR_BLACK))
	{
		cout << "texture_BackgroundBlack_Not_Found !" << endl;
	}
	else cout << "_BackgroundBlack_found" << endl;

	if (!this->_PowerUpBlue_Bolt.loadFromFile(POWER_UP_BLUE_BOLT))
	{
		cout << "texture_PowerUpBlue_Bolt_Not_Found !" << endl;
	}
	else cout << "_PowerUpBlue_Bolt_found" << endl;

	if (!this->_PowerUpBlue_Star.loadFromFile(POWER_UP_BLUE_STAR))
	{
		cout << "texture_PowerUpBlue_Star_Not_Found !" << endl;
	}
	else cout << "_PowerUpBlue_Star_found" << endl;

	if (!this->_Redship_Boss_1.loadFromFile(BOSS_RED_SHIP_1))
	{
		cout << "texture_Redship_Boss_1_Not_Found !" << endl;
	}
	else cout << "_Redship_Boss_1_found" << endl;

	if (!this->_LaserRed3.loadFromFile(LASER_RED3))
	{
		cout << "texture_LaserRed3_Not_Found !" << endl;
	}
	else cout << "_LaserRed3_found" << endl;

	if (!this->_LaserRed4.loadFromFile(LASER_RED4))
	{
		cout << "texture_LaserRed4_Not_Found !" << endl;
	}
	else cout << "_LaserRed4_found" << endl;
}


void Game::loadSound()
{
	if (!_background_music.openFromFile(COMBAT_MUSIC))
	{

	}
	//_background_music.play();
	//_background_music.setLoop(true);


	if (!_projectileShoot.loadFromFile(LASER_SOUND))
	{

	}
}
