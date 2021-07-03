#pragma once
#include "Game.h"
#define OptionMax 2
class MainMenu
{
private:
	
	Text Titrejeu;
	Text MenuJeu[OptionMax];
	Font font;
public:
	MainMenu(RenderWindow& window);
	~MainMenu();
	void InitMenu(RenderWindow &window);
	void EventHaut();
	void EventBas();
	int MenuSelectionne;
	bool enJeu = false;
};

