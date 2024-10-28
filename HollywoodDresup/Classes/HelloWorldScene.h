#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    cocos2d::Point touchPoint;
    cocos2d::Size visibleSize;
    
    virtual bool init();
    
    //=========== Sprites ===========//
    
    cocos2d::Sprite *main_bg;
    
    cocos2d::Sprite *Char;
    cocos2d::Sprite *Char_Close;
    
    cocos2d::Sprite *Title_1;
    
    void Jelly_Effect(float ft);
    
    //=========== Buttons ===========//
    
    cocos2d::Sprite *play_btn;
    
    cocos2d::Sprite *More_btn;
    cocos2d::Sprite *Star_btn;
    cocos2d::Sprite *Sound_btn;
    
    void sound_method();
    
    //=========== Particals ===========//
    
    cocos2d::ParticleSystemQuad *Button_Part;
    void BTN_Part(Sprite *S);
    
    cocos2d::ParticleSystemQuad *Particals;
    cocos2d::ParticleSystemQuad *bg_particle;
    
    //=========== Methods ===========//
    
    void Close_Eyes();
    void Open_Eyes();
    
    void play_method();
    void load_btn(float dt);
    void Load_Title(float dt);
    
    //===========
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    //virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
private:
    cocos2d::Label* labelTouchInfo;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
