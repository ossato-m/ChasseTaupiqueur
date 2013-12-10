//
//  GameScene.h
//  ChasseTaupiqueur
//
//  Created by kmu on 13. 12. 5..
//
//

#ifndef __ChasseTaupiqueur__GameScene__
#define __ChasseTaupiqueur__GameScene__

#include <iostream>
#include "Hole.h"
#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    ~GameScene();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);
    
    void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    void update(float dt);
    
    Hole* findAvailableHole();
    bool  hasAvailableHole();
    void  resetMole();
    void  increaseDifficulty();
    
    
private:
    int                  _score;
    cocos2d::CCLabelTTF* _scoreLabel;
    std::vector<Hole*>   _holes;
    float                _moleInterval;
	float                _moleTimer;
    float                _difficultyTimer;
    float                _difficultyInterval;
    cocos2d::CCSprite*   _background;
    cocos2d::CCSprite*   _life1;
    cocos2d::CCSprite*   _life2;
    cocos2d::CCSprite*   _life3;
    cocos2d::CCSprite*   _ui;
};

#endif /* defined(__ChasseTaupiqueur__GameScene__) */
