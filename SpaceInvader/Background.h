#pragma once
#include "Asset.h"
class Background : public Asset
{
public:

	Background(Texture &text);
	~Background();
	void  Update(RenderWindow&) override;
	bool   onTriggerEnter(Asset* obj) override; // pas tres utile pour le fond 


	float speed_y;
	float speed_x;
	float elapsedTime;
};

