//
//  DressUpScene.h
//  Make My Barbie
//
//  Created by Mehul on 02/03/15.
//
//

#ifndef __Make_My_Barbie__DressUpScene__
#define __Make_My_Barbie__DressUpScene__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "CCSpriteWithHue.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace ui;

class DressUpScene : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    Point locationPoint;
    Size visibleSize;
    
    //////////////////////////////////////////////////
    
    Sprite *BG;
    Sprite *Char_body,*Char_WEye,*Char_Eye,*Char_EyeLash,*Char_Liner,*Char_Eyebrow,*Char_CEye,*Char_Eyeshadow;
    
    std::vector<std::string>Img_STR_1,Img_STR_2,Img_STR_3,Img_STR_4,Img_STR_5,Img_STR_6,Img_STR_7,Img_STR_8,Img_STR_9;
    std::vector<Sprite *>Thumb_Panel,Tool_Item;
    std::vector<SpriteWithHue *>Char_Item;
    
    std::vector<ScrollView *>SCView;
    std::vector<Button *>SC_Thumb_1,SC_Thumb_2,SC_Thumb_3,SC_Thumb_4,SC_Thumb_5,SC_Thumb_6,SC_Thumb_7,SC_Thumb_8,SC_Thumb_9;
    
    void Vocal_Sound();
    void Tap_Sound();
    void Jelly_Effect(Sprite *Img);
    void Click_Effect(Node *Nd);
    
    Button *Home_BTN,*BG_BTN,*Camera_BTN,*Done_BTN;
    
    int BG_CHANGE;
    
    void Done_Method();
    void Done_Release(float dt);
    
    void Close_Eyes();
    void Open_Eyes();
    
    void Scroll_In(int N);
    void Scroll_Out();
    
    void Home_Method();
    void Camera_Method();
    void CameraPartical();
    void afterCapture(bool succed, const std::string &outputFile);// Screenshot
    
    //////////////////////////////////////////////////
    
    cocos2d::ParticleSystemQuad *BG_Part,*Clean_Part,*Button_Part;
    
    void BTN_Part(Node *Nd,int N);
    void Change_Part(float F1,float F2);
    
    //=====================================================
    void valueChanged(cocos2d::Ref* sender, extension::Control::EventType controlEvent);
    cocos2d::extension::ControlSlider *slider;
    
    //=====================================================
    
    /////////////////////////////////////////////////
    
    void scheduledSelector(float dt);
    
    // implement the "static node()" method manually
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    
    CREATE_FUNC(DressUpScene);
    
private:
    cocos2d::Vect getAnimation(const char *format, int count);
    
};

#endif /* defined(__Make_My_Barbie__DressUpScene__) */
