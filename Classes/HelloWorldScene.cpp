#include "HelloWorldScene.h"
#include "GameWinScene.hpp"
#include "GameOverScene.hpp"

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) // LayerColor::initWithColor(Color4B(248, 248, 248, 248) //0, 0, 0, 0
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    float _cit = 1.5;
    closeItem->setScale(_cit);
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - _cit*closeItem->getContentSize().width/2,
                                origin.y + _cit*closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("2D-X Plane", "fonts/Marker Felt.ttf", 24);
    auto score_board = Label::create();
    auto level_board = Label::create();
    star_img = Director::getInstance()->getTextureCache()->addImage("res/star.png");
    auto star_board = Sprite::createWithTexture(star_img);
    auto star_cal = Label::createWithTTF(StringUtils::format("x%d", this->star), "fonts/Marker Felt.ttf", 12);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - 2*label->getContentSize().height));
    score_board->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height - 3*label->getContentSize().height -
                                  1.2*score_board->getContentSize().height));
    score_board->setSystemFontName("fonts/Marker Felt.ttf");
    score_board->setSystemFontSize(18);
    level_board->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height - 3.75*label->getContentSize().height -
                                  level_board->getContentSize().height));
    level_board->setSystemFontName("fonts/Marker Felt.ttf");
    level_board->setSystemFontSize(15);
    float _star_margin = MAX(star_board->getContentSize().height/2, star_cal->getContentSize().height/2);
    star_board->setPosition(Vec2(origin.x + visibleSize.width - star_board->getContentSize().width/2,
                           origin.y + visibleSize.height - _star_margin));
    star_cal->setPosition(Vec2(star_board->getPositionX() - star_board->getContentSize().width/2 -
                               star_cal->getContentSize().width/2,
                               star_board->getPositionY() - 1));
    
    // text color
    label->setTextColor(Color4B(55, 55, 55, 55));
    score_board->setTextColor(Color4B(55, 55, 55, 55));
    level_board->setTextColor(Color4B(155, 155, 155, 155));
    star_cal->setTextColor(Color4B(18, 18, 18, 100));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    this->addChild(score_board, 1);
    this->addChild(level_board, 1);
    this->addChild(star_board, 1);
    this->addChild(star_cal, 1);
    

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

    // add "icon" splash
    auto icon_img = Director::getInstance()->getTextureCache()->addImage("res/icon72x72.png");
    auto sprite = Sprite::createWithTexture(icon_img);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.2);
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // add plane
    img = Director::getInstance()->getTextureCache()->addImage("res/plane.png");
    const float _w_img = 256.0, _h_img = 256.0;
    float _cst = MAX(img->getContentSize().width / _w_img, img->getContentSize().height/ _h_img);
    float _start_height = 30;
    /*
     <SubTexture name="hero_1" x="66" y="168" width="62" height="68"/>
     <SubTexture name="hero_2" x="2" y="168" width="62" height="75"/>
     */
    auto plane = Sprite::create();
    plane->setTexture(img);
    plane->setTextureRect(Rect(66*_cst, 168*_cst, 62*_cst, 68*_cst));
    plane->setTag(1);
    plane->setPosition(Vec2(origin.x + /*plane->getContentSize().width/2 +
                            random(0.0f, visibleSize.width - plane->getContentSize().width)*/
                            visibleSize.width/2,
                            origin.y + plane->getContentSize().height/2 + _start_height));
    
    this->addChild(plane, 2);
    
    schedule([plane, _cst](float f){
        if (plane->getTag()) {
            plane->setTag(0);
            plane->setTextureRect(Rect(66*_cst, 168*_cst, 62*_cst, 68*_cst));
        } else {
            plane->setTag(1);
            plane->setTextureRect(Rect(2*_cst, 168*_cst, 62*_cst, 75*_cst));
        }
        
    }, 0.5, "Shining");
    
    // add star
