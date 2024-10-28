#ifndef _AdCall_Jni_H_
#define _AdCall_Jni_H_

#include "cocos2d.h"

class AdCall_Jni : public cocos2d::Ref
{
public :

	static bool isFull_PageAdAvailable();
	static void showSmallBanner();
    static void showFullScreenAd();
	static void BackButtonClicked();
    
    static void MoreGame();
    static void RateGame();
    
    static void Vibration();
    
    static void HideBanner();
    static void ShowBanner();
    
    //InApp Purchase
    void static restorePurchase();
    
    static void Purchase(char* id);
    static void Subscribe(char* id);
    
    static void RemoveAllAds();
    
    static void ShareGameLink();
    
    //Save and Share
    void static SaveImageToJNI(bool visible);
    void static ShareImageToJNI(bool visible);
    
    
};

#endif // _Tiles_H_
