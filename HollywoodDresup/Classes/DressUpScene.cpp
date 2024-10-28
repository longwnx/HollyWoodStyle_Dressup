#include "Headers.h"

using namespace cocos2d;
using namespace CocosDenshion;

USING_NS_CC;

Scene* DressUpScene::createScene()
{
    Scene *scene = Scene::create();
    DressUpScene *layer = DressUpScene::create();
    scene->addChild(layer);
    return scene;
}

bool DressUpScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //====================== Ads ==================================//
    
    //============================================================//
    
    BG_CHANGE=1;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
//    SimpleAudioEngine::getInstance()->stopEffect(Idea_Sound);
//    SimpleAudioEngine::getInstance()->stopEffect(VocalSound);
    
#pragma mark ==================== Sprite
    
    BG=Sprite::create("dressup_bg_1.png");
    BG->setPosition(visibleSize/2);
    this->addChild(BG);
    
    BG_Part=ParticleSystemQuad::create("BG_Part.plist");
    BG_Part->setPosition(Vec2(384,512));
    this->addChild(BG_Part);
    
    Char_body=Sprite::create(StringUtils::format("Dressup_Body_%d.png",SELECTED_CHAR));
    Char_body->setAnchorPoint(Vec2(0.5,0));
    Char_body->setPosition(Vec2(384,50));
    this->addChild(Char_body,1);
    
    Char_WEye=Sprite::create("Char_1_WEye.png");
    Char_WEye->setPosition(Char_body->getContentSize()/2);
    Char_body->addChild(Char_WEye);
    
    Char_Eye=Sprite::create("Char_1_Eye.png");
    Char_Eye->setPosition(Char_body->getContentSize()/2);
    Char_body->addChild(Char_Eye);
    
    Char_Liner=Sprite::create("Char_1_Liner.png");
    Char_Liner->setPosition(Char_body->getContentSize()/2);
    Char_body->addChild(Char_Liner);
    
    Char_EyeLash=Sprite::create("Char_1_EyeLash.png");
    Char_EyeLash->setPosition(Char_body->getContentSize()/2);
    Char_body->addChild(Char_EyeLash);
    
    Char_CEye=Sprite::create("Char_1_CEye.png");
    Char_CEye->setPosition(Char_body->getContentSize()/2);
    Char_CEye->setVisible(false);
    Char_body->addChild(Char_CEye);
    
    Char_Eyeshadow=Sprite::create("Char_1_EyeShadow.png");
    Char_Eyeshadow->setPosition(Char_body->getContentSize()/2);
    Char_Eyeshadow->setVisible(false);
    Char_body->addChild(Char_Eyeshadow);
    
    Char_Eyebrow=Sprite::create("Char_1_Eyebrow.png");
    Char_Eyebrow->setPosition(Char_body->getContentSize()/2);
    Char_body->addChild(Char_Eyebrow);
    
    
    
#pragma mark - ======== Character DressUp ===================
    
    for (int i=0,Y=950; i<9; i++)
    {
        Char_Item.push_back(SpriteWithHue::create(StringUtils::format("Char_Item_%d_%d.png",i+1,1)));
        Char_Item[i]->setPosition(Char_body->getContentSize()/2);
        Char_Item[i]->setVisible(false);
        Char_body->addChild(Char_Item[i]);
        
        Tool_Item.push_back(Sprite::create(StringUtils::format("Dressup_Tool_%d.png",i+1)));
        Tool_Item[i]->setPosition(Vec2(70,Y));
        this->addChild(Tool_Item[i],10);
        
        Y=Y-100;
    }
    
    Char_Item[2]->setVisible(true);
    Char_Item[5]->setVisible(true);
    
    Tool_Item[2]->setPosition(Vec2(70,950));
    Tool_Item[5]->setPosition(Vec2(70,850));
    Tool_Item[3]->setPosition(Vec2(70,750));
    Tool_Item[6]->setPosition(Vec2(70,650));
    Tool_Item[1]->setPosition(Vec2(70,550));
    Tool_Item[7]->setPosition(Vec2(70,450));
    Tool_Item[4]->setPosition(Vec2(70,350));
    Tool_Item[8]->setPosition(Vec2(70,250));
    Tool_Item[0]->setPosition(Vec2(70,150));
    
    
    
#pragma mark ==================== Slider
    
    slider = cocos2d::extension::ControlSlider::create("Hue_Slider.png","Hue_Slider.png" ,"Hue_Slider_BTN.png");
    slider->setAnchorPoint(Vec2(0.5f, 1.0f));
    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(6.8f);
    slider->setValue(0.2f);
    slider->setMaximumAllowedValue(6.5f);
    slider->setMinimumAllowedValue(0.2f);
    slider->setPosition(Vec2(50000,50000));
    slider->setRotation(90);
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(DressUpScene::valueChanged), cocos2d::extension::Control::EventType::VALUE_CHANGED);
    addChild(slider,40);
    
#pragma mark - ======== BTN
    
    Home_BTN=Button::create("Home_BTN.png","Home_BTN.png");
    Home_BTN->setPosition(Vec2(700,950));
    Home_BTN->setScale(1,0.75);
    Home_BTN->setTouchEnabled(true);
    this->addChild(Home_BTN,10);
    
    Done_BTN=Button::create("Done_BTN.png","Done_BTN.png");
    Done_BTN->setPosition(Vec2(570,950));
    Done_BTN->setScale(1,0.75);
    Done_BTN->setTouchEnabled(true);
    this->addChild(Done_BTN,10);
    
//    Camera_BTN=Button::create("Camera_BTN.png","Camera_BTN.png");
//    Camera_BTN->setPosition(Vec2(700+200,650));
//    Camera_BTN->setScale(1,0.75);
//    Camera_BTN->setTouchEnabled(false);
//    this->addChild(Camera_BTN,10);
    
    BG_BTN=Button::create("BG_BTN.png","BG_BTN.png");
    BG_BTN->setPosition(Vec2(700+200,800));
    BG_BTN->setScale(1,0.75);
    BG_BTN->setTouchEnabled(false);
    this->addChild(BG_BTN,10);
    
    Home_BTN->addClickEventListener([=](Ref* _sender) {
        Home_BTN->setTouchEnabled(false);
        DressUpScene::BTN_Part(Home_BTN,2);
        DressUpScene::Click_Effect(Home_BTN);
        DressUpScene::Home_Method();
    });
    Done_BTN->addClickEventListener([=](Ref* _sender) {
        Done_BTN->setTouchEnabled(false);
        DressUpScene::BTN_Part(Done_BTN,2);
        DressUpScene::Click_Effect(Done_BTN);
        DressUpScene::Done_Method();
    });
