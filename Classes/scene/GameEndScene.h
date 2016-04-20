#ifndef __GAME_ENE_SCENE_H__
#define __GAME_ENE_SCENE_H__
#include "cocos2d.h"
#include "config\Config.h"
USING_NS_CC;
class GameEndScene :public Scene
{
public:
	GameEndScene();
	~GameEndScene();
	CREATE_FUNC(GameEndScene);
private:
	bool virtual init();
	int _winType;
};

#endif