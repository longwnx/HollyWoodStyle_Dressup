//
//  Headers.h
//  NewGame
//
//  Created by IMobiGames on 8/21/15.
//
//

#ifndef NewGame_Headers_h
#define NewGame_Headers_h

#define IS_IPHONE Application::getInstance()->getTargetPlatform()

#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "DressUpScene.h"

#include "CCSpriteWithHue.h"
#include "extensions/cocos-ext.h"

#include "AdCall_Jni.h"

#define RAND_UINT_MAX        0xFFFFFFFF
#define RAND_INT_MAX        0x7FFFFFFF
#define RAND_INT_VAL(a,b)        ((arc4random() % ((b)-(a)+1)) + (a))
#define RAND_FLOAT_VAL(a,b)        (((((float)arc4random()) * ((b)-(a))) / RAND_UINT_MAX) + (a))

#endif
