#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::listenEvent(Event& event)
{

	switch (event.type)
	{
	case Event::KeyPressed:

		if (event.key.code == sf::Keyboard::D)
		{
			this->right = true;
		}

		if (event.key.code == sf::Keyboard::Z)
		{
			this->forward = true;
		}

		if (event.key.code == sf::Keyboard::Q)
		{
			this->left = true;
		}

		if (event.key.code == sf::Keyboard::S)
		{
			this->backward = true;
		}

		if (event.key.code == sf::Keyboard::E)
		{
			this->shoot = true;
		}

		break;

	case Event::KeyReleased:
		if (event.key.code == sf::Keyboard::D)
		{
			this->right = false;
		}

		if (event.key.code == sf::Keyboard::Z)
		{
			this->forward = false;
		}

		if (event.key.code == sf::Keyboard::Q)
		{
			this->left = false;
		}

		if (event.key.code == sf::Keyboard::S)
		{
			this->backward = false;
		}

		if (event.key.code == sf::Keyboard::E)
		{
			this->shoot = false;
		}


	default:
		break;
	}


}
