#include "GameManager.h"
#include <new>
#include "config\Config.h"
#include "EventManager.h"

static GameManager* _manager = nullptr;

GameManager::GameManager()
	:_director(Director::getInstance()),
	_currentMoveChessman(Config::nullChessman),
	_currentSelectChessman(Config::nullChessman)
{
}

GameManager::~GameManager()
{
}

GameManager* GameManager::GetIns()
{
	if (nullptr == _manager)
	{
		_manager = new (std::nothrow) GameManager();
	}
	return _manager;
}

void GameManager::setCurrentOpponent(int value)
{
	_currentOpponent = value;
	//给玩家一个倒计时
	EventManager::getIns()->dispatchEvent(EventManager::EVENT_NEXT_COUNTDOWN, &_currentOpponent);
}

void GameManager::setCurrentSelectChessman(int chessmanType)
{
	_currentSelectChessman = chessmanType;
}

void GameManager::setCurrentMoveChessman(int chessmanType)
{
	_currentMoveChessman = chessmanType;
}

void GameManager::startTime()
{
	//_director->getScheduler()->scheduleScriptFunc(schedule_selector(), 10, false);
}
//
bool GameManager::isEatOrMove(int opponentType)
{
	bool isEatOrMove = false;
	if (_currentSelectChessman == -1)
	{
		isEatOrMove = true;
	}
	else
	{
		if (opponentType == _currentOpponent)
		{
			isEatOrMove = false;
		}
		else
		{
			if (_currentSelectChessman == _currentMoveChessman || _currentMoveChessman < _currentSelectChessman)
			{
				isEatOrMove = true;
			}
			else if (_currentSelectChessman == Config::CHESSTYPE::handsome && _currentMoveChessman == Config::CHESSTYPE::soldiers)
			{
				isEatOrMove = true;
			}
		}
	}
	return isEatOrMove;
}

void GameManager::moveChessman(int opponentType)
{
	//在这里写交换两个棋子的位置




	//修改下一个下棋的人
	if (opponentType == Config::pc)
	{
		setCurrentOpponent(Config::player);
	}
	else
	{
		setCurrentOpponent(Config::pc);
	}
}


