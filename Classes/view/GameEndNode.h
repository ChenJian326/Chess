#ifndef __GAME_END_NODE_H__
#define __GAME_END_NODE_H__
#include "cocos2d.h"
#include "config\Config.h"

USING_NS_CC;
class GameEndNode :public Node
{
public:
	GameEndNode();
	~GameEndNode();
	CREATE_FUNC(GameEndNode);
private:
	bool virtual init();
	void continueGame(Ref* pSender);
	void exitGame(Ref* pSender);
	int _winType;
};



#endif // !__GAME_END_NODE_H__

