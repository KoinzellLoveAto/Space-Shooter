#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Input
{
public :
	Input();
	~Input();

	bool forward = false;
	bool backward = false;
	bool right = false;
	bool left = false;

	bool shoot;

	void listenEvent(Event& event);
};