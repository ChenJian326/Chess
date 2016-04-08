#include "GameInfoNode.h"
#include "manager\EventManager.h"
#include "config\Config.h"
#include "config\VisibleRect.h"
GameInfoNode::GameInfoNode()
	:_countdown(0)
{
}

GameInfoNode::~GameInfoNode()
{
}

bool GameInfoNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto visiSize = Director::getInstance()->getVisibleSize();
	_countdownLb = Label::createWithSystemFont("00:00:00", "微软雅黑", 22);
	_countdownLb->setAnchorPoint(Vec2(0, 0));
	_countdownLb->setPosition(Vec2(60, visiSize.height - 30));

	_pcInfo = Label::createWithSystemFont(Config::GBKToUTF8("PC：红色棋子"), "微软雅黑", 22);
	_pcInfo->setAnchorPoint(Vec2(1, 0));
	_pcInfo->setPosition(Vec2(VisibleRect::rightBottom().x, VisibleRect::leftBottom().y + 100));

	_playerInfo = Label::createWithSystemFont(Config::GBKToUTF8("玩家：黑色棋子"), "微软雅黑", 22);
	_playerInfo->setAnchorPoint(Vec2(0, 0));
	_playerInfo->setPosition(Vec2(VisibleRect::leftBottom().x, VisibleRect::leftBottom().y + 100));

	_currentInfo = Label::createWithSystemFont("", "微软雅黑", 22);
	_currentInfo->setAnchorPoint(Vec2(0, 0));
	_currentInfo->setPosition(Vec2(VisibleRect::center().x, VisibleRect::leftBottom().y + 100));

	this->addChild(_countdownLb);
	this->addChild(_pcInfo);
	this->addChild(_playerInfo);
	this->addChild(_currentInfo);

	EventManager::getIns()->addEventListener(EventManager::EVENT_NEXT_COUNTDOWN, "", [this](EventCustom* event) {
		auto userData = static_cast<int*>(event->getUserData());
		const int type = Config::player;
		const int user = *userData;//将int*的值赋值给const int user
		if (user == type)
		{
			_countdown = 11;
			this->showCountdown(0.0);
			this->schedule(CC_SCHEDULE_SELECTOR(GameInfoNode::showCountdown), 1);
			_currentInfo->setString(Config::GBKToUTF8("当前下棋：玩家"));
		}
		else
		{
			_countdown = 1;
			this->showCountdown(0.0);
			_currentInfo->setString(Config::GBKToUTF8("当前下棋：PC"));
		}
	}, this);
	return true;
}
void GameInfoNode::showCountdown(float td)
{
	_countdown--;
	if (_countdown <= 0)
	{
		this->stopCountdown();
	}
	char str[9];
	if (_countdown < 10)
	{
		sprintf(str, "00:00:0%d", _countdown);
	}
	else 
	{
		sprintf(str, "00:00:%d", _countdown);
	}
	_countdownLb->setString(str);
}

void GameInfoNode::stopCountdown()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(GameInfoNode::showCountdown));
}