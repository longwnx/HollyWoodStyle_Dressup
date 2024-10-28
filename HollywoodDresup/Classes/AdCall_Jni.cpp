#include "AdCall_Jni.h"
#include "Headers.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#endif
USING_NS_CC;

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_purchasesuceed(JNIEnv* env, jobject thiz, jstring myStringParam);
};


extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_purchasefailed(JNIEnv* env, jobject thiz, jstring myStringParam);
};



void AdCall_Jni::Purchase(char* id) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo_ methodInfo;

    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "BuyNormal", "(Ljava/lang/String;)V")) {

        jstring  aid = methodInfo.env->NewStringUTF(id);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,aid);
        methodInfo.env->DeleteLocalRef(aid);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

    }

#endif

}

void AdCall_Jni::Subscribe(char* id) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    cocos2d::JniMethodInfo_ methodInfo;

    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "BuySubscribe", "()V")) {
        jstring  aid = methodInfo.env->NewStringUTF(id);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,aid);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

    }

#endif
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_purchasesuceed(JNIEnv* env, jobject thiz, jstring myStringParam)
{

    const char* str = env->GetStringUTFChars(myStringParam, NULL);

    CCLOG("C++ method called with args :%s", str);

//    LOCK_LVL=30;
//
//    IS_LOCK=false;
//    cocos2d::UserDefault::getInstance()->setBoolForKey("LOCK_KEY",IS_LOCK);
//    cocos2d::UserDefault::getInstance()->flush();
//
//    cocos2d::UserDefault::getInstance()->setBoolForKey("Unlock",true);
//    cocos2d::UserDefault::getInstance()->flush();

//    LOCK_STORE=16;
//    cocos2d::UserDefault::getInstance()->setIntegerForKey("LOCK_STORE_KEY",LOCK_STORE);
//    cocos2d::UserDefault::getInstance()->flush();
//
//    IS_LOCK=false;
//    cocos2d::UserDefault::getInstance()->setBoolForKey("LOCK_KEY",IS_LOCK);
//    cocos2d::UserDefault::getInstance()->flush();

    env->ReleaseStringUTFChars(myStringParam, str);



}


JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_purchasefailed(JNIEnv* env, jobject thiz, jstring myStringParam){


    const char* str = env->GetStringUTFChars(myStringParam, NULL);

    CCLOG("C++ method called with args :%s", str);

//    LOCK_STORE=16;
//    cocos2d::UserDefault::getInstance()->setIntegerForKey("LOCK_STORE_KEY",LOCK_STORE);
//    cocos2d::UserDefault::getInstance()->flush();
//
//    IS_LOCK=false;
//    cocos2d::UserDefault::getInstance()->setBoolForKey("LOCK_KEY",IS_LOCK);
//    cocos2d::UserDefault::getInstance()->flush();

    env->ReleaseStringUTFChars(myStringParam, str);
}

void AdCall_Jni:: restorePurchase()
{

    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,"org/cocos2dx/cpp/AppActivity","restorePurchase","()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }


}

void AdCall_Jni::Vibration()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //if(cocos2d::UserDefault::getInstance()->getBoolForKey(REMOVE_ADS))
    //return ;
    
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "VibrationLoad", "()V")) {
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
#endif
}

void AdCall_Jni::ShowBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //if(cocos2d::UserDefault::getInstance()->getBoolForKey(REMOVE_ADS))
    //return ;
    
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "bannerEnabled", "()V")) {
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
#endif
}

void AdCall_Jni::HideBanner()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //if(cocos2d::UserDefault::getInstance()->getBoolForKey(REMOVE_ADS))
    //return ;
   
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "HideBanner", "()V")) {
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
#endif
}

void AdCall_Jni::RemoveAllAds() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    cocos2d::JniMethodInfo_ methodInfo;

    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "hideBannerAd", "()V")) {

        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

    }

#endif
}

bool AdCall_Jni::isFull_PageAdAvailable() {

	/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    //if(cocos2d::UserDefault::getInstance()->getBoolForKey(KEY_INAPP_REMOVEADS))
    //return false;
	CCLOG( " Befor ..... AdCall-jni Method Called on .....");
	
			cocos2d::JniMethodInfo_ methodInfo;
	
			if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "isInterstitialAvailable", "()Z")){
		
				CCLOG("AdCall-jni Method Called on .....");

				bool returnValue = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);

				if (returnValue)
					CCLOG(" Full Page is Loaded ");


				methodInfo.env->DeleteLocalRef(methodInfo.classID);

			}
			else {

				CCLOG("Static Method Not Available in Java Class.. Plz Define ");

			}
			
	#endif*/

	return false;
}

void AdCall_Jni::showFullScreenAd() {
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //if(cocos2d::UserDefault::getInstance()->getBoolForKey(KEY_INAPP_REMOVEADS))
    //return ;
    
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "showInterstitial", "()V")){
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
    
    
#endif
    
    
}


void AdCall_Jni::showSmallBanner() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //if(cocos2d::UserDefault::getInstance()->getBoolForKey(KEY_INAPP_REMOVEADS))
    //return ;
    
	cocos2d::JniMethodInfo_ methodInfo;

	if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "bannerEnabled", "()V")) {

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);

	}

#endif

}

void AdCall_Jni::SaveImageToJNI(bool visible){
    
#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
   cocos2d::JniMethodInfo methodInfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity","getInstance","()Lorg/cocos2dx/cpp/AppActivity;");
    
    jobject activityObj;
    if (isHave) {
        
        activityObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
    }
    
    isHave = cocos2d::JniHelper::getMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity","SaveToGallery","(Ljava/lang/String;)V");
    
    
    if (!isHave)
    {
        CCLOG("Call SaveToGallry Method ia not in App Activity;");
    }
    else
    {
        CCLOG("Call SaveToGallry Method is  in App Activity;");
        jstring StringArg1 = methodInfo.env->NewStringUTF("Share.png");
        methodInfo.env->CallVoidMethod(activityObj, methodInfo.methodID,StringArg1);
        //        methodInfo.env->DeleteGlobalRef(activityObj);
    }
#endif
}

void AdCall_Jni::ShareImageToJNI(bool visible){
    
#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
    cocos2d::JniMethodInfo methodInfo;
    CCLOG("Nitin hello i am adcall");
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity","getInstance","()Lorg/cocos2dx/cpp/AppActivity;");
    
    jobject activityObj;
    if (isHave) {
        
        activityObj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
    }
    
    isHave = cocos2d::JniHelper::getMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity","ShareDialog","(Ljava/lang/String;)V");
    
    
    if (!isHave)
    {
        CCLOG("Call ShareDialog Method ia not in App Activity;");
    }
    else
    {
        CCLOG("Call ShareDialog Method is  in App Activity;");
        jstring StringArg1 = methodInfo.env->NewStringUTF("Image_Save.png");
        methodInfo.env->CallVoidMethod(activityObj, methodInfo.methodID,StringArg1);
        //        methodInfo.env->DeleteGlobalRef(activityObj);
    }
#endif
}

void AdCall_Jni::ShareGameLink()
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        cocos2d::JniMethodInfo_ methodInfo;
        
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "ShareGameLink", "()V")) {
            
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    #endif
    
}



void AdCall_Jni::MoreGame() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "OpenMoreGame", "()V")) {
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
#endif
}



void AdCall_Jni::RateGame() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    cocos2d::JniMethodInfo_ methodInfo;
    
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "openRateGame", "()V")) {
        
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    
#endif
}


void AdCall_Jni::BackButtonClicked() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	cocos2d::JniMethodInfo_ methodInfo;

	if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "BackButtonClicked", "()V")) {

		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);

	}

#endif
}
