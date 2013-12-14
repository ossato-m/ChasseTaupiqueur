#include "MenuScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

MenuScene::~MenuScene() {
    CC_SAFE_DELETE(_gameTitle);
    CC_SAFE_DELETE(_endGame);
    CC_SAFE_DELETE(_startGame);
    CC_SAFE_DELETE(_background);
    CC_SAFE_DELETE(_pMenu);
}

CCScene* MenuScene::scene() {
    CCScene* scene = SceneManager::getOrCreateScene();
    
    scene->addChild(MenuScene::create());
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Background-music.wav", true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);

    CCSize winSize = this->getContentSize();
    
    _background = CCSprite::create("background.png");
    _background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    _background->retain();
    this->addChild(_background, 0);
    
    _gameTitle = CCSprite::create("title.png");
    _gameTitle->setPosition(ccp(winSize.width / 2, winSize.height * 3 / 4));
    _gameTitle->setScale(1.5);
    _gameTitle->retain();
    this->addChild(_gameTitle);
    
    _endGame = CCMenuItemImage::itemWithNormalImage("quit.png", "quit.png", this, menu_selector(MenuScene::quitCallback));
    _endGame->setPosition(ccp(0, - _gameTitle->getContentSize().height / 2 - 100));
    _endGame->retain();
    
    CCMenuItem *_startGame = CCMenuItemImage::itemWithNormalImage("play.png", "play.png", this, menu_selector(MenuScene::startCallback));
    _startGame->setPosition(ccp(0, - _gameTitle->getContentSize().height / 2));
    _startGame->retain();
    
    _pMenu = CCMenu::create(_startGame, _endGame, NULL);
    _pMenu->retain();
    this->addChild(_pMenu);
    return true;
}

void MenuScene::startCallback(cocos2d::CCObject* pSender) {
    CCScene* scene = SceneManager::getOrCreateScene();
    scene->removeChild(this, true);
    scene->addChild(GameScene::create());
}

void MenuScene::quitCallback(cocos2d::CCObject *pSender) {
    CCDirector:: sharedDirector()-> end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}