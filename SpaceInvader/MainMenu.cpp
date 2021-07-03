#include "MainMenu.h"


MainMenu::MainMenu(RenderWindow &window)
{
	
	// Démarrer le jeu
	font.loadFromFile("Font/Kenney Pixel.ttf");
	MenuJeu[0].setFont(font);
	MenuJeu[0].setFillColor(Color::Green);
	MenuJeu[0].setString("Démarrer AdlezShooter");
	MenuJeu[0].setCharacterSize(50);
	MenuJeu[0].setPosition(Vector2f(window.getSize().x / 2 - 50, window.getSize().y / (OptionMax + 1)));

	// Quitter le jeu
	font.loadFromFile("Font/Kenney Pixel.ttf");
	MenuJeu[1].setFont(font);
	MenuJeu[1].setFillColor(Color::White);
	MenuJeu[1].setString("Quitter");
	MenuJeu[1].setCharacterSize(50);
	MenuJeu[1].setPosition(Vector2f(window.getSize().x / 2 - 50, window.getSize().y / (OptionMax + 1) * 2));

	MenuSelectionne = 0;
	InitMenu(window);
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitMenu(RenderWindow &window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(MenuJeu[i]);
	}
}

void MainMenu::EventHaut()
{
	if (MenuSelectionne -1 >= 0)
	{
		MenuJeu[MenuSelectionne].setFillColor(Color::Green);
		MenuSelectionne--;
		if (MenuSelectionne == -1)
		{
			MenuSelectionne = 1;
		}
		MenuJeu[MenuSelectionne].setFillColor(Color::White);
	}
}

void MainMenu::EventBas()
{
	if (MenuSelectionne +1 <= OptionMax)
	{
		MenuJeu[MenuSelectionne].setFillColor(Color::White);
		MenuSelectionne++;
		if (MenuSelectionne == 2)
		{
			MenuSelectionne = 0;
		}
		MenuJeu[MenuSelectionne].setFillColor(Color::Green);
	}
}