//    schedule([this, visibleSize, origin](float f){
//        auto free_star = Sprite::createWithTexture(star_img);
//        float _star_x = random(free_star->getContentSize().width/2,
//                              visibleSize.width - free_star->getContentSize().width/2);
//        free_star->setPosition(origin.x + _star_x,
//                               origin.y + visibleSize.height + free_star->getContentSize().height/2);
//        this->addChild(free_star, 1);
//        ccBezierConfig bzf;
//        auto conf_1 = random(3.0f, 12.0f);
//        auto conf_2 = random(3.0f, 12.0f);
//        auto conf_3 = random(3.0f, 12.0f);
//        auto conf_4 = random(3.0f, 12.0f);
//        bzf.endPosition = Vec2(origin.x + random(free_star->getContentSize().width/2,
//                                                 visibleSize.width - free_star->getContentSize().width/2),
//                               origin.y - free_star->getContentSize().height/2);
//        bzf.controlPoint_1 = Vec2(free_star->getPositionX() + random(-conf_1*free_star->getContentSize().width,
//                                                                     conf_2*free_star->getContentSize().width),
//                                  2*free_star->getPositionY()/3);
//        bzf.controlPoint_2 = Vec2(free_star->getPositionX() + random(-conf_3*free_star->getContentSize().width,
//                                                                     conf_4*free_star->getContentSize().width),
//                                  free_star->getPositionY()/3);
//        auto Bezier = BezierTo::create(random(3.0f, 6.0f), bzf);
//        free_star->runAction();
//        return false;
//    }, 5.0, "More Stars");
    

    schedule([this, visibleSize, origin, plane, score_board](float f){
        score_board->setString(StringUtils::format("%d", _score));
        // move plane
        if (_touch_flag) {
            auto _dir = Vec2(_touch_p.x - plane->getPositionX(), _touch_p.y - plane->getPositionY());
            _dir.normalize();
            plane->setPosition(plane->getPosition() + _dir*_plane_sp);
        }
    }, "Action");
    
    
    ////////////////////////////
    // add listener (x2)
    //   tp, au
    //
    // move plane : Touches
    auto tp_listen = EventListenerTouchAllAtOnce::create();
    tp_listen->onTouchesMoved = [this, plane](const std::vector<Touch*>& touches, Event *event){
        // onTouchesMoved : update _touch_p
        auto t = touches[0];
        _touch_p = t->getLocation();
    };
    tp_listen->onTouchesEnded = [this](const std::vector<Touch*>& touches, Event *event){
        _touch_flag = false;
    };
    tp_listen->onTouchesBegan = [this, plane](const std::vector<Touch*>& touches, Event *event){
        auto t = touches[0];
        if (!plane->getBoundingBox().containsPoint(t->getLocation())) {
            _touch_flag = true;
            _touch_p = t->getLocation();
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tp_listen, 1);
    
    // audio
    auto audio = SimpleAudioEngine::getInstance();
    audio->preloadEffect("res/explosion.mp3");
    audio->preloadEffect("res/shoot.mp3");
    audio->preloadBackgroundMusic("res/dance_to_the_death.mp3");
    
    audio->setEffectsVolume(0.5);
    audio->setBackgroundMusicVolume(0.95);
    
    // pause: x="184" y="117" width="30" height="29"
    auto pauser = Sprite::createWithTexture(img, Rect(184*_cst, 117*_cst, 30*_cst, 29*_cst));
    pauser->setPosition(Vec2(origin.x + 32*_cst*3,
                             origin.y + visibleSize.height - 32*_cst));
    pauser->setScale(1.85);
    pauser->setTag(1); // 1: running; 0: stopped
    this->addChild(pauser);
    
    /*
     <SubTexture name="pause_button" x="175" y="148" width="22" height="23"/>
     <SubTexture name="resume_button" x="216" y="145" width="25" height="27"/>
     */
    auto audio_button = Sprite::create();
    audio_button->setTexture(img);
    if (this->audio_count) {
        audio_button->setTextureRect(Rect(175*_cst, 148*_cst, 22*_cst, 23*_cst));
    } else {
        audio_button->setTextureRect(Rect(216*_cst, 145*_cst, 25*_cst, 27*_cst));
    }
    audio_button->setPosition(Vec2(origin.x + 32*_cst,
                                   origin.y + visibleSize.height - 32*_cst));
    audio_button->setScale(2.0);
    this->addChild(audio_button);
    
    auto au_listen = EventListenerTouchOneByOne::create();
    au_listen->onTouchBegan = [this, audio, audio_button, pauser, _cst](Touch *t, Event *event){
        if (pauser->getTag() && audio_button->getBoundingBox().containsPoint(t->getLocation())) {
            if (this->audio_count) {
                if (audio->isBackgroundMusicPlaying()) {
                    audio->pauseBackgroundMusic();
                    audio_button->setTag(1);
                }
                audio_button->setTextureRect(Rect(216*_cst, 145*_cst, 25*_cst, 27*_cst));
                this->audio_count = 0;
            } else {
                if (audio_button->getTag() == 1) {
                    audio->resumeBackgroundMusic();
                } else {
                    audio->playBackgroundMusic("res/dance_to_the_death.mp3", true);
                }
                audio_button->setTag(5);
                audio_button->setTextureRect(Rect(175*_cst, 148*_cst, 22*_cst, 23*_cst));
                this->audio_count = 1;
            }
        } else if (pauser->getBoundingBox().containsPoint(t->getLocation())) {
            if (pauser->getTag() == 1) {
                audio->pauseAllEffects();
                audio->pauseBackgroundMusic();
                Director::getInstance()->stopAnimation();
                pauser->setTag(0);
            } else {
                if (this->audio_count) {
                    audio->resumeAllEffects();
                    audio->resumeBackgroundMusic();
                }
                Director::getInstance()->startAnimation();
                pauser->setTag(1);
            }
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(au_listen, -128);
    
    
    if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() && this->audio_count) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("res/dance_to_the_death.mp3", true);
    }
    
    // add bullets
    // red: Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst)
    // black: Rect(66*_cst, 237*_cst, 7*_cst, 20*_cst)
    schedule([this, audio, visibleSize, origin, _cst, plane](float f){
        
        float dur_time = 0.8; // time to fly through height
        Sprite *bullet;
        // level == 1
        if (_level == 1) {
            bullet = Sprite::createWithTexture(img, Rect(66*_cst, 237*_cst, 7*_cst, 20*_cst));
        } else if (_level > 2) {
            bullet = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
        }
        if (_level == 1 || _level > 2) {
            auto fly = MoveTo::create((visibleSize.height - bullet->getPositionY()) / (visibleSize.height/dur_time),
                                      Vec2(plane->getPositionX(),
                                           origin.y + visibleSize.height + bullet->getContentSize().height/2));
            
            bullet->setPosition(Vec2(plane->getPositionX(),
                                     plane->getPositionY() + bullet->getContentSize().height));
            bullet->runAction(Sequence::create(fly,
                                               CallFunc::create([this, bullet](){
                this->removeChild(bullet);
                this->_bullets.eraseObject(bullet);
            }),
                                               NULL)); // add explosion
            bullet->setTag(12);
            
            this->_bullets.pushBack(bullet);
            this->addChild(bullet, 1);
        }
        
        // upgrade: 1
        if (this->_score >= level1) {
            auto p1 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f1 = MoveTo::create((visibleSize.height - p1->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() - plane->getContentSize().width/4,
                                          visibleSize.height + p1->getContentSize().height/2));
            p1->setPosition(Vec2(plane->getPositionX() - plane->getContentSize().width/4,
                                 plane->getPositionY() + p1->getContentSize().height));
            p1->runAction(Sequence::create(f1,
                                           CallFunc::create([this, p1](){
                this->removeChild(p1);
                this->_bullets.eraseObject(p1);
            }),
                                           NULL)); // add explosion
            p1->setTag(12);
            this->_bullets.pushBack(p1);
            this->addChild(p1, 1);
            
            auto p2 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f2 = MoveTo::create((visibleSize.height - p2->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() + plane->getContentSize().width/4,
                                          visibleSize.height + p2->getContentSize().height/2));
            p2->setPosition(Vec2(plane->getPositionX() + plane->getContentSize().width/4,
                                 plane->getPositionY() + p2->getContentSize().height));
            p2->runAction(Sequence::create(f2,
                                           CallFunc::create([this, p2](){
                this->removeChild(p2);
                this->_bullets.eraseObject(p2);
            }),
                                          NULL)); // add explosion
            p2->setTag(12);
            this->_bullets.pushBack(p2);
            this->addChild(p2, 1);
        }
        
        // upgrade: 2
        if (this->_score >= level2) {
            auto p1 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f1 = MoveTo::create((visibleSize.height - p1->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() - plane->getContentSize().width/2,
                                          visibleSize.height + p1->getContentSize().height/2));
            p1->setPosition(Vec2(plane->getPositionX() - plane->getContentSize().width/2,
                                 plane->getPositionY()));
            p1->runAction(Sequence::create(f1,
                                           CallFunc::create([this, p1](){
                this->removeChild(p1);
                this->_bullets.eraseObject(p1);
            }),
                                           NULL)); // add explosion
            p1->setTag(12);
            this->_bullets.pushBack(p1);
            this->addChild(p1, 1);
            
            auto p2 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f2 = MoveTo::create((visibleSize.height - p2->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() + plane->getContentSize().width/2,
                                          visibleSize.height + p2->getContentSize().height/2));
            p2->setPosition(Vec2(plane->getPositionX() + plane->getContentSize().width/2,
                                 plane->getPositionY()));
            p2->runAction(Sequence::create(f2,
                                           CallFunc::create([this, p2](){
                this->removeChild(p2);
                this->_bullets.eraseObject(p2);
            }),
                                           NULL)); // add explosion
            p2->setTag(12);
            this->_bullets.pushBack(p2);
            this->addChild(p2, 1);
        }
        
        // upgrade: 3
        if (this->_score >= level3) {
            auto p1 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f1 = MoveTo::create((visibleSize.height - p1->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() - 2*plane->getContentSize().width,
                                          visibleSize.height + p1->getContentSize().height/2));
            p1->setPosition(Vec2(plane->getPositionX() - plane->getContentSize().width/4,
                                 plane->getPositionY()));
            p1->runAction(Sequence::create(f1,
                                           CallFunc::create([this, p1](){
                this->removeChild(p1);
                this->_bullets.eraseObject(p1);
            }),
                                           NULL)); // add explosion
            p1->setTag(12);
            this->_bullets.pushBack(p1);
            this->addChild(p1, 1);
            
            auto p2 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f2 = MoveTo::create((visibleSize.height - p2->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() + 2*plane->getContentSize().width,
                                          visibleSize.height + p2->getContentSize().height/2));
            p2->setPosition(Vec2(plane->getPositionX() + plane->getContentSize().width/4,
                                 plane->getPositionY()));
            p2->runAction(Sequence::create(f2,
                                           CallFunc::create([this, p2](){
                this->removeChild(p2);
                this->_bullets.eraseObject(p2);
            }),
                                           NULL)); // add explosion
            p2->setTag(12);
            this->_bullets.pushBack(p2);
            this->addChild(p2, 1);
        }
        
        // upgrade: 4
        if (this->_score >= level4) {
            auto p1 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f1 = MoveTo::create((visibleSize.height - p1->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() - 4*plane->getContentSize().width,
                                          visibleSize.height + p1->getContentSize().height/2));
            p1->setPosition(Vec2(plane->getPositionX() - plane->getContentSize().width/2,
                                 plane->getPositionY()));
            p1->runAction(Sequence::create(f1,
                                           CallFunc::create([this, p1](){
                this->removeChild(p1);
                this->_bullets.eraseObject(p1);
            }),
                                           NULL)); // add explosion
            p1->setTag(12);
            this->_bullets.pushBack(p1);
            this->addChild(p1, 1);
            
            auto p2 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f2 = MoveTo::create((visibleSize.height - p2->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() + 4*plane->getContentSize().width,
                                          visibleSize.height + p2->getContentSize().height/2));
            p2->setPosition(Vec2(plane->getPositionX() + plane->getContentSize().width/2,
                                 plane->getPositionY()));
            p2->runAction(Sequence::create(f2,
                                           CallFunc::create([this, p2](){
                this->removeChild(p2);
                this->_bullets.eraseObject(p2);
            }),
                                           NULL)); // add explosion
            p2->setTag(12);
            this->_bullets.pushBack(p2);
            this->addChild(p2, 1);
        }
        
        // upgrade: 5
        if (this->_score >= level5) {
            auto p1 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f1 = MoveTo::create((visibleSize.height - p1->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() - 6*plane->getContentSize().width,
                                          visibleSize.height + p1->getContentSize().height/2));
            p1->setPosition(Vec2(plane->getPositionX() - plane->getContentSize().width/2,
                                 plane->getPositionY()));
            p1->runAction(Sequence::create(f1,
                                           CallFunc::create([this, p1](){
                this->removeChild(p1);
                this->_bullets.eraseObject(p1);
            }),
                                           NULL)); // add explosion
            p1->setTag(12);
            this->_bullets.pushBack(p1);
            this->addChild(p1, 1);
            
            auto p2 = Sprite::createWithTexture(img, Rect(112*_cst, 2*_cst, 9*_cst, 17*_cst));
            auto f2 = MoveTo::create((visibleSize.height - p2->getPositionY()) / (visibleSize.height/dur_time),
                                     Vec2(plane->getPositionX() + 6*plane->getContentSize().width,
                                          visibleSize.height + p2->getContentSize().height/2));
            p2->setPosition(Vec2(plane->getPositionX() + plane->getContentSize().width/2,
                                 plane->getPositionY()));
            p2->runAction(Sequence::create(f2,
                                           CallFunc::create([this, p2](){
                this->removeChild(p2);
                this->_bullets.eraseObject(p2);
            }),
                                           NULL)); // add explosion
            p2->setTag(12);
            this->_bullets.pushBack(p2);
            this->addChild(p2, 1);
        }
        
    }, shoot_freq, "Shoot");
    
    
    // upgrade enemy
    schedule([this, level_board, star_cal](float f){
        
        if (this->_score > level1) {
            // _score
            this->_score_b = 1500;
            this->_score_m = 1000;
            this->_score_s = 100;
            // freq
            this->freq_b = 5.5;
            this->freq_m = 2.8;
            this->freq_s = 0.75;
            // _HP++
            this->_HP_b = 12;
            this->_HP_m = 5;
            this->_HP_s = 2;
            // level
            _level = 2;
            // speed
            _plane_sp = 1.7;
            // shoot
            shoot_freq = 0.15;
        }
        if (this->_score > level2) {
            // _score
            this->_score_b = 2000;
            this->_score_m = 800;
            this->_score_s = 100;
            // freq
            this->freq_b = 5.0;
            this->freq_m = 2.5;
            this->freq_s = 0.7;
            // _HP++
            this->_HP_b = 20;
            this->_HP_m = 7;
            this->_HP_s = 3;
            // level
            _level = 3;
            // speed
            _plane_sp = 2.0;
            // shoot
            shoot_freq = 0.2;
        }
        if (this->_score > level3) {
            // _score
            this->_score_b = 2000;
            this->_score_m = 800;
            this->_score_s = 200;
            // freq
            this->freq_b = 4.7;
            this->freq_m = 2.4;
            this->freq_s = 0.65;
            // _HP++
            this->_HP_b = 24;
            this->_HP_m = 12;
            this->_HP_s = 5;
            // level
            _level = 4;
            // speed
            _plane_sp = 2.4;
            // shoot
            shoot_freq = 0.12;
        }
        if (this->_score > level4) {
            // _score
            this->_score_b = 2750;
            this->_score_m = 1200;
            this->_score_s = 100;
            // freq
            this->freq_b = 4.2;
            this->freq_m = 2.0;
            this->freq_s = 0.58;
            // _HP++
            this->_HP_b = 36;
            this->_HP_m = 18;
            this->_HP_s = 7;
            // level
            _level = 5;
            // speed
            _plane_sp = 3.0;
            // shoot
            shoot_freq = 0.18;
        }
        if (this->_score > level5) {
            // _score
            this->_score_b = 2750;
            this->_score_m = 1200;
            this->_score_s = 300;
            // freq
            this->freq_b = 4.0;
            this->freq_m = 1.8;
            this->freq_s = 0.5;
            // _HP++
            this->_HP_b = 40;
            this->_HP_m = 20;
            this->_HP_s = 10;
            // level
            _level = 6;
            // speed
            _plane_sp = 3.0;
            // shoot
            shoot_freq = 0.15;
        }
        
        level_board->setString(StringUtils::format("Level %d", this->_level));
        star_cal->setString(StringUtils::format("x%d", this->star));
        
    }, "More Targets");
    
    // add target_plane
    // name="enemy_b" Rect(2*_cst, 2*_cst, 108*_cst, 164*_cst)
    // name="enemy_m" Rect(130*_cst, 2*_cst, 69*_cst, 89*_cst)
    // name="enemy_s" Rect(201*_cst, 88*_cst, 39*_cst, 27*_cst)
    schedule([this, visibleSize, origin, _cst](float f){
        
        auto target = Sprite::createWithTexture(img, Rect(2*_cst, 2*_cst, 108*_cst, 164*_cst));
        float dur_time = random(15.0, 20.0); // time to fly through height
        if (this->_score > level1) {
            dur_time -= 1;
        }
        if (this->_score > level2) {
            dur_time -= 1;
        }
        if (this->_score > level3) {
            dur_time -= 1.5;
        }
        if (this->_score > level4) {
            dur_time -= 1.5;
        }
        if (this->_score > level5) {
            dur_time -= 2;
        }
        float _tar_x = random(target->getContentSize().width/2,
                              visibleSize.width - target->getContentSize().width/2);
        
        auto fly = MoveTo::create(dur_time, Vec2(origin.x + _tar_x,
                                                 origin.y - target->getContentSize().height/2));
        
        target->setPosition(Vec2(origin.x + _tar_x,
                                 origin.y + visibleSize.height + target->getContentSize().height/2));
        target->runAction(Sequence::create(fly,
                                           CallFunc::create([this, target](){
            this->removeChild(target);
            this->_targets_b.eraseObject(target);
            this->star -= 3;
        }),
                                           NULL));
        target->setTag(100+_HP_b);
        
        this->_targets_b.pushBack(target);
        this->addChild(target, 2);
        
    }, freq_b, "Enemy_b");
    
    schedule([this, visibleSize, origin, _cst](float f){
        
        auto target = Sprite::createWithTexture(img, Rect(130*_cst, 2*_cst, 69*_cst, 89*_cst));
        float dur_time = random(7.5, 11.5); // time to fly through height
        if (this->_score > level1) {
            dur_time -= 0.3;
        }
        if (this->_score > level2) {
            dur_time -= 0.5;
        }
        if (this->_score > level3) {
            dur_time -= 0.5;
        }
        if (this->_score > level4) {
            dur_time -= 0.7;
        }
        if (this->_score > level5) {
            dur_time -= 1.0;
        }
        float _tar_x = random(target->getContentSize().width/2,
                              visibleSize.width - target->getContentSize().width/2);
        
        auto fly = MoveTo::create(dur_time, Vec2(origin.x + _tar_x,
                                                 origin.y - target->getContentSize().height/2));
        
        target->setPosition(Vec2(origin.x + _tar_x,
                                 origin.y + visibleSize.height + target->getContentSize().height/2));
        target->runAction(Sequence::create(fly,
                                           CallFunc::create([this, target](){
            this->removeChild(target);
            this->_targets_m.eraseObject(target);
            this->star -= 2;
        }),
                                           NULL));
        target->setTag(100+_HP_m);
        
        this->_targets_m.pushBack(target);
        this->addChild(target, 2);
        
    }, freq_m, "Enemy_m");
    
    schedule([this, visibleSize, origin, _cst](float f){
        
        auto target = Sprite::createWithTexture(img, Rect(201*_cst, 88*_cst, 39*_cst, 27*_cst));
        float dur_time = random(5.5, 9.0); // time to fly through height
        if (this->_score > level1) {
            dur_time -= 0.3;
        }
        if (this->_score > level2) {
            dur_time -= 0.3;
        }
        if (this->_score > level3) {
            dur_time -= 0.4;
        }
        if (this->_score > level4) {
            dur_time -= 0.5;
        }
        if (this->_score > level5) {
            dur_time -= 0.5;
        }
        float _tar_x = random(target->getContentSize().width/2,
                              visibleSize.width - target->getContentSize().width/2);
        
        auto fly = MoveTo::create(dur_time, Vec2(origin.x + _tar_x,
                                                 origin.y - target->getContentSize().height/2));
        
        target->setPosition(Vec2(origin.x + _tar_x,
                                 origin.y + visibleSize.height + target->getContentSize().height/2));
        target->runAction(Sequence::create(fly,
                                           CallFunc::create([this, target](){
            this->removeChild(target);
            this->_targets_s.eraseObject(target);
            this->star -= 1;
        }),
                                           NULL));
        target->setTag(100+_HP_s);
        
        this->_targets_s.pushBack(target);
        this->addChild(target, 2);
        
    }, freq_s, "Enemy_s");
    
    
    // collision dectection
    // name="explosion_01" Rect(216*_cst, 117*_cst, 26*_cst, 26*_cst)
    // name="explosion_02" Rect(144*_cst, 93*_cst, 38*_cst, 39*_cst)
    // name="explosion_03" Rect(201*_cst, 44*_cst, 40*_cst, 42*_cst)
    schedule([this, audio, visibleSize, origin, _cst](float f){
    
        Vector<Sprite*> _t_b2del;
        for (auto _t_b : this->_targets_b) {
            auto _t_rect = _t_b->getBoundingBox();
            // check all bullets
            Vector<Sprite*> bullet2del;
            for (auto _bul : this->_bullets) {
                if (_t_rect.intersectsRect(_bul->getBoundingBox())) {
                    bullet2del.pushBack(_bul);
                    _t_b->setTag(_t_b->getTag()-1);
                }
            }
            if (_t_b->getTag() <= 100) {
                _t_b2del.pushBack(_t_b);
            }
            // del bullets
            for (auto _bul : bullet2del) {
                this->removeChild(_bul);
                this->_bullets.eraseObject(_bul);
            }
        }
        // del target_b
        for (auto _t_b : _t_b2del) {
            this->_targets_b.eraseObject(_t_b);
            // add explosion
            auto exp = Sprite::createWithTexture(img, Rect(201*_cst, 44*_cst, 40*_cst, 42*_cst));
            exp->setPosition(Vec2(_t_b->getPositionX(), _t_b->getPositionY()-_t_b->getContentSize().height/4));
            this->addChild(exp);
            if (audio_count) {
                audio->playEffect("res/explosion.mp3");
            }
            exp->runAction(Sequence::create(
                                            MoveBy::create(0.5, Vec2(0, 0)),
                                            // ShuffleTiles::create(0.8, Size(180, 180), 5),
                                            CallFunc::create([this, exp](){ this->removeChild(exp);}),
                                            NULL));
            this->removeChild(_t_b);
            _score += _score_b;
        }

        Vector<Sprite*> _t_m2del;
        for (auto _t_m : this->_targets_m) {
            auto _t_rect = _t_m->getBoundingBox();
            // check all bullets
            Vector<Sprite*> bullet2del;
            for (auto _bul : this->_bullets) {
                if (_t_rect.intersectsRect(_bul->getBoundingBox())) {
                    bullet2del.pushBack(_bul);
                    _t_m->setTag(_t_m->getTag()-1);
                }
            }
            if (_t_m->getTag() <= 100) {
                _t_m2del.pushBack(_t_m);
            }
            // del bullets
            for (auto _bul : bullet2del) {
                this->removeChild(_bul);
                this->_bullets.eraseObject(_bul);
            }
        }
        // del target_m
        for (auto _t_m : _t_m2del) {
            this->_targets_m.eraseObject(_t_m);
            // add explosion
            auto exp = Sprite::createWithTexture(img, Rect(144*_cst, 93*_cst, 38*_cst, 39*_cst));
            exp->setPosition(Vec2(_t_m->getPositionX(), _t_m->getPositionY()-_t_m->getContentSize().height/4));
            this->addChild(exp);
            if (audio_count) {
                audio->playEffect("res/explosion.mp3");
            }
            exp->runAction(Sequence::create(
                                            MoveBy::create(0.3, Vec2(0, 0)),
                                            // ShuffleTiles::create(0.5, Size(180, 180), 5),
                                            CallFunc::create([this, exp](){ this->removeChild(exp);}),
                                            NULL));
            this->removeChild(_t_m);
            _score += _score_m;
        }

        Vector<Sprite*> _t_s2del;
        for (auto _t_s : this->_targets_s) {
            auto _t_rect = _t_s->getBoundingBox();
            // check all bullets
            Vector<Sprite*> bullet2del;
            for (auto _bul : this->_bullets) {
                if (_t_rect.intersectsRect(_bul->getBoundingBox())) {
                    bullet2del.pushBack(_bul);
                    _t_s->setTag(_t_s->getTag()-1);
                }
            }
            if (_t_s->getTag() <= 100) {
                _t_s2del.pushBack(_t_s);
            }
            // del bullets
            for (auto _bul : bullet2del) {
                this->removeChild(_bul);
                this->_bullets.eraseObject(_bul);
            }
        }
        // del target_s
        for (auto _t_s : _t_s2del) {
            this->_targets_s.eraseObject(_t_s);
            // add explosion
            auto exp = Sprite::createWithTexture(img, Rect(216*_cst, 117*_cst, 26*_cst, 26*_cst));
            exp->setPosition(Vec2(_t_s->getPositionX(), _t_s->getPositionY()-_t_s->getContentSize().height/4));
            this->addChild(exp);
            if (audio_count) {
                audio->playEffect("res/shoot.mp3");
            }
            exp->runAction(Sequence::create(
                                            MoveBy::create(0.2, Vec2(0, 0)),
                                            // ShuffleTiles::create(0.3, Size(180, 180), 5),
                                            CallFunc::create([this, exp](){ this->removeChild(exp);}),
                                            NULL));
            this->removeChild(_t_s);
            _score += _score_s;
        }
    
    }, "Collision");
    
    
    // scene: game over or scene: win
    schedule([this, audio, visibleSize, origin, plane, _cst, tp_listen, au_listen](float f){
        
        auto plane_box = plane->getBoundingBox();
        bool boooom = false;
        
        for (auto _t_b : this->_targets_b) {
            if (plane_box.intersectsRect(_t_b->getBoundingBox())) {
                boooom = true;
                break;
            }
        }
        if (!boooom) {
            for (auto _t_m : this->_targets_m) {
                if (plane_box.intersectsRect(_t_m->getBoundingBox())) {
                    boooom = true;
                    break;
                }
            }
        }
        if (!boooom) {
            for (auto _t_s : this->_targets_s) {
                if (plane_box.intersectsRect(_t_s->getBoundingBox())) {
                    boooom = true;
                    break;
                }
            }
        }
        if (boooom || this->star <= 0) {
            // remove Listener
            Director::getInstance()->getEventDispatcher()->removeEventListener(tp_listen);
            Director::getInstance()->getEventDispatcher()->removeEventListener(au_listen);
            // audio->stopBackgroundMusic();
            // game over
            this->unschedule("Game Final");
            this->unschedule("Change Background");
            this->unschedule("Enemy_b");
            this->unschedule("Enemy_m");
            this->unschedule("Enemy_s");
            this->unschedule("More Targets");
            this->unschedule("Shoot");
            this->unschedule("Shining");
            this->unschedule("Action");
            // this->unschedule("More Stars");
            // add death explosion
            plane->setTextureRect(Rect(201*_cst, 44*_cst, 40*_cst, 42*_cst));
            plane->setScale(2.0);
            if (audio_count) {
                audio->playEffect("res/explosion.mp3");
            }
            plane->runAction(Sequence::create(
                                            MoveBy::create(0.8, Vec2(0, 0)),
                                            // ShuffleTiles::create(0.8, Size(10, 10), 5),
                                            CallFunc::create([this, plane](){
                this->removeChild(plane);
                auto _game_over = GameOverScene::createScene(this->_score);
                //this->retain();
                this->unscheduleAllCallbacks();
                auto trans = TransitionFlipAngular::create(1.0, _game_over);
                Director::getInstance()->replaceScene(trans);
            }),
                                            NULL));
        } else if (this->_score >= level5 && this->star > 0) {
            // remove Listener
            Director::getInstance()->getEventDispatcher()->removeEventListener(tp_listen);
            Director::getInstance()->getEventDispatcher()->removeEventListener(au_listen);
            // audio->stopBackgroundMusic();
            // game win
            this->unschedule("Game Final");
            this->unschedule("Change Background");
            this->unschedule("Enemy_b");
            this->unschedule("Enemy_m");
            this->unschedule("Enemy_s");
            this->unschedule("More Targets");
            this->unschedule("Shoot");
            this->unschedule("Shining");
            this->unschedule("Action");
            // this->unschedule("More Stars");
            plane->runAction(Sequence::create(
                                                MoveTo::create(1.2, Vec2(plane->getPositionX(),
                                                                         origin.y + visibleSize.height +
                                                                         plane->getContentSize().height/2)),
                                                // ShuffleTiles::create(0.3, Size(180, 180), 5),
                                                CallFunc::create([this, plane](){
                this->removeChild(plane);
                auto _game_win = GameWinScene::createScene(this->_score);
                this->unscheduleAllCallbacks();
                auto trans = TransitionFlipAngular::create(1.0, _game_win);
                Director::getInstance()->replaceScene(trans);
            }),
                                                NULL));
        }

    }, "Game Final");

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    this->unscheduleAllCallbacks();
    SimpleAudioEngine::getInstance()->stopAllEffects();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
