#pragma once
#include <SFML/Graphics.hpp>
#include "assetPath.h"
#include <iostream>
#include "Game.h"

using namespace std;
using namespace sf;
int main()
{
	
	Game *g = Game::getInstance();
	while (true)
	{
		if (Game::Instance == nullptr)
		{
			g = Game::getInstance();
		}
		else
		{
			g->run();
		}
	}	
}

