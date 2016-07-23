//
//  WelcomeScene.cpp
//  2D-X.Plane
//
//  Created by ChiuPhonic on 16/7/23.
//
//

#include "WelcomeScene.hpp"
#include "HelloWorldScene.h"

Scene* WelcomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool WelcomeScene::init()
{
    if ( !Layer::init() ) // LayerColor::initWithColor(Color4B(248, 248, 248, 248) //0, 0, 0, 0
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(WelcomeScene::menuCloseCallback, this));
    float _cit = 1.5;
    closeItem->setScale(_cit);
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - _cit*closeItem->getContentSize().width/2,
                                origin.y + _cit*closeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto label = Label::createWithTTF("2D-X Plane", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + 2*visibleSize.height/3 - 1.5*label->getContentSize().height));
    label->setTextColor(Color4B(55, 55, 55, 55));
    this->addChild(label, 1);
    
    // add button
    auto start = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 18);
    start->setPosition(origin.x + visibleSize.width/2,
                         origin.y + visibleSize.height/3);
    start->setTextColor(Color4B(155, 155, 155, 75));
    this->addChild(start, 1);
    
    auto listen = EventListenerTouchOneByOne::create();
    listen->onTouchBegan = [this, start, listen](Touch *t, Event *event){
        if (start->getBoundingBox().containsPoint(t->getLocation())) {
            Director::getInstance()->getEventDispatcher()->removeEventListener(listen);
            auto scene = HelloWorld::createScene();
            this->unscheduleAllCallbacks();
            auto trans = TransitionFlipAngular::create(1.0, scene);
            Director::getInstance()->replaceScene(trans);
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listen, this);
    
    
    // add Background
    back_01 = Director::getInstance()->getTextureCache()->addImage("res/bg_01.jpg");
    back_02 = Director::getInstance()->getTextureCache()->addImage("res/bg_02.jpg");
    auto bgi = Sprite::createWithTexture(back_01);
    bgi->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float _scale_times = MAX(visibleSize.width / bgi->getContentSize().width,
                             visibleSize.height / bgi->getContentSize().height);
    bgi->setScale(_scale_times);
    this->addChild(bgi, 0);
    
    schedule([this, bgi](float f){
        if (bgf) {
            bgi->setTexture(back_02);
            bgf = false;
        } else {
            bgi->setTexture(back_01);
            bgf = true;
        }
    }, 15.0, "Change Background");
    
    return true;
}


void WelcomeScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    this->unscheduleAllCallbacks();
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}