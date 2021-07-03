#include "GameOver.h"

GameOver::GameOver(RenderWindow& window, int score , float temps) 
{
	// Démarrer le jeu
	
	font.loadFromFile("Font/Kenney Pixel.ttf");
	MenuJeu[0].setFont(font);
	MenuJeu[0].setFillColor(Color::Red);
	MenuJeu[0].setString("Game Over");
	MenuJeu[0].setCharacterSize(50);
	MenuJeu[0].setPosition(Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 2));

	// Score du jeu
	font.loadFromFile("Font/Kenney Pixel.ttf");
	MenuJeu[1].setFont(font);
	MenuJeu[1].setFillColor(Color::White);
	MenuJeu[1].setString("Score :" + score);
	MenuJeu[1].setCharacterSize(40);
	MenuJeu[1].setPosition(Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 2));

	font.loadFromFile("Font/Kenney Pixel.ttf");
	MenuJeu[2].setFont(font);
	MenuJeu[2].setFillColor(Color::White);
	MenuJeu[2].setString("Temps Joué :" + to_string(temps));
	MenuJeu[2].setCharacterSize(40);
	MenuJeu[2].setPosition(Vector2f(window.getSize().x / 2 - 50, window.getSize().y / 2));

	InitOver(window);
}

GameOver::~GameOver()
{
}

void GameOver::InitOver(RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(MenuJeu[i]);
	}
}

