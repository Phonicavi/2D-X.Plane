//
//  Ball.hpp
//  Cocos2d-Widget
//
//  Created by ChiuPhonic on 16/7/17.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Ball : public cocos2d::Sprite {

public:
    virtual bool init();
    
    CREATE_FUNC(Ball);
    
// CREATE_FUNC: similar to below
    
//    static Ball *create() {
//
//        Ball *ball = new Ball();
//        ball->init();
//        ball->autorelease();
//
//        return ball;
//    }
    
    // if not add to 'autorelease'
    /*
     
     Object *obj = new Object();
     obj->autorelease();
     
     */
    // then: need
    /*
     {
        obj->retain();
        
        // TODO
     
        obj->release();
     
     }
     */
};

#endif /* Ball_hpp */
