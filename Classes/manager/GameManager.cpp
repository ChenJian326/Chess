#include "GameManager.h"
#include <new>
#include "config\Config.h"
#include "EventManager.h"
#include "view\ChessmanNode.h"
#include "ai\PcAi.h"

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

void GameManager::starGame(int opponentType)
{
	setCurrentOpponent(opponentType);
	PcAi::initChessIndex();
}

void GameManager::endGame(int opponentType)
{
}

void GameManager::setCurrentOpponent(int value)
{
	_currentOpponent = value;
	//给玩家一个倒计时
	EventManager::getIns()->dispatchEvent(EventManager::EVENT_NEXT_COUNTDOWN, &_currentOpponent);
	if (_currentOpponent == Config::pc)
	{
		auto index = PcAi::startAi(_currentOpponent);
		if (PcAi::getNextIndex() == Config::nullChessman) {
			dynamic_cast<ChessmanNode*>(_pcChessmans.at(index))->MoveOrSelect(true);
		}
		else
		{
			dynamic_cast<ChessmanNode*>(_pcChessmans.at(index))->MoveOrSelect(true);
			dynamic_cast<ChessmanNode*>(_pcChessmans.at(PcAi::getNextIndex()))->MoveOrSelect(true);
		}
	}
	_currentMoveChessman = Config::nullChessman;
	_currentSelectChessman = Config::nullChessman;
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
	if (_currentSelectChessman == Config::nullChessman)
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

void GameManager::pushChessman(Node * node)
{
	auto chessman = dynamic_cast<ChessmanNode*>(node);
	if (chessman->getOpponentType() == Config::pc) {
		_pcChessmans.push_back(chessman);
	}
	else
	{
		_playerChessmans.push_back(chessman);
	}
	_allChessmans.push_back(node);
}



int GameManager::getSelectChessOpponent()
{
	int opponent = Config::nullChessman;
	if (!_moveChessmens.empty() && _moveChessmens.size() > 0)
	{
		opponent = dynamic_cast<ChessmanNode*>(_moveChessmens.at(0))->getOpponentType();
	}
	return opponent;
}

std::vector<Node*> GameManager::getChessmans(int opponentType)
{
	if (opponentType == Config::pc) {
		return _pcChessmans;
	}
	else
	{
		return _playerChessmans;
	}
}

void GameManager::pushMoveChessmens(Node * node)
{
	_moveChessmens.push_back(node);
}

void GameManager::moveChessman(int opponentType)
{
	//在这里写交换两个棋子的位置
	if (!_moveChessmens.empty() && _moveChessmens.size() > 1)
	{
		ChessmanNode* chessman1 = dynamic_cast<ChessmanNode*>(_moveChessmens.at(0));
		ChessmanNode* chessman2 = dynamic_cast<ChessmanNode*>(_moveChessmens.at(1));
		int type1 = chessman1->getOpponentType(), type2 = chessman1->getChessmanType(), index = chessman1->getIndex();
		CCLOG("one type1 = %d type2 = %d index = %d", type1, type2, index);
		if (chessman2->getOpponentType() == Config::pc)
		{
			int i = 0;
			for each (auto var in _pcChessmans)
			{
				if (dynamic_cast<ChessmanNode*>(var)->getIndex() == index) {
					_pcChessmans.erase(_pcChessmans.begin() + i);
					break;
				}
				i++;
			}
		}
		
		chessman1->clearChessman(chessman2->getIndex());
		chessman2->setChessType(type1, type2, index);
		CCLOG("san type1 = %d type2 = %d index = %d", type1, type2, index);
		//修改下一个下棋的人
		setCurrentOpponent(opponentType == Config::pc ? Config::player : Config::pc);
		_moveChessmens.erase(_moveChessmens.begin());
		_moveChessmens.erase(_moveChessmens.begin());
	}
}


