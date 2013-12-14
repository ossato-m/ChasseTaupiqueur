//
//  GameOverScene.h
//  ChasseTaupiqueur
//
//  Created by 계명대학교
//  on 13. 12. 3..
//
//

#ifndef __ChasseTaupiqueur__GameOverScene__
#define __ChasseTaupiqueur__GameOverScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameOverScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void quitCallback(CCObject* pSender);
    void restartCallback(CCObject* pSender);
    
    ~GameOverScene();

    int _score;
    
    CCLabelTTF* _scoreLabel;
    CCSprite* _background;
    CCSprite*  _gameOver;
    CCMenuItemImage* _restartGame;
    CCMenuItemImage* _quitGame;
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameOverScene);
};

#endif /* defined(__ChasseTaupiqueur__GameOverScene__) */
