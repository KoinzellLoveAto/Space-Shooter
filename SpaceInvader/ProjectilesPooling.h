#pragma once
#include "Projectile.h"
const int sizePollingProjectiles = 1000;

class ProjectilesPooling
{
public :
	Projectile* tabProjectile[sizePollingProjectiles];

	static ProjectilesPooling* Instance;
	static ProjectilesPooling* GetInstance();


	ProjectilesPooling();
	~ProjectilesPooling();

	
};

