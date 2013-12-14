//
//  GameScene.cpp
//  ChasseTaupiqueur
//
//  Created by kmu on 13. 12. 5..
//
//

#include <vector>
#include "GameOverScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

extern CCScene* globalScene;
extern int _score;
extern float _time;

// on "init" you need to initialize your instance
bool GameScene::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    srand(getpid());
    _moleInterval = 2.5f;
	_moleTimer = _moleInterval * 0.99f;
    
    _difficultyInterval = 5.0f;
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
    _scoreLabel->setPosition(ccp(240, size.height - 52));
    _scoreLabel->retain();
    this->addChild(_scoreLabel);
    
    _time = 0;
    _timeLabel = CCLabelTTF::create("00:00", "Arial", 20);
    _timeLabel->setPosition(ccp(580, size.height - 52));
    _timeLabel->retain();
    this->addChild(_timeLabel);
    
    _moleStayInterval = 5.0f;
    
    _parasectTimer = 0.f;
    
    _parasectAction = CCRepeat::create(CCSequence::createWithTwoActions(CCMoveBy::create(0.1, ccp(5, 5)), CCMoveBy::create(0.1, ccp(-5, -5))), 10);
    _parasectAction->retain();
    
    //listen for touches
    this->setTouchEnabled(true);
    
    //create main loop
    this->schedule(schedule_selector(GameScene::update));
    
    return true;
}

void GameScene::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {
    if (_parasectTimer <= 0.f) {
    for (CCSetIterator i = pTouches->begin(); i != pTouches->end(); i++) {
        CCTouch* touch = (CCTouch*) (*i);
        
        if (touch) {
            std::vector<Hole*>::iterator it;
            for (it = _holes.begin(); it != _holes.end(); it++) {
                if (!(*it)->isAvailable() && (*it)->isTouched(touch)) {
                    
                    this->removeChild((*it)->getSprite(), false);
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Hit.mp3");
                    switch ((*it)->getMoleType()) {
                        case DUGTRIO:
                            _score += 30;
                            break;
                        case DIGLETT:
                            _score += 10;
                            break;
                        case CLEFAIRY:
                            removeLife();
                            break;
                        case PARASECT:
                            std::vector<Hole*>::iterator it;
                            for (it = _holes.begin(); it != _holes.end(); it++) {
                                (*it)->getSprite()->runAction((CCAction*) _parasectAction->copy());
                            }                            
                            _parasectTimer = 2.0;
                            break;
                    }
                    
                    (*it)->removeMole();
                    this->addChild((*it)->getSprite());
                    
                    char score_buffer[10];
                    sprintf(score_buffer,"%i", _score);
                    _scoreLabel->setString(score_buffer);
                }
            }
        }
    }
    }
}

void GameScene::resetMole(void) {
    if (hasAvailableHole()) {
        Hole* hole = findAvailableHole();
        
        this->removeChild(hole->getSprite(), false);
        
        int randVal = random() % 100;
        if (randVal >= 0 && randVal <= 10) {
            hole->addMole("clefairy.png", CLEFAIRY);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Clefairy.mp3");
        } else if (randVal >= 11 && randVal <= 20) {
            hole->addMole("dugtrio.png", DUGTRIO);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("triotriotrio.mp3");
        } else if (randVal >= 21 && randVal <= 30) {
            hole->addMole("parasect.png", PARASECT);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Parasect.mp3");
        } else {
            hole->addMole("diglett.png", DIGLETT);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Diglett.mp3");
        }
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
    _moleStayInterval = _moleStayInterval * 0.9f;
}

void GameScene::removeLife() {
    if (_life3->isVisible()) {
        _life3->setVisible(false);
    } else if (_life2->isVisible()) {
        _life2->setVisible(false);
    } else if (_life1->isVisible()) {
        _life1->setVisible(false);
        CCScene* scene = SceneManager::getOrCreateScene();
        scene->removeChild(this, true);
        scene->addChild(GameOverScene::create());
    }
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
    
    std::vector<Hole*>::iterator it;
    for (it = _holes.begin(); it != _holes.end(); it++) {
        if (!(*it)->isAvailable() && (*it)->checkTime(_moleStayInterval, dt)) {
            if ((*it)->getMoleType() == DIGLETT || (*it)->getMoleType() == DUGTRIO) {
                removeLife();
            }
            this->removeChild((*it)->getSprite(), false);
            (*it)->removeMole();
            this->addChild((*it)->getSprite());            
        }
    }
    
    if (_parasectTimer > 0.f) {
        _parasectTimer -= dt;
    }
    if (_parasectTimer < 0.f) {
        _parasectTimer = 0.f;
    }
    
    _time += dt;
    
    char time_buffer[10];
    int time_int = (int) _time;
    
    sprintf(time_buffer,"%.2d:%.2d", time_int / 60, time_int % 60);
    _timeLabel->setString(time_buffer);
}

GameScene::~GameScene() {
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_life1);
    CC_SAFE_RELEASE(_life2);
    CC_SAFE_RELEASE(_life3);
    CC_SAFE_RELEASE(_ui);
    CC_SAFE_RELEASE(_scoreLabel);
    CC_SAFE_RELEASE(_timeLabel);
    CC_SAFE_RELEASE(_parasectAction);
    
    for (int i = 0; i < _holes.size() - 1; i++) {
        CC_SAFE_RELEASE(_holes[i]->getSprite());
    }
    for (int i = 0; i < _holes.size(); i++) {
        delete _holes[i];
    }
}