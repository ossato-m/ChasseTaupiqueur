//
//  GameOverScene.cpp
//  ChasseTaupiqueur
//
//  Created by 계명대학교
//  on 13. 12. 3..
//
//

#include "GameOverScene.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameOverScene::scene()
{
    CCScene* scene = SceneManager::getOrCreateScene();
    
    scene->addChild(GameOverScene::create());
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Game Over.mp3", true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);

    CCSize winSize = this->getContentSize();
    
    _background = CCSprite::create("background.png");
    _background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    _background->retain();
    this->addChild(_background, 0);
    
    _gameOver = CCSprite::create("GameOver.png");
    _gameOver->setPosition(ccp(winSize.width / 2, winSize.height * 3 / 4));
    _gameOver->setScale(1.5);
    _gameOver->retain();
    this->addChild(_gameOver);
    
    _scoreLabel = CCLabelTTF::create("0", "Arial", 20);
    _scoreLabel->setPosition(ccp(220, winSize.height - 52));
    _scoreLabel->retain();
    this->addChild(_scoreLabel);
    
    _quitGame = CCMenuItemImage::itemWithNormalImage("quit.png", "quit.png", this, menu_selector(MenuScene::quitCallback));
    _quitGame->setPosition(ccp(0, - _gameOver->getContentSize().height / 2 - 100));
    _quitGame->retain();
    
    CCMenuItem *_restartGame = CCMenuItemImage::itemWithNormalImage("play.png", "play.png", this, menu_selector(MenuScene::startCallback));
    _restartGame->setPosition(ccp(0, - _gameOver->getContentSize().height / 2));
    _restartGame->retain();
    
    CCMenu* pMenu = CCMenu::create(_restartGame, _quitGame, NULL);
    pMenu->retain();
    
    this->addChild(pMenu);
    return true;
}

void GameOverScene::restartCallback(cocos2d::CCObject* pSender) {
    CCScene* scene = SceneManager::getOrCreateScene();
    scene->removeChild(this, true);
    scene->addChild(MenuScene::create());
}

void GameOverScene::quitCallback(cocos2d::CCObject *pSender) {
    CCDirector:: sharedDirector()-> end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}