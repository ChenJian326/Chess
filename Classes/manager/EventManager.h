#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__
#include <string>

#include "cocos2d.h"
USING_NS_CC;


class EventManager
{
public:
	static const std::string EVENT_NEXT_COUNTDOWN;
	static const std::string EVENT_UPDATE_SCORE;
	static const std::string EVENT_GAME_END;
	EventManager();
	~EventManager();
	static EventManager* getIns();

	void dispatchEvent(std::string name, void* data);
	//name跟eventName最好不要一样
	void addEventListener(std::string name, std::string eventName , std::function<void(EventCustom*)> CallBackFunc, Node* node);
	void removeEventListener(std::string eventName);
private:
	EventDispatcher* _eventDispatcher;
	std::map<std::string, EventListenerCustom*> _events;
};



#endif // !__EVENT_MANAGER__

