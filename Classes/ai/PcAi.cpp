#include "PcAi.h"
#include "view\ChessmanNode.h"
#include "config\Config.h"
#include <math.h>

int PcAi::_nextIndex = 0;

typedef std::map<int, std::vector<int>> PAIR;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	auto itr1 = lhs.begin()->second.at(1);
	auto itr2 = rhs.begin()->second.at(1);
	return itr1 > itr2;
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
	std::map<int, std::vector<std::vector<int>>> _chessInfoMap;
	std::vector<std::map<int, std::vector<int>>> _chessSortVec;
	std::map<int, std::vector<std::vector<int>>>::iterator itr;
	auto vec = GameManager::GetIns()->getChessmans(opponentType);
	int leftIndex = 0, rightIndex = 0, topIndex = 0, bottomIndex = 0, index = 0;
	_nextIndex = Config::nullChessman;

	for (unsigned int var = 0; var < vec.size(); var++)
	{
		auto node = dynamic_cast<ChessmanNode*>(vec.at(var));
		if (node->isOpen())
		{
			_chessInfoMap[var] = std::vector<std::vector<int>>{ PcAi::leftAi(node->getIndex()) ,PcAi::rightAi(node->getIndex()), PcAi::topAi(node->getIndex()) ,PcAi::bottomAi(node->getIndex()) };
		}
		else
		{
			_indexs.push_back(var);
		}
	}
	for (itr = _chessInfoMap.begin(); itr != _chessInfoMap.end(); itr++)
	{
		std::sort(itr->second.begin(), itr->second.end(), [](std::vector<int> i1, std::vector<int> i2)->bool {
			return i1.at(1) > i2.at(1);
		});
		std::map<int, std::vector<int>> map;
		map[itr->first] = itr->second.at(0);
		_chessSortVec.push_back(map);
	}
	std::sort(_chessSortVec.begin(), _chessSortVec.end(), cmp_by_value);

	if (_indexs.size() == vec.size())
	{
		index = _indexs.at(random(0, (int)_indexs.size() - 1));
	}
	else
	{	//如果没有可以行动的棋子
		if (_chessSortVec.at(0).begin()->second.at(1) <= 0)
		{
			index = _indexs.at(random(0, (int)_indexs.size() - 1));
		}
		else
		{
			index = _chessSortVec.at(0).begin()->first;
			_nextIndex = PcAi::getNextDirectionIndex(index, _chessSortVec.at(0).begin()->second.at(0),1);
		}
	}
	CCLOG("index = %d ***** _nextIndex = %d", index, _nextIndex);
	return index;
}

std::vector<int> PcAi::leftAi(int index)
{
	int k = Config::column - (ceil((index + 1) / (float)Config::column) * Config::column - index - 1);
	auto dirs = PcAi::ai(index, k, Config::left);
	return dirs;
}

std::vector<int> PcAi::rightAi(int index)
{
	int k = ceil((index + 1) / (float)Config::column) * Config::column - index - 1;
	auto dirs = PcAi::ai(index, k, Config::left);
	return dirs;
}

std::vector<int> PcAi::topAi(int index)
{
	int k = Config::row - ceil(index / (float)Config::column);
	auto dirs = PcAi::ai(index, k, Config::left);
	return dirs;
}

std::vector<int> PcAi::bottomAi(int index)
{
	int k = ceil(index / (float)Config::column) - 1, i = 1;
	auto dirs = PcAi::ai(index, k, Config::left);
	return dirs;
}

std::vector<int> PcAi::ai(int index, int key, int dir)
{
	int type = Config::zero;
	std::vector<int> _dirs;
	auto vec = GameManager::GetIns()->getAllChessmans();
	auto chessman = dynamic_cast<ChessmanNode*>(vec.at(index));
	for (int var = 0; var < key; var++)
	{
		int at = index - PcAi::getNextDirectionIndex(index, dir, var + 1);
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
	_dirs.push_back(dir);
	_dirs.push_back(type);
	return _dirs;
}

int PcAi::getNextDirectionIndex(int index, int dir, int num)
{
	int _index = 0;
	switch (dir)
	{
	case Config::left:
		_index = _index - (1 * num);
		break;
	case Config::right:
		_index = _index + (1 * num);
		break;
	case Config::top:
		_index = _index + Config::column * num;
		break;
	case Config::botom:
		_index = _index - Config::column * num;
		break;
	default:
		break;
	}
	return _index;
}
