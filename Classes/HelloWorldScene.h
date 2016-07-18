#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer
{
private:
    int _score = 0;
    int _score_b = 1500;
    int _score_m = 800;
    int _score_s = 100;
    bool _touch_flag;
    
    cocos2d::Vec2 _touch_p;
    
    cocos2d::Texture2D *img;
    
    cocos2d::Vector<Sprite*> _bullets;
    cocos2d::Vector<Sprite*> _targets_b;
    cocos2d::Vector<Sprite*> _targets_m;
    cocos2d::Vector<Sprite*> _targets_s;
    
    int _HP_b = 8;
    int _HP_m = 3;
    int _HP_s = 1;
    
    float freq_b = 6.0;
    float freq_m = 3.0;
    float freq_s = 0.8;
    
    int _level = 1;
    int level1 = 20000;
    int level2 = 50000;
    int level3 = 100000;
    int level4 = 200000;
    int level5 = 5000000;
    
    float _plane_sp = 1.5;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
};

#endif // __HELLOWORLD_SCENE_H__
