#include "EventManager.h"
#include <new>

const std::string EventManager::EVENT_NEXT_COUNTDOWN = "EVENT_NEXT_COUNTDOWN";
const std::string EventManager::EVENT_UPDATE_SCORE = "EVENT_UPDATE_SCORE";
const std::string EventManager::EVENT_GAME_END = "EVENT_GAME_END";
static EventManager* _ins;
EventManager::EventManager()
{
	_eventDispatcher = Director::getInstance()->getEventDispatcher();
}

EventManager::~EventManager()
{
}

EventManager * EventManager::getIns()
{
	if (nullptr == _ins)
	{
		_ins = new (std::nothrow) EventManager();
	}
	return _ins;
}

void EventManager::dispatchEvent(std::string name, void* data)
{
	EventCustom event(name);
	event.setUserData(data);
	_eventDispatcher->dispatchEvent(&event);
}
//
void EventManager::addEventListener(std::string name, std::string eventName,std::function<void(EventCustom*)> CallBackFunc, Node * node)
{
	auto custom = EventListenerCustom::create(name, CallBackFunc);
	if (nullptr == node)
	{
		_eventDispatcher->addEventListenerWithFixedPriority(custom,1);
		if ("" != eventName)
		{
			_events[eventName] = custom;
		}
	}
	else
	{
		_eventDispatcher->addEventListenerWithSceneGraphPriority(custom, node);
	}	
}

void EventManager::removeEventListener(std::string eventName)
{
	if (_events[eventName])
	{
		_eventDispatcher->removeEventListener(_events[eventName]);
		_events[eventName] = nullptr;
	}
}
