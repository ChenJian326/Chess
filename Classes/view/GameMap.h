#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__
#include "cocos2d.h"
using namespace cocos2d;
class GameMap :public Node
{
public:
	GameMap();
	~GameMap();
	CREATE_FUNC(GameMap);
	//static Node* createMap();
private:
	virtual bool init();
	void initChess();
	int nodeId;
	std::vector<int> opponets;
	std::vector<int> chessmans;
};


#endif