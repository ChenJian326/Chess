#include "GameInfoNode.h"
#include "manager\EventManager.h"
#include "config\Config.h"
#include "config\VisibleRect.h"
#include "tips\TipsManager.h"
#include "config\DisplayTools.h"

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
	int spacing = visiSize.height * 0.08;

	_countdownLb = DisplayTools::createLabel("00:00:00", 22, Vec2(60, visiSize.height - 30), Vec2(0, 0));
	_pcInfo = DisplayTools::createLabel(Config::GBKTOUTF8("PC：红色棋子"), 18, Vec2(VisibleRect::rightBottom().x, VisibleRect::leftBottom().y + spacing), Vec2(1, 0));
	_playerInfo = DisplayTools::createLabel(Config::GBKTOUTF8("player：黑色棋子"), 18, Vec2(VisibleRect::leftBottom().x, VisibleRect::leftBottom().y + spacing), Vec2(0, 0));
	_currentInfo = DisplayTools::createLabel("", 18, Vec2(VisibleRect::center().x, VisibleRect::leftBottom().y + spacing), Vec2(0.5, 0));
	_pcScore = DisplayTools::createLabel("pc:0", 18, Vec2(VisibleRect::left().x + 80, visiSize.height - 70), Vec2(0, 0));
	_playerScore = DisplayTools::createLabel("player:0", 18, Vec2(VisibleRect::right().x - 150, visiSize.height - 70), Vec2(0, 0));

	this->addChild(_countdownLb);
	this->addChild(_pcInfo);
	this->addChild(_playerInfo);
	this->addChild(_currentInfo);
	this->addChild(_pcScore);
	this->addChild(_playerScore);

	EventManager::getIns()->addEventListener(EventManager::EVENT_NEXT_COUNTDOWN, "", [this](EventCustom* event) {
		auto userData = static_cast<int*>(event->getUserData());
		const int type = Config::player;
		const int user = *userData;//将int*的值赋值给const int user
		if (user == type)
		{
			_countdown = 11;
			_isShowTips = true;
			this->showCountdown(0.0);
			this->schedule(CC_SCHEDULE_SELECTOR(GameInfoNode::showCountdown), 1);
			_currentInfo->setString(Config::GBKTOUTF8("当前下棋：玩家"));
		}
		else
		{
			_countdown = 1;
			_isShowTips = false;
			this->showCountdown(0.0);
			_currentInfo->setString(Config::GBKTOUTF8("当前下棋：PC"));
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
		if (_isShowTips) {
			TipsManager::showTips("喂！快点下棋啊，怎么想了那么久啊");
		}
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

void GameInfoNode::updateScore(int score1, int score2)
{
	char str[12];
	sprintf(str, "pc:%d", 16 - score2);
	_pcScore->setString(str);
	sprintf(str, "player:%d", 16 - score1);
	_playerScore->setString(str);
}