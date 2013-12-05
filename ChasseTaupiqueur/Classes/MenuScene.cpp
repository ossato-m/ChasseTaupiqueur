#include "MenuScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

MenuScene::~MenuScene() {
    CC_SAFE_DELETE(_gameTitle);
    CC_SAFE_DELETE(_endGame);
    CC_SAFE_DELETE(_startGame);
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
    
    CCSize winSize = this->getContentSize();
    
    _gameTitle = CCLabelTTF::create("Chasse Taupiqueur !!!", "Arial", 80);
    _gameTitle->setPosition(ccp(winSize.width / 2, winSize.height * 3 / 4));
    _gameTitle->retain();
    this->addChild(_gameTitle);
    
    _endGame= CCMenuItemFont::create("Close", this, menu_selector(MenuScene::quitCallback));
    _endGame->setPosition(ccp(0, - _gameTitle->getContentSize().height / 2));
    _endGame->retain();
    
    CCMenuItem *_startGame = CCMenuItemFont::create("Test", this, menu_selector(MenuScene::startCallback));
    _startGame->retain();
    
    CCMenu* pMenu = CCMenu::create(_startGame, _endGame, NULL);
    pMenu->retain();
    this->addChild(pMenu);
    return true;
}

void MenuScene::startCallback(cocos2d::CCObject* pSender) {
    CCScene* scene = SceneManager::getOrCreateScene();
    scene->removeChild(this, true);
    scene->addChild(GameOverScene::create());
}

void MenuScene::quitCallback(cocos2d::CCObject *pSender) {
    CCDirector:: sharedDirector()-> end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}