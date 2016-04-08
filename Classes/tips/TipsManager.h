#ifndef __TIPS_MANAGER_H__
#define __TIPS_MANAGER_H__
#include "cocos2d.h"
#include "config\Config.h"
#include "config\VisibleRect.h"
USING_NS_CC;
class TipsManager
{
public:
	TipsManager();
	~TipsManager();
	static void showTips(const char* str,int fontSzie = 22, Color3B color = Color3B::WHITE,float time = 1.2);
	static void showRedTips(const char* str, int fontSzie = 22, float time = 1.2);
	static void showBlackTips(const char* str, int fontSzie = 22, float time = 1.2);
private:

};

#endif