#include "Headers.h"

//#include "extensions/GUI/CCScrollView/CCScrollView.h"

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
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    //==========================================================================//
    
    //==========================================================================//
    
//    SimpleAudioEngine::getInstance()->stopEffect(Idea_Sound);
//    SimpleAudioEngine::getInstance()->stopEffect(VocalSound);
    
    main_bg=Sprite::create("mainscreen_bg.png");
    main_bg->setPosition(visibleSize/2);
    this->addChild(main_bg);
    
    Particals=ParticleSystemQuad::create("BG_Part.plist");
    Particals->setPosition(Vec2(384,512));
    this->addChild(Particals);
    
    
    
    #pragma mark - ======== Character  ===================
    
    Char=Sprite::create("Main_Char_1.png");
    Char->setAnchorPoint(Vec2(0.1,0.2));
    Char->setPosition(Vec2(20,0));
    this->addChild(Char,2);
    
    #pragma mark - ======== Character  ===================
    
    
    Title_1=Sprite::create("mainscreen_title.png");
    Title_1->setPosition(Vec2(500,780+1024));
    this->addChild(Title_1,3);
    
    Title_1->runAction(EaseBackInOut::create(MoveBy::create(1.0, Vec2(0,-1024))));
    
    
    play_btn=Sprite::create("mainscreen_play_btn.png");
    play_btn->setPosition(Vec2(600,450-1024));
    play_btn->setScale(1,0.75);
    this->addChild(play_btn,5);
    
    play_btn->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1.0, 1,1),
                                                               ScaleTo::create(1.0, 0.75,0.75),NULL)));
    
    
    More_btn=Sprite::create("More_BTN.png");
    More_btn->setPosition(Vec2(70,960+300));
    More_btn->setScale(1,0.75);
    this->addChild(More_btn,5);

    Star_btn=Sprite::create("Star_BTN.png");
    Star_btn->setPosition(Vec2(384,960+300));
    Star_btn->setScale(1,0.75);
    this->addChild(Star_btn,5);
    
    Sound_btn=Sprite::create("Sound_On_BTN.png");
    Sound_btn->setPosition(Vec2(700,960+300));
    Sound_btn->setScale(1,0.75);
    this->addChild(Sound_btn,5);
    
    if (MUSIC==0)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        Sound_btn->setTexture("Sound_Off_BTN.png");
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        Sound_btn->setTexture("Sound_On_BTN.png");
    }
    
    //==========================================================================//
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //==========================================================================//
    
    this->scheduleOnce(schedule_selector(HelloWorld::Load_Title), 1.5f);
    this->scheduleOnce(schedule_selector(HelloWorld::load_btn), 1.0f);

    this->scheduleOnce(SEL_SCHEDULE(&HelloWorld::Close_Eyes), 3.0);
    this->schedule(schedule_selector(HelloWorld::Jelly_Effect), 3.0f);
    
    return true;
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK){
        
        AdCall_Jni::BackButtonClicked();
    }
}


void HelloWorld::Open_Eyes()
{
    Char->setTexture("Main_Char_1.png");
    
    this->scheduleOnce(SEL_SCHEDULE(&HelloWorld::Close_Eyes), 3.0);
}

void HelloWorld::Close_Eyes()
{
    Char->setTexture("Main_Char_2.png");
    
    this->scheduleOnce(SEL_SCHEDULE(&HelloWorld::Open_Eyes), 0.1);
}

void HelloWorld::Jelly_Effect(float ft)
{
    Title_1->stopAllActions();
    Title_1->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0,-20)),
                                        MoveBy::create(0.2, Vec2(0,20)),NULL));
}

void HelloWorld::load_btn(float dt)
{
    play_btn->runAction(EaseBackInOut::create(MoveTo::create(1.0, Vec2(600,450))));
    
    More_btn->runAction(EaseBackInOut::create(MoveTo::create(2.0, Vec2(70,960))));
    Star_btn->runAction(EaseBackInOut::create(MoveTo::create(2.0, Vec2(384,960))));
    Sound_btn->runAction(EaseBackInOut::create(MoveTo::create(2.0, Vec2(700,960))));
}
void HelloWorld::Load_Title(float dt)
{
//    if (MUSIC==1)
//    {
//        VocalSound = SimpleAudioEngine::getInstance()->playEffect("Title_Sound.mp3");
//    }
}

void HelloWorld::sound_method()
{
    if (MUSIC==1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        Sound_btn->setTexture("Sound_Off_BTN.png");
        MUSIC=0;
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        Sound_btn->setTexture("Sound_On_BTN.png");
        MUSIC=1;
    }
}

void HelloWorld::BTN_Part(Sprite *S)
{
    Button_Part=ParticleSystemQuad::create("Button_Part.plist");
    Button_Part->setPosition(S->getPosition());
    this->addChild(Button_Part,100);
}



bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    touchPoint = convertToNodeSpace(touchPoint);
    
    if (play_btn->getBoundingBox().containsPoint(touchPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Play_S.mp3");
            }
            
            HelloWorld::BTN_Part(play_btn);
            
            //play_btn->runAction(Sequence::create(ScaleTo::create(0.2, 1,1),
                                                // ScaleTo::create(0.2, 0.75,0.75),NULL));
            
            auto scene1 = DressUpScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene1));
        }
        
        if (More_btn->getBoundingBox().containsPoint(touchPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Tap_1.mp3");
            }
            
            //More_btn->runAction(Sequence::create(ScaleTo::create(0.2, 1,1),
                                                 //ScaleTo::create(0.2, 0.75,0.75),NULL));
            
            HelloWorld::BTN_Part(More_btn);
            AdCall_Jni::MoreGame();
            
        }
        
        if (Star_btn->getBoundingBox().containsPoint(touchPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Tap_1.mp3");
            }
            
            //Star_btn->runAction(Sequence::create(ScaleTo::create(0.2, 1,1),
                                                // ScaleTo::create(0.2, 0.75,0.75),NULL));
            
            HelloWorld::BTN_Part(Star_btn);
            AdCall_Jni::RateGame();
            
        }
        
        if (Sound_btn->getBoundingBox().containsPoint(touchPoint))
        {
            if (MUSIC==1)
            {
                SimpleAudioEngine::getInstance()->playEffect("Tap_1.mp3");
            }
            
            HelloWorld::BTN_Part(Sound_btn);
            
            //Sound_btn->runAction(Sequence::create(ScaleTo::create(0.2, 1,1),
                                    //              ScaleTo::create(0.2, 0.75,0.75),NULL));
            
            HelloWorld::sound_method();
        }
    
    
    return true;
}


void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    touchPoint = convertToNodeSpace(touchPoint);
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    touchPoint = touch->getLocationInView();
    touchPoint = Director::getInstance()->convertToGL(touchPoint);
    touchPoint = convertToNodeSpace(touchPoint);
    
    CCLOG("x==>%f,y==>%f",touchPoint.x,touchPoint.y);
    
}


//void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
//{
//    cocos2d::log("touch cancelled");
//}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
