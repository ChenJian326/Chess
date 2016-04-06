#include "MainScene.h"
#include "config\VisibleRect.h"
#include "scene\GameScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto startBtn = MenuItemFont::create("star game", CC_CALLBACK_1(MainScene::startGameCallback, this));
	auto menu = Menu::create(startBtn, nullptr);
	menu->setPosition(VisibleRect::center());
	this->addChild(menu);
	return true;
}

void MainScene::startGameCallback(Ref* pSender) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
