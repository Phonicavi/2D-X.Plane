//
//  GameWinScene.hpp
//  CocosBall
//
//  Created by ChiuPhonic on 16/7/19.
//
//

#ifndef GameWinScene_hpp
#define GameWinScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GameWinScene : public cocos2d::Layer
{
public:
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameWinScene);
    
    static cocos2d::Scene *createScene();
    static cocos2d::Scene *createScene(int _score);
};

#endif /* GameWinScene_hpp */
