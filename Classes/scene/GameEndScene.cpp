#include "GameEndScene.h"

GameEndScene::GameEndScene()
	:_winType(Config::pc)
{
}

GameEndScene::GameEndScene(int winType)
{
	_winType = winType;
}

GameEndScene::~GameEndScene()
{
}

bool GameEndScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	if (_winType == Config::pc)
	{

	}
	return true;
}
