#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameScene :public Node
{
public:
	GameScene();
	~GameScene();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
private:
	
};

#endif
