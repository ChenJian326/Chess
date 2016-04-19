#include "GameScene.h"
#include "view\GameMap.h"
#include "view\GameInfoNode.h"
#include "manager\EventManager.h"
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
	//��Ҫ��һ��������¼��Ż���Ч
	auto infoPanel = GameInfoNode::create();
	this->addChild(infoPanel);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::showMap),0.05);
	EventManager::getIns()->addEventListener(EventManager::EVENT_UPDATE_SCORE, "", [=](EventCustom* event) {
		auto userData = static_cast<std::vector<int>*>(event->getUserData());
		infoPanel->updateScore(userData->at(0), userData->at(1));
	}, this);
	return true;
}

void GameScene::showMap(float dt)
{
	auto map = GameMap::create();
	this->addChild(map);
}
