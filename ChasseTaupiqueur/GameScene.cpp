//
//  GameScene.cpp
//  ChasseTaupiqueur
//
//  Created by kmu on 13. 12. 5..
//
//

#include "GameScene.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

extern CCScene* globalScene;

// on "init" you need to initialize your instance
bool GameScene::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    _moleInterval = 2.5f;
	_moleTimer = _moleInterval * 0.99f;
    
    for (int i = 0; i < 10; i++) {
        _holes.push_back(new Hole());
    }
    
    //listen for touches
    this->setTouchEnabled(true);
    
    //create main loop
    this->schedule(schedule_selector(GameScene::update));
    
    return true;
}

void GameScene::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
    CCObject* it = NULL;
    
    /*CCARRAY_FOREACH(_moles, it) {
        CCSprite* mole = dynamic_cast<CCSprite*>(it);
    }*/
}

void GameScene::resetMole(void) {
    if (hasAvailableHole()) {
        Hole* hole = findAvailableHole();
        hole->addMole(CCSprite::create("Icon-72.png"));
        printf("Added a mole\n");
    } else {
        printf("No available hole bouuuuh\n");
    }
}

bool GameScene::hasAvailableHole() {
    for (int i = 0; i < 9; i++) {
        if (_holes[i]->isAvailable()) {
            return true;
        }
    }
    return false;
}

Hole* GameScene::findAvailableHole() {
    int randValue = rand() % 10;
    
    if (_holes[randValue]->isAvailable()) {
        return _holes[randValue];
    }
    return findAvailableHole();
}

void GameScene::update(float dt) {
    /*_difficultyTimer += dt;
    if (_difficultyTimer > _difficultyInterval) {
        _difficultyTimer = 0;
        this->increaseDifficulty();
    }*/
    
    _moleTimer += dt;
    if (_moleTimer > _moleInterval && _moleTimer != 0) {
        _moleTimer = 0;
        this->resetMole();
    }
}

GameScene::~GameScene() {
}