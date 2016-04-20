#include "GameScene.h"
#include "view\GameMap.h"
#include "view\GameInfoNode.h"
#include "manager\EventManager.h"
#include "GameEndScene.h"
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
	//需要等一会里面的事件才会生效
	auto infoPanel = GameInfoNode::create();
	this->addChild(infoPanel);
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::showMap),0.05);
	EventManager::getIns()->addEventListener(EventManager::EVENT_UPDATE_SCORE, "", [=](EventCustom* event) {
		auto userData = static_cast<std::vector<int>*>(event->getUserData());
		int pcSize = userData->at(0);
		int plSize = userData->at(1);
		infoPanel->updateScore(pcSize, plSize);
	}, this);
	EventManager::getIns()->addEventListener(EventManager::EVENT_GAME_END, "", [=](EventCustom* event) {
		auto scene = GameEndScene::create();
		Director::getInstance()->replaceScene(scene);
	}, this);
	return true;
}

void GameScene::showMap(float dt)
{
	auto map = GameMap::create();
	this->addChild(map);
}
