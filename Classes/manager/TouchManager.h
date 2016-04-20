#ifndef __TOUCH_MANAGER_H__
#define __TOUCH_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class TouchManager
{
public:
	TouchManager();
	~TouchManager();
	static TouchManager* getIns();
	void addTouchNode(Node *node,std::function<void()> func);
	void removeTouchs();
private:
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	Node *_touchNode;
	std::map<std::string,std::function<void()>> _callBackFuncMap;
};


#endif // !__TOUCH_MANAGER_H__

