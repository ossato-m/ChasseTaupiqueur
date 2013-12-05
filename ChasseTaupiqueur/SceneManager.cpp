//
//  SceneManager.cpp
//  ChasseTaupiqueur
//
//  Created by 계명대학교
//  on 13. 12. 3..
//
//

#include "cocos2d.h"
#include "SceneManager.h"

using namespace cocos2d;

CCScene* SceneManager::getOrCreateScene()
{
    static CCScene* scene = NULL;
    
    if (!scene) {
        scene = CCScene::create();
    }
    return scene;
}