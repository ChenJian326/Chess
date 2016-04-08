#include "TipsManager.h"

TipsManager::TipsManager()
{
}

TipsManager::~TipsManager()
{
}

void TipsManager::showTips(const char* str, int fontSzie, Color3B color, float time)
{
	auto label = Label::createWithSystemFont(Config::GBKToUTF8(str), "Î¢ÈíÑÅºÚ", fontSzie);
	label->setColor(color);
	label->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + 100));
	label->setCascadeOpacityEnabled(true);
	label->runAction(
		EaseExponentialOut::create(
			Sequence::create(
				Spawn::create(
					DelayTime::create(0.5),
					MoveTo::create(time, Vec2(VisibleRect::center().x, VisibleRect::top().y)),
					FadeOut::create(time),
					nullptr
					),
				RemoveSelf::create(),
				nullptr)));
	Director::getInstance()->getRunningScene()->addChild(label);
}

void TipsManager::showRedTips(const char * str, int fontSzie, float time)
{
	TipsManager::showTips(str, fontSzie, Color3B::RED, time);
}

void TipsManager::showBlackTips(const char * str, int fontSzie, float time)
{
	TipsManager::showTips(str, fontSzie, Color3B::BLACK, time);
}
