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
    
    CCSize winSize = this->getContentSize();
    
    _background = CCSprite::create("background.png");
    _background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    _background->retain();
    this->addChild(_background, 0);
    
    _gameOverText = CCLabelTTF::create("Game Over !", "Pokemon Hollow Normal", 80);
    _gameOverText->setPosition(ccp(winSize.width / 2, winSize.height * 3 / 4));
    _gameOverText->retain();
    this->addChild(_gameOverText);
    
    _quitGame = CCMenuItemFont::create("Quit", this, menu_selector(GameOverScene::quitCallback));
    _quitGame->setPosition(ccp(0, - _gameOverText->getContentSize().height / 2));
    _quitGame->retain();
    
    _restartGame = CCMenuItemFont::create("Retry", this, menu_selector(GameOverScene::restartCallback));
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