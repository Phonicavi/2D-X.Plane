#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer
{
private:
    int _score;
    int _score_b;
    int _score_m;
    int _score_s;
    bool _touch_flag;
    
    cocos2d::Vec2 _touch_p;
    
    cocos2d::Texture2D *img;
    
    cocos2d::Vector<Sprite*> _bullets;
    cocos2d::Vector<Sprite*> _targets_b;
    cocos2d::Vector<Sprite*> _targets_m;
    cocos2d::Vector<Sprite*> _targets_s;
    
    int level1 = 5000;
    int level2 = 10000;
    int level3 = 20000;
    int level4 = 50000;
    int level5 = 100000;
    float freq_b, freq_m, freq_s;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
};

#endif // __HELLOWORLD_SCENE_H__
