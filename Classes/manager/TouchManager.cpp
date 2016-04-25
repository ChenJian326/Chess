#include "TouchManager.h"
#include <new>
#include "config\Config.h"
static TouchManager *_ins = nullptr;
//
TouchManager::TouchManager()
	:_touchNode(nullptr)
{
}

TouchManager::~TouchManager()
{
}

TouchManager * TouchManager::getIns()
{
	if (nullptr == _ins)
	{
		_ins = new(std::nothrow) TouchManager();

	}
	return _ins;
}

void TouchManager::addTouchNode(Node *node, std::function<void()> func)
{
	_callBackFuncMap[node->getName()] = func;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchManager::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchManager::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchManager::onTouchEnded, this);
	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

void TouchManager::removeTouchs()
{
	_callBackFuncMap.erase(_callBackFuncMap.begin(), _callBackFuncMap.end());
}

bool TouchManager::onTouchBegan(Touch* touch, Event* event)
{
	bool isTouch = false;
	auto touchNode = event->getCurrentTarget();
	Rect rect;
	rect.size = touchNode->getContentSize();
	auto camera = Camera::getVisitingCamera();
	isTouch = isScreenPointInRect(touch->getLocation(), camera, touchNode->getWorldToNodeTransform(), rect, nullptr);
	CCLOG("%s %s", "onTouchBegan", Config::GBKToUTF8(touchNode->getName().c_str()));
	return isTouch;
}

void TouchManager::onTouchMoved(Touch* touch, Event* event)
{
	//CCLOG("move mouse x = %f y = %f", touch->getLocation().x, touch->getLocation().y);
}

void TouchManager::onTouchEnded(Touch* touch, Event* event)
{
	auto touchNode = event->getCurrentTarget();
	if (!touchNode->getBoundingBox().containsPoint(touchNode->getParent()->convertToNodeSpace(touch->getLocation()))) {
		return;
	}
	if (!_callBackFuncMap.empty() && _callBackFuncMap[touchNode->getName()])
	{
		_callBackFuncMap[touchNode->getName()]();
	}
}
