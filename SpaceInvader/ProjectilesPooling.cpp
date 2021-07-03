#include "ProjectilesPooling.h"


ProjectilesPooling* ProjectilesPooling::Instance
{
	Instance = nullptr
};

ProjectilesPooling* ProjectilesPooling::GetInstance()
{
	if (Instance == nullptr)
		Instance = new ProjectilesPooling();
	return Instance;
}



ProjectilesPooling::ProjectilesPooling()
{
}

ProjectilesPooling::~ProjectilesPooling()
{
}
