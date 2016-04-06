#include "GameScene.h"
#include "view\GameMap.h"
#include "view\GameInfoNode.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

Scene * GameScene::createScene()
{
	auto scene = Scene::create();

	auto node = GameScene::create();

	scene->addChild(node);

	return scene;
}

bool GameScene::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto infoPanel = GameInfoNode::create();
	this->addChild(infoPanel);
	auto map = GameMap::create();
	this->addChild(map);
	return true;
}