//    Camera_BTN->addClickEventListener([=](Ref* _sender) {
//        DressUpScene::BTN_Part(Camera_BTN,2);
//        DressUpScene::Click_Effect(Camera_BTN);
//        DressUpScene::Camera_Method();
//    });
    BG_BTN->addClickEventListener([=](Ref* _sender) {
        DressUpScene::BTN_Part(BG_BTN,2);
        DressUpScene::Click_Effect(BG_BTN);
        
        DressUpScene::Tap_Sound();
        
        BG_CHANGE++;
        
        if (BG_CHANGE==5)
        {
            BG_CHANGE=1;
            BG->setTexture(StringUtils::format("dressup_bg_%d.png",BG_CHANGE));
        }
        else
        {
            BG->setTexture(StringUtils::format("dressup_bg_%d.png",BG_CHANGE));
        }
    });
    
    #pragma mark - ======== Scroll
    
    for (int i=0; i<9; i++)
    {
        Thumb_Panel.push_back(Sprite::create("Thumb_Panel.png"));
        Thumb_Panel[i]->setAnchorPoint(Vec2(1,0.5));
        Thumb_Panel[i]->setPosition(Vec2(500000,500000));
        this->addChild(Thumb_Panel[i],5);
        
        SCView.push_back(ScrollView::create());
        SCView[i]->setAnchorPoint(Vec2(1,0.5));
        SCView[i]->setContentSize(Size(130,580));
        SCView[i]->setPosition(Vec2(Thumb_Panel[i]->getContentSize().width,Thumb_Panel[i]->getContentSize().height/2));
        SCView[i]->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        SCView[i]->setBounceEnabled(false);
        SCView[i]->setTouchEnabled(true);
        SCView[i]->setScrollBarEnabled(false);
        SCView[i]->setInnerContainerSize(Size(130,15*160));
        SCView[i]->setInnerContainerPosition(Vec2(0,0));
        Thumb_Panel[i]->addChild(SCView[i]);
        
    }
    
    for (int i=0,Y=(15*160)-80; i<15; i++)
    {
        Img_STR_1.push_back(StringUtils::format("Char_Item_1_T%d.png",i+1));
        Img_STR_2.push_back(StringUtils::format("Char_Item_2_T%d.png",i+1));
        Img_STR_3.push_back(StringUtils::format("Char_Item_3_T%d.png",i+1));
        Img_STR_4.push_back(StringUtils::format("Char_Item_4_T%d.png",i+1));
        Img_STR_5.push_back(StringUtils::format("Char_Item_5_T%d.png",i+1));
        Img_STR_6.push_back(StringUtils::format("Char_Item_6_T%d.png",i+1));
        Img_STR_7.push_back(StringUtils::format("Char_Item_7_T%d.png",i+1));
        Img_STR_8.push_back(StringUtils::format("Char_Item_8_T%d.png",i+1));
        Img_STR_9.push_back(StringUtils::format("Char_Item_9_T%d.png",i+1));
        
        SC_Thumb_1.push_back(ui::Button::create(Img_STR_1[i],Img_STR_1[i]));
        SC_Thumb_1[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_1[i]->setTouchEnabled(true);
        SC_Thumb_1[i]->setPosition(Vec2(SCView[0]->getContentSize().width/2,Y));
        SCView[0]->addChild(SC_Thumb_1[i]);
        
        SC_Thumb_2.push_back(ui::Button::create(Img_STR_2[i],Img_STR_2[i]));
        SC_Thumb_2[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_2[i]->setTouchEnabled(true);
        SC_Thumb_2[i]->setPosition(Vec2(SCView[1]->getContentSize().width/2,Y));
        SCView[1]->addChild(SC_Thumb_2[i]);
        
        SC_Thumb_3.push_back(ui::Button::create(Img_STR_3[i],Img_STR_3[i]));
        SC_Thumb_3[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_3[i]->setTouchEnabled(true);
        SC_Thumb_3[i]->setPosition(Vec2(SCView[2]->getContentSize().width/2,Y));
        SCView[2]->addChild(SC_Thumb_3[i]);
        
        SC_Thumb_4.push_back(ui::Button::create(Img_STR_4[i],Img_STR_4[i]));
        SC_Thumb_4[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_4[i]->setTouchEnabled(true);
        SC_Thumb_4[i]->setPosition(Vec2(SCView[3]->getContentSize().width/2,Y));
        SCView[3]->addChild(SC_Thumb_4[i]);
        
        SC_Thumb_5.push_back(ui::Button::create(Img_STR_5[i],Img_STR_5[i]));
        SC_Thumb_5[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_5[i]->setTouchEnabled(true);
        SC_Thumb_5[i]->setPosition(Vec2(SCView[4]->getContentSize().width/2,Y));
        SCView[4]->addChild(SC_Thumb_5[i]);
        
        SC_Thumb_6.push_back(ui::Button::create(Img_STR_6[i],Img_STR_6[i]));
        SC_Thumb_6[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_6[i]->setTouchEnabled(true);
        SC_Thumb_6[i]->setPosition(Vec2(SCView[5]->getContentSize().width/2,Y));
        SCView[5]->addChild(SC_Thumb_6[i]);
        
        SC_Thumb_7.push_back(ui::Button::create(Img_STR_7[i],Img_STR_7[i]));
        SC_Thumb_7[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_7[i]->setTouchEnabled(true);
        SC_Thumb_7[i]->setPosition(Vec2(SCView[6]->getContentSize().width/2,Y));
        SCView[6]->addChild(SC_Thumb_7[i]);
        
        SC_Thumb_8.push_back(ui::Button::create(Img_STR_8[i],Img_STR_8[i]));
        SC_Thumb_8[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_8[i]->setTouchEnabled(true);
        SC_Thumb_8[i]->setPosition(Vec2(SCView[7]->getContentSize().width/2,Y));
        SCView[7]->addChild(SC_Thumb_8[i]);
        
        SC_Thumb_9.push_back(ui::Button::create(Img_STR_9[i],Img_STR_9[i]));
        SC_Thumb_9[i]->setAnchorPoint(Vec2(0.5,0.5));
        SC_Thumb_9[i]->setTouchEnabled(true);
        SC_Thumb_9[i]->setPosition(Vec2(SCView[8]->getContentSize().width/2,Y));
        SCView[8]->addChild(SC_Thumb_9[i]);
        
        
        
        
        
        
        
        
        SC_Thumb_1[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_1[i]);
            Char_Item[0]->setTexture(StringUtils::format("Char_Item_1_%d.png",i+1));
            Char_Item[0]->setVisible(true);
            
            DressUpScene::Change_Part(246,82);
            
            SLIDER_TEMP=1;
            Flag_Val[0]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_2[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_2[i]);
            Char_Item[1]->setTexture(StringUtils::format("Char_Item_2_%d.png",i+1));
            Char_Item[1]->setVisible(true);
            DressUpScene::Change_Part(81,702);
            
            SLIDER_TEMP=2;
            Flag_Val[1]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_3[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_3[i]);
            Char_Item[2]->setTexture(StringUtils::format("Char_Item_3_%d.png",i+1));
            Char_Item[2]->setVisible(true);
            DressUpScene::Change_Part(226,550);
            
            SLIDER_TEMP=3;
            Flag_Val[2]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_4[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_4[i]);
            Char_Item[3]->setTexture(StringUtils::format("Char_Item_4_%d.png",i+1));
            Char_Item[3]->setVisible(true);
            DressUpScene::Change_Part(230,713);
            
            SLIDER_TEMP=4;
            Flag_Val[3]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_5[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_5[i]);
            Char_Item[4]->setTexture(StringUtils::format("Char_Item_5_%d.png",i+1));
            Char_Item[4]->setVisible(true);
            DressUpScene::Change_Part(230,713);
            
            SLIDER_TEMP=5;
            Flag_Val[4]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_6[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_6[i]);
            Char_Item[5]->setTexture(StringUtils::format("Char_Item_6_%d.png",i+1));
            Char_Item[5]->setVisible(true);
            DressUpScene::Change_Part(225,885);
            
            SLIDER_TEMP=6;
            Flag_Val[5]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_7[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_7[i]);
            Char_Item[6]->setTexture(StringUtils::format("Char_Item_7_%d.png",i+1));
            Char_Item[6]->setVisible(true);
            DressUpScene::Change_Part(224,791);
            
            SLIDER_TEMP=7;
            Flag_Val[6]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_8[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_8[i]);
            Char_Item[7]->setTexture(StringUtils::format("Char_Item_8_%d.png",i+1));
            Char_Item[7]->setVisible(true);
            DressUpScene::Change_Part(225,885);
            
            SLIDER_TEMP=8;
            Flag_Val[7]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        SC_Thumb_9[i]->addClickEventListener([=](Ref* _sender) {
            DressUpScene::Click_Effect(SC_Thumb_9[i]);
            Char_Item[8]->setTexture(StringUtils::format("Char_Item_9_%d.png",i+1));
            Char_Item[8]->setVisible(true);
            DressUpScene::Change_Part(337,633);
            
            SLIDER_TEMP=9;
            Flag_Val[8]=0;
            slider->setValue(0.2);
            slider->setPosition(Vec2(200,500));
        });
        
        
        Y=Y-160;
    }
    
    //==========================================================================//
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(DressUpScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(DressUpScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(DressUpScene::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //==========================================================================//
    
    this->scheduleOnce(SEL_SCHEDULE(&DressUpScene::Close_Eyes), 3.0);
    
    return true;
}


#pragma mark - ======== Method

void DressUpScene::valueChanged(Ref *sender, cocos2d::extension::Control::EventType controlEvent)
{
    cocos2d::extension::ControlSlider* pSlider = (cocos2d::extension::ControlSlider*)sender;
    CCLOG("Slide Method Value St =====  %f",pSlider->getValue());
    
    Char_Item[SLIDER_TEMP-1]->setHue(pSlider->getValue());
    Flag_Val[SLIDER_TEMP-1]=pSlider->getValue();
}

void DressUpScene::Open_Eyes()
{
    Char_CEye->setVisible(false);
    Char_Eyeshadow->setVisible(false);
    
    this->scheduleOnce(SEL_SCHEDULE(&DressUpScene::Close_Eyes), 3.0);
}

void DressUpScene::Close_Eyes()
{
    Char_CEye->setVisible(true);
    Char_Eyeshadow->setVisible(true);
    
    this->scheduleOnce(SEL_SCHEDULE(&DressUpScene::Open_Eyes), 0.1);
}

void DressUpScene::Scroll_In(int N)
{
    Thumb_Panel[N]->setPosition(Vec2(768,500));
    SCView[N]->setTouchEnabled(true);
    SCView[N]->scrollToTop(5.0, true);
}

void DressUpScene::Scroll_Out()
{
    for (int i=0; i<9; i++)
    {
        Thumb_Panel[i]->setPosition(Vec2(500000,500000));
        SCView[i]->setInnerContainerPosition(Vec2(0,0));
        SCView[i]->setTouchEnabled(false);
        
        Flag_Val[i]=0;
        
        
    }
    
    slider->setPosition(Vec2(500000,500000));
}

void DressUpScene::Home_Method()
{
    DressUpScene::Tap_Sound();
    
    AdCall_Jni::showFullScreenAd();
    
    auto scene1 = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene1));
}

void DressUpScene::Done_Method()
{
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    
    DressUpScene::Tap_Sound();
    
 //   sk::game_services::Admob_FullScreen();
    
    Done_BTN->setTag(2);
    Done_BTN->runAction(FadeOut::create(1.0));
    
    DressUpScene::Scroll_Out();
    
    //Camera_BTN->runAction(MoveBy::create(1.0, Vec2(-200,0)));
    BG_BTN->runAction(MoveBy::create(1.0, Vec2(-200,0)));
    
    for (int i=0; i<9; i++)
    {
        Tool_Item[i]->runAction(MoveBy::create(1.0, Vec2(-300,0)));
    }
    
    this->scheduleOnce(schedule_selector(DressUpScene::Done_Release),1.0);
}

void DressUpScene::Done_Release(float dt)
{
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
    
   // Camera_BTN->setTouchEnabled(true);
    BG_BTN->setTouchEnabled(true);
}

void DressUpScene::Camera_Method()
{
    if (MUSIC==1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Camera.mp3");
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    Camera_BTN->setVisible(false);
   // BG_BTN->setVisible(false);
    Home_BTN->setVisible(false);
    
    utils::captureScreen(CC_CALLBACK_2(DressUpScene::afterCapture, this), "ScreenShot.png");
    
#endif
    
    
}

void DressUpScene::afterCapture(bool succed, const std::string &outputFile)
{
    if (succed)
    {
    //    sk::game_services::Load_ScreenShot();
        
       // Camera_BTN->setVisible(true);
        BG_BTN->setVisible(true);
        Home_BTN->setVisible(true);
    }
    else
    {
        log("Succed Failed");
    }
}

#pragma mark - ======== SOUND SFX

void DressUpScene::Tap_Sound()
{
    if (MUSIC==1)
    {
        SimpleAudioEngine::getInstance()->playEffect("Tap_1.mp3");
    }
}

void DressUpScene::Vocal_Sound()
{
    int V_RAND = RAND_INT_VAL(1,20);
    
    if (V_RAND<=9)
    {
        std::string VSFX = StringUtils::format("Vocal_S_%d.mp3",V_RAND);
        
        if (MUSIC==1)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(VSFX.c_str());
        }
    }
    else
    {
        if (MUSIC==1)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sparkle_S_1.mp3");
        }
    }
}

void DressUpScene::Jelly_Effect(Sprite *Img)
{
    Img->stopAllActions();
    Img->runAction(Sequence::create(ScaleTo::create(0.1, 0.7, 1.0),
                                    ScaleTo::create(0.1, 1.0, 0.7),
                                    ScaleTo::create(0.1, 0.7, 1.0),
                                    ScaleTo::create(0.1, 1.0, 0.7),
                                    ScaleTo::create(0.1, 1.0, 1.0)
                                    ,NULL));
}

void DressUpScene::Click_Effect(Node *Nd)
{
    //Nd->runAction(Sequence::create(ScaleTo::create(0.2, 0.75,0.75),
                                    // ScaleTo::create(0.2, 1.0,1.0),NULL));
}

void DressUpScene::BTN_Part(Node *Nd,int N)
{
    if(N==1)
    {
        Button_Part=ParticleSystemQuad::create("Button_Part.plist");
    }
    else if(N==2)
    {
        Button_Part=ParticleSystemQuad::create("Small_Spark.plist");
    }
    
    Button_Part->setPosition(Nd->getPosition());
    this->addChild(Button_Part,100);
}

void DressUpScene::Change_Part(float F1,float F2)
{
    DressUpScene::Vocal_Sound();
    
    Clean_Part=ParticleSystemQuad::create("Button_Part.plist");
    Clean_Part->setPosition(Vec2(F1,F2));
    Char_body->addChild(Clean_Part,100);
}

#pragma mark - ======== Touch Begin


bool DressUpScene::onTouchBegan(Touch* touch, Event* event)
{
    locationPoint = touch->getLocationInView();
    locationPoint = Director::getInstance()->convertToGL(locationPoint);
    locationPoint = convertToNodeSpace(locationPoint);
    
    for (int i=0; i<9; i++)
    {
        if(Tool_Item[i]->getBoundingBox().containsPoint(locationPoint))
        {
            if (MUSIC==1)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sparkle_S_4.mp3");
            }
            
            DressUpScene::Jelly_Effect(Tool_Item[i]);
            DressUpScene::BTN_Part(Tool_Item[i],2);
            
            DressUpScene::Scroll_Out();
            DressUpScene::Scroll_In(i);
        }
    }
    
    return true;
}
#pragma mark - ======== Touch Move

void DressUpScene::onTouchMoved(Touch* touch, Event* event)
{
    locationPoint = touch->getLocationInView();
    locationPoint = Director::getInstance()->convertToGL(locationPoint);
    locationPoint = convertToNodeSpace(locationPoint);
    
//    BG->setPosition(locationPoint);
}

#pragma mark - ======== Touch Ended

void DressUpScene::onTouchEnded(Touch* touch, Event* event)
{
    locationPoint = touch->getLocationInView();
    locationPoint = Director::getInstance()->convertToGL(locationPoint);
    locationPoint = convertToNodeSpace(locationPoint);
    
    CCLOG("X==>%f,Y==%f",locationPoint.x,locationPoint.y);
    
    
}


