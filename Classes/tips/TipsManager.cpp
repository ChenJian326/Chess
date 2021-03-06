#include "TipsManager.h"

TipsManager::TipsManager()
{
}

TipsManager::~TipsManager()
{
}

void TipsManager::showTips(const char* str, int fontSzie, Color3B color, float time)
{
	auto label = Label::createWithSystemFont(Config::GBKTOUTF8(str), GAME_FONE_NAME, fontSzie);
	label->setColor(color);
	label->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y + 100));
	label->setCascadeOpacityEnabled(true);
	label->runAction(
		Sequence::create(
			DelayTime::create(2.0),
			EaseExponentialOut::create(
				Spawn::create(
					MoveTo::create(time, Vec2(VisibleRect::center().x, VisibleRect::top().y)),
					FadeOut::create(time),
					nullptr
				)
			),
			RemoveSelf::create(),
			nullptr));
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
