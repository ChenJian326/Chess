#ifndef __DISPLAY_TOOLS_H__
#define __DISPLAY_TOOLS_H__
#include "cocos2d.h"
USING_NS_CC;
class DisplayTools
{
public:
	DisplayTools();
	~DisplayTools();
	static Label* createLabel(const char* str, int fontSize = 18,Vec2 pos = Vec2::ZERO,Vec2 apos = Vec2(0.5,0.5), Color3B color = Color3B::WHITE);
	static Node* createNode();
private:

};

#endif // !__DISPLAY_TOOLS_H__
