//
//  SceneManager.h
//  ChasseTaupiqueur
//
//  Created by 계명대학교
//  on 13. 12. 3..
//
//

#ifndef __ChasseTaupiqueur__SceneManager__
#define __ChasseTaupiqueur__SceneManager__

#include <iostream>
#include "cocos2d.h"

class SceneManager {
    public: static cocos2d::CCScene* getOrCreateScene();
};

#endif /* defined(__ChasseTaupiqueur__SceneManager__) */
