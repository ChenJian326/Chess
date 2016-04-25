#include "PcAi.h"
#include "view\ChessmanNode.h"
#include "config\Config.h"
#include <math.h>
typedef std::map<int, std::vector<int>> PAIR;

int PcAi::_direction = 0;
std::vector<int>   PcAi::_chessIndexs = {};
std::vector<Node*> PcAi::_allChessman = GameManager::GetIns()->getAllChessmans();
static bool _isInit = false;
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	auto itr1 = lhs.begin()->second.at(1);
	auto itr2 = rhs.begin()->second.at(1);
	return itr1 > itr2;
}

PcAi::PcAi()
{
	CCLOG("");
}

PcAi::~PcAi()
{
}

int PcAi::startAi(int opponentType = Config::pc)
{
	std::map<int, std::vector<std::vector<int>>> _chessInfoMap;
	std::vector<std::map<int, std::vector<int>>> _chessSortVec;
	std::map<int, std::vector<std::vector<int>>>::iterator itr;
	auto vec = GameManager::GetIns()->getChessmans(opponentType);
	int chessIndex = 0, index = 0;
	_direction = Config::nullChessman;
	if (_allChessman.size() <= 0)
	{
		_allChessman = GameManager::GetIns()->getAllChessmans();
	}
	for (unsigned int var = 0; var < vec.size(); var++)
	{
		auto node = dynamic_cast<ChessmanNode*>(vec.at(var));
		if (node->isOpen())
		{
			chessIndex = node->getIndex();
			_chessInfoMap[node->getIndex()] = std::vector<std::vector<int>>{ PcAi::leftAi(chessIndex) ,PcAi::rightAi(chessIndex), PcAi::topAi(chessIndex) ,PcAi::bottomAi(chessIndex) };
		}
		else if (_isInit)
		{
			_chessIndexs.push_back(node->getIndex());
			//	CCLOG("_chessIndexs push index = %d", node->getIndex());
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

	if (_chessIndexs.size() == vec.size())
	{
		index = _chessIndexs.at(random(0, (int)_chessIndexs.size() - 1));
	}
	else
	{	//如果没有可以行动的棋子
		if (_chessSortVec.at(0).begin()->second.at(1) <= 0)
		{
			index = _chessIndexs.at(random(0, (int)_chessIndexs.size() - 1));
		}
		else
		{
			index = _chessSortVec.at(0).begin()->first;
			_direction = _chessSortVec.at(0).begin()->second.at(0);
		}
	}
	//CCLOG("[startAi] index = %d ***** _direction = %d", index, _direction);
	_isInit = false;
	return index;
}

void PcAi::initChessIndex()
{
	if (!_chessIndexs.empty() && _chessIndexs.size() > 0)
	{
		_chessIndexs.erase(_chessIndexs.begin(), _chessIndexs.end());
	}
	_isInit = true;
}

std::vector<int> PcAi::leftAi(int index)
{
	int k = Config::column - (ceil((index + 1) / (float)Config::column) * Config::column - index);
	auto dirs = PcAi::ai(index, k, Config::left);
	return dirs;
}

std::vector<int> PcAi::rightAi(int index)
{
	int k = ceil((index + 1) / (float)Config::column) * Config::column - index - 1;
	auto dirs = PcAi::ai(index, k, Config::right);
	return dirs;
}

std::vector<int> PcAi::topAi(int index)
{
	int k = Config::row - ceil((index + 1) / (float)Config::column);
	auto dirs = PcAi::ai(index, k, Config::top);
	return dirs;
}

std::vector<int> PcAi::bottomAi(int index)
{
	int k = ceil((index + 1) / (float)Config::column) - 1;
	auto dirs = PcAi::ai(index, k, Config::botom);
	return dirs;
}

std::vector<int> PcAi::ai(int index, int key, int dir)
{
	int number = Config::zero;
	std::vector<int> _dirs;
	auto chessman = dynamic_cast<ChessmanNode*>(_allChessman.at(index));
	for (int var = 0; var < key; var++)
	{
		int at = PcAi::getNextDirectionIndex(index, dir, var + 1);
		auto node = dynamic_cast<ChessmanNode*>(_allChessman.at(at));
		if (!node->isOpen())
		{
			number = -1;
			break;
		}
		else
		{
			//两个棋子类型相同
			if (node->getOpponentType() == chessman->getOpponentType())
			{
				number = -1;
				break;
			}
			//一个可以吃的棋子
			else if (chessman->getChessmanType() <= node->getChessmanType() || (chessman->getChessmanType() == Config::soldiers && node->getChessmanType() == Config::handsome))
			{
				number = Config::seven - var;
				break;
			}
			//如果遇到比自己大的
			else if (chessman->getChessmanType() >= node->getChessmanType())
			{
				number = Config::zero;
				auto var = PcAi::changeDirection(dir, index);
				if (var != -1){
					dir = var;
					number = Config::one;
				}
				break;
			}
			else
			{
				//寻找其余两个个方向可以吃的
				if (PcAi::inDepth(at, chessman->getChessmanType(), dir))
				{
					number = Config::five - var;
				}
				//如果下一个棋子是无效的棋子
				else if (node->getChessmanType() == Config::nullChessman)
				{
					number = Config::zero;
				}
			}
		}
	}
	_dirs.push_back(dir);
	_dirs.push_back(number);
	return _dirs;
}
bool PcAi::inDepth(int index, int chessmanType, int dir)
{
	bool isInDepth = false;
	std::vector<int> dirVec = { Config::left,Config::right,Config::top,Config::botom };
	if (dir == Config::left || dir == Config::right)
	{
		dirVec.erase(dirVec.begin(), dirVec.begin() + 1);
	}
	else
	{
		dirVec.erase(dirVec.begin() + 2, dirVec.end());
	}
	for (unsigned int i = 0; i < dirVec.size(); i++)
	{
		int at = PcAi::getNextDirectionIndex(index, dirVec.at(i), 1);
		if (at > 31 || at < 0)
		{
			break;
		}
		auto node = dynamic_cast<ChessmanNode*>(_allChessman.at(at));
		if (chessmanType <= node->getChessmanType() || (chessmanType == Config::soldiers && node->getChessmanType() == Config::handsome))
		{
			isInDepth = true;
			break;
		}
	}
	return isInDepth;
}
int PcAi::changeDirection(int dir, int index)
{
	int direction = -1;
	std::vector<int> dirVec = { Config::left,Config::right,Config::top,Config::botom };
	dirVec.erase(dirVec.begin() + dir);
	for (unsigned int i = 0; i < dirVec.size(); i++)
	{
		int at = PcAi::getNextDirectionIndex(index, dirVec.at(i), 1);
		if (at > 31 || at < 0)
		{
			break;
		}
		auto node = dynamic_cast<ChessmanNode*>(_allChessman.at(at));
		if (node->getChessmanType() == Config::nullChessman)
		{
			direction = dirVec.at(i);
			break;
		}
	}
	//CCLOG("changeDirection direction = %d", direction);
	return direction;
}
int PcAi::clearOrFindChessIndex(int index, bool isFind)
{
	unsigned int length = _chessIndexs.size();
	int findIndex = -1;
	for (unsigned int i = 0; i < length; i++)
	{
		if (_chessIndexs.at(i) == index) {
			if (isFind)
			{
				findIndex = i;
			}
			else
			{
				_chessIndexs.erase(_chessIndexs.begin() + i);
			}
			break;
		}
	}
	return findIndex;
}

int PcAi::getNextDirectionIndex(int index, int dir, int num)
{
	int _index = 0;
	switch (dir)
	{
	case Config::left:
		_index = index - (1 * num);
		break;
	case Config::right:
		_index = index + (1 * num);
		break;
	case Config::top:
		_index = index + Config::column * num;
		break;
	case Config::botom:
		_index = index - Config::column * num;
		break;
	default:
		break;
	}
	return _index;
}
