#ifndef __GAME_INFO_NODE_H__
#define __GAME_INFO_NODE_H__
#include "cocos2d.h"
USING_NS_CC;
class GameInfoNode :public Node
{
public:
	GameInfoNode();
	~GameInfoNode();
	void showCountdown(float td);
	void stopCountdown();
	CREATE_FUNC(GameInfoNode);
private:
	bool virtual init();
	int _countdown;
	Label* _countdownLb;
	Label* _pcInfo;
	Label* _playerInfo;
	Label* _currentInfo;
};

#endif
