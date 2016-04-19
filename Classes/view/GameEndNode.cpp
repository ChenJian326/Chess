#include "GameEndNode.h"

GameEndNode::GameEndNode()
	:_winType(Config::pc)
{
}

GameEndNode::GameEndNode(int winType)
{
	_winType = winType;
}

GameEndNode::~GameEndNode()
{
}

bool GameEndNode::init()
{
	if (!Node::init()) {
		return false;
	}
	if (_winType == Config::pc)
	{

	}
	return true;
}
