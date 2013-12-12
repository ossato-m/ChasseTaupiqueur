//
//  GameScene.cpp
//  ChasseTaupiqueur
//
//  Created by kmu on 13. 12. 5..
//
//

#include <vector>
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
    
    _difficultyInterval = 10.0f;
    _difficultyTimer = _difficultyInterval * 0.99f;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    _background = CCSprite::create("background.png");
    _background->setPosition(ccp(size.width / 2, size.height / 2));
    _background->retain();
    this->addChild(_background, 0);
    
    for (int i = 0; i < 9; i++) {
        Hole* newHole = new Hole(i);
        
        _holes.push_back(newHole);
        this->addChild(newHole->getSprite(), 0);
    }
    
    _ui = CCSprite::create("score_life_time_ui.png");
    _ui->setPosition(ccp(size.width / 2, size.height - 50));
    _ui->retain();
    this->addChild(_ui, 0);
    
    _life1 = CCSprite::create("life.png");
    _life1->setPosition(ccp(size.width - 162.5, size.height - 45));
    _life1->retain();
    this->addChild(_life1, 0);
    
    _life2 = CCSprite::create("life.png");
    _life2->setPosition(ccp(size.width - 100, size.height - 45));
    _life2->retain();
    this->addChild(_life2, 0);
    
    _life3 = CCSprite::create("life.png");
    _life3->setPosition(ccp(size.width - 37.5, size.height - 45));
    _life3->retain();
    this->addChild(_life3, 0);
    
    _score = 0;
    _scoreLabel = CCLabelTTF::create("0", "Arial", 20);
    _scoreLabel->setPosition(ccp(220, size.height - 52));
    _scoreLabel->retain();
    this->addChild(_scoreLabel);
    
    //listen for touches
    this->setTouchEnabled(true);
    
    //create main loop
    this->schedule(schedule_selector(GameScene::update));
    
    return true;
}

void GameScene::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
    for (CCSetIterator i = pTouches->begin(); i != pTouches->end(); i++) {
        CCTouch* touch = (CCTouch*) (*i);
        
        if (touch) {
            std::vector<Hole*>::iterator it;
            for (it = _holes.begin(); it != _holes.end(); it++) {
                if (!(*it)->isAvailable() && (*it)->isTouched(touch)) {
                    this->removeChild((*it)->getSprite(), false);
                    (*it)->removeMole();
                    this->addChild((*it)->getSprite());
                    _score += 10;
                    //_scoreLabel->set
                }
            }
        }
    }
}

void GameScene::resetMole(void) {
    if (hasAvailableHole()) {
        Hole* hole = findAvailableHole();
        
        this->removeChild(hole->getSprite(), false);        
        hole->addMole("diglett.png");
        this->addChild(hole->getSprite());
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
    int randValue = rand() % 9;
    
    if (_holes[randValue]->isAvailable()) {
        return _holes[randValue];
    }
    return findAvailableHole();
}

void GameScene::increaseDifficulty() {
    _moleInterval = _moleInterval * 0.9f;
}

void GameScene::update(float dt) {
    _difficultyTimer += dt;
    if (_difficultyTimer > _difficultyInterval && _difficultyTimer != 0) {
        _difficultyTimer = 0;
        this->increaseDifficulty();
    }
    
    _moleTimer += dt;
    if (_moleTimer > _moleInterval && _moleTimer != 0) {
        _moleTimer = 0;
        this->resetMole();
    }
}

GameScene::~GameScene() {
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_life1);
    CC_SAFE_RELEASE(_life2);
    CC_SAFE_RELEASE(_life3);
    CC_SAFE_RELEASE(_ui);
    CC_SAFE_RELEASE(_scoreLabel);
}