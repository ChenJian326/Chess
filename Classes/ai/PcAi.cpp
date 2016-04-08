#include "PcAi.h"
#include "view\ChessmanNode.h"
#include "config\Config.h"
#include <math.h>

int PcAi::_nextIndex = 0;

typedef std::map<int, int> PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	auto itr1 = lhs.begin();
	auto itr2 = rhs.begin();
	return itr1->second > itr2->second;
}

PcAi::PcAi()
{

}

PcAi::~PcAi()
{
}

int PcAi::startAi(int opponentType = Config::pc)
{
	std::vector<int> _indexs;
	std::map<int, std::vector<int>> _chessInfoMap;
	std::vector<std::map<int, int>> _chessSortVec;
	std::map<int, std::vector<int>>::iterator itr;

	auto vec = GameManager::GetIns()->getChessmans(opponentType);
	int leftIndex = 0, rightIndex = 0, topIndex = 0, bottomIndex = 0, index = 0;
	_nextIndex = Config::nullChessman;
	for (int var = 0; var < vec.size(); var++)
	{
		auto node = dynamic_cast<ChessmanNode*>(vec.at(var));
		if (node->isOpen())
		{
			leftIndex = PcAi::leftAi(node->getIndex());
			rightIndex = PcAi::rightAi(node->getIndex());
			topIndex = PcAi::topAi(node->getIndex());
			bottomIndex = PcAi::bottomAi(node->getIndex());
			_chessInfoMap[var] = std::vector<int>{ leftIndex ,rightIndex,topIndex ,bottomIndex };
		}
		else
		{
			_indexs.push_back(var);
		}
	}

	for (itr = _chessInfoMap.begin(); itr != _chessInfoMap.end(); itr++)
	{
		std::sort(itr->second.begin(), itr->second.end(), [](int i1, int i2)->bool {
			return i1 > i2;
		});
		std::map<int, int> map;
		map[itr->first] = itr->second.at(0);
		_chessSortVec.push_back(map);
	}
	std::sort(_chessSortVec.begin(), _chessSortVec.end(), cmp_by_value);

	if (_indexs.size() == vec.size())
	{
		index = _indexs.at(random(0, (int)_indexs.size() - 1));
	}
	else
	{
		index = _chessSortVec.at(0).begin()->first;
	}
	CCLOG("index = %d ***** _nextIndex = %d", index, _nextIndex);
	return index;
}

int PcAi::leftAi(int index)
{
	int type = Config::zero;
	int k = Config::column - (ceil((index + 1) / (float)Config::column) * Config::column - index - 1);
	auto vec = GameManager::GetIns()->getAllChessmans();
	auto chessman = dynamic_cast<ChessmanNode*>(vec.at(index));
	for (int var = 0; var < k; var++)
	{
		auto node = dynamic_cast<ChessmanNode*>(vec.at(index - (var + 1)));
		if (!node->isOpen())
		{
			type = Config::zero;
			break;
		}
		else
		{
			if (node->getOpponentType() == chessman->getOpponentType())
			{
				type = Config::zero;
				break;
			}
			if (chessman->getOpponentType() != node->getOpponentType() && chessman->getChessmanType() <= node->getChessmanType())
			{
				type = Config::seven - var;
				break;
			}
		}
	}
	return type;
}

int PcAi::rightAi(int index)
{
	int type = Config::zero;
	int k = ceil((index + 1) / (float)Config::column) * Config::column - index - 1;
	auto vec = GameManager::GetIns()->getAllChessmans();
	auto chessman = dynamic_cast<ChessmanNode*>(vec.at(index));
	for (int var = 0; var < k; var++)
	{
		auto node = dynamic_cast<ChessmanNode*>(vec.at(index + (var + 1)));
		if (!node->isOpen())
		{
			type = Config::zero;
			break;
		}
		else
		{
			if (node->getOpponentType() == chessman->getOpponentType())
			{
				type = Config::zero;
				break;
			}
			if (chessman->getOpponentType() != node->getOpponentType() && chessman->getChessmanType() <= node->getChessmanType())
			{
				type = Config::seven - var;
				break;
			}
		}
	}
	return type;
}

int PcAi::topAi(int index)
{
	int type = Config::zero;
	int i = 1;
	int k = Config::row - ceil(index / (float)Config::column);
	auto vec = GameManager::GetIns()->getAllChessmans();
	auto chessman = dynamic_cast<ChessmanNode*>(vec.at(index));
	for (int var = 0; var < k; var++)
	{
		int at = index + (Config::column * i) - 1;
		auto node = dynamic_cast<ChessmanNode*>(vec.at(at));
		if (!node->isOpen())
		{
			type = Config::zero;
			break;
		}
		else
		{
			if (node->getOpponentType() == chessman->getOpponentType())
			{
				type = Config::zero;
				break;
			}
			if (chessman->getOpponentType() != node->getOpponentType() && chessman->getChessmanType() <= node->getChessmanType())
			{
				type = Config::seven - var;
				break;
			}
		}
		i++;
	}
	return type;
}

int PcAi::bottomAi(int index)
{
	int type = Config::zero;
	int k = ceil(index / (float)Config::column) - 1, i = 1;
	auto vec = GameManager::GetIns()->getAllChessmans();
	auto chessman = dynamic_cast<ChessmanNode*>(vec.at(index));
	for (int var = 0; var < k; var++)
	{
		int at = index - (Config::column * i) - 1;
		auto node = dynamic_cast<ChessmanNode*>(vec.at(at));
		if (!node->isOpen())
		{
			type = Config::zero;
			break;
		}
		else
		{
			if (node->getOpponentType() == chessman->getOpponentType())
			{
				type = Config::zero;
				break;
			}
			if (chessman->getOpponentType() != node->getOpponentType() && chessman->getChessmanType() <= node->getChessmanType())
			{
				type = Config::seven - var;
				break;
			}
		}
	}
	return type;
}
