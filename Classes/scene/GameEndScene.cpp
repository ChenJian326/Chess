#include "GameEndScene.h"
#include "view\GameEndNode.h"
GameEndScene::GameEndScene()
	:_winType(Config::pc)
{
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
	auto node = GameEndNode::create();
	this->addChild(node);
	return true;
}
