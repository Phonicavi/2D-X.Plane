//
//  GameOverScene.cpp
//  CocosBall
//
//  Created by ChiuPhonic on 16/7/17.
//
//

#include "GameOverScene.hpp"

USING_NS_CC;

bool GameOverScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // add background
    auto bgi = Sprite::create("res/bg_01.jpg");
    bgi->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float _scale_times = MAX(visibleSize.width / bgi->getContentSize().width,
                             visibleSize.height / bgi->getContentSize().height);
    bgi->setScale(_scale_times);
    this->addChild(bgi, 0);
    
    return true;
}

cocos2d::Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

cocos2d::Scene* GameOverScene::createScene(int _score)
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // add score_board
    auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
    auto score_board = Label::create();
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + label->getContentSize().height));
    score_board->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height/2 -
                                  1.2*score_board->getContentSize().height));
    score_board->setString(StringUtils::format("Total score: %d", _score));
    score_board->setSystemFontName("fonts/Marker Felt.ttf");
    score_board->setSystemFontSize(16);
    label->setTextColor(Color4B(55, 55, 55, 55));
    score_board->setTextColor(Color4B(55, 55, 55, 55));
    
    
    // add the label as a child to this layer
    layer->addChild(label, 1);
    layer->addChild(score_board, 1);
    
    scene->addChild(layer);
    return scene;
}


void GameOverScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

