#pragma once
#include "Game.h"

class GameOver
{
private:
	Text MenuJeu[3];
	Font font;
public:
	GameOver(RenderWindow& window,int score,float temps);
	~GameOver();
	void InitOver(RenderWindow& window);
	bool mort = false;
};

