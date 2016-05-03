#include "GameEndNode.h"
#include "config\VisibleRect.h"
#include "scene\GameScene.h"
#include "manager\GameManager.h"
#include "config\DisplayTools.h"


GameEndNode::GameEndNode()
	:_winType(Config::pc)
{
}

GameEndNode::~GameEndNode()
{
}

bool GameEndNode::init()
{
	if (!Node::init()) {
		return false;
	}
	_winType = GameManager::GetIns()->getWinType();
	Label *lb;
	if (_winType == Config::pc)
	{
		lb = DisplayTools::createLabel(Config::GBKTOUTF8("人类你们弱爆了，可有本事再战一局！"),16,Vec2(VisibleRect::center().x, VisibleRect::center().y + 30));
	}
	else
	{
		lb = DisplayTools::createLabel(Config::GBKTOUTF8("不是听说你PC会深度学习吗，怎么还是这个鬼样，可有本事再战一局！"), 16, Vec2(VisibleRect::center().x, VisibleRect::center().y + 30));
	}
	auto startBtn = MenuItemFont::create("continue game", CC_CALLBACK_1(GameEndNode::continueGame, this));
	auto exitBtn = MenuItemFont::create("exit game", CC_CALLBACK_1(GameEndNode::exitGame, this));
	exitBtn->setPositionY(-30);
	auto menu = Menu::create(startBtn, exitBtn, nullptr);
	menu->setPosition(VisibleRect::center());
	this->addChild(menu);
	this->addChild(lb);
	return true;
}

void GameEndNode::continueGame(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameEndNode::exitGame(Ref* pSender)
{
	Director::getInstance()->end();
}
