#include "PcAi.h"
#include "view\ChessmanNode.h"
#include "config\Config.h"
#include <math.h>

int PcAi::_nextIndex = 0;

PcAi::PcAi()
{
	
}

PcAi::~PcAi()
{
}

int PcAi::startAi(int opponentType = Config::pc)
{
	auto vec = GameManager::GetIns()->getChessmans(opponentType);
	int index = -1;
	int leftIndex = 0, rightIndex = 0, topIndex = 0, bottomIndex = 0;
	_nextIndex = Config::nullChessman;
	std::vector<int> nextIndex = { leftIndex ,rightIndex ,topIndex,bottomIndex };
	for (int var = 0; var < vec.size(); var++)
	{
		auto node = dynamic_cast<ChessmanNode*>(vec.at(var));
		if (node->isOpen())
		{
			leftIndex += PcAi::leftAi(node->getIndex());
			rightIndex += PcAi::rightAi(node->getIndex());
			topIndex += PcAi::topAi(node->getIndex());
			bottomIndex += PcAi::bottomAi(node->getIndex());
			index = var;
		}
		else
		{
			index++;
		}
	}
	std::sort(nextIndex.begin(), nextIndex.end(), [](int i1, int i2)->bool {
		return i1 > i2;
	});
	if (index == vec.size() - 1)
	{
		index = random(0, index);
	}
	else
	{
		if (nextIndex.at(0) == leftIndex)
		{
			_nextIndex = index - 1;
		}
		else if (nextIndex.at(0) == rightIndex) {
			_nextIndex = index + 1;
		}
		else if (nextIndex.at(0) == topIndex) {
			_nextIndex = index + Config::column;
		}
		else if (nextIndex.at(0) == bottomIndex) {
			_nextIndex = index - Config::column;
		}
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
		CCLOG("top at = %d floor = %f k = d", at, ceil(3.1), k);
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
	int k = ceil(index / (float)Config::column) - 1,i = 1;
	auto vec = GameManager::GetIns()->getAllChessmans();
	auto chessman = dynamic_cast<ChessmanNode*>(vec.at(index));
	for (int var = 0; var < k ; var++)
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