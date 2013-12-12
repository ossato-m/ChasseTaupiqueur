#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class MenuScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void startCallback(CCObject* pSender);
    void quitCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MenuScene);
    ~MenuScene();
    
    cocos2d::CCSprite* _gameTitle;
    CCMenuItemFont* _startGame;
    CCMenuItemFont* _endGame;
    cocos2d::CCSprite*   _background;
};

#endif // __HELLOWORLD_SCENE_H__
