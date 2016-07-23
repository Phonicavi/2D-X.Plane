//
//  WelcomeScene.hpp
//  2D-X.Plane
//
//  Created by ChiuPhonic on 16/7/23.
//
//

#ifndef WelcomeScene_hpp
#define WelcomeScene_hpp

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public cocos2d::Layer
{
private:
    bool bgf = false;
    
    cocos2d::Texture2D *back_01;
    cocos2d::Texture2D *back_02;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene);
};


#endif /* WelcomeScene_hpp */
