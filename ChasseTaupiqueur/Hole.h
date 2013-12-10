//
//  Hole.h
//  ChasseTaupiqueur
//
//  Created by kmu on 13. 12. 5..
//
//

#ifndef __ChasseTaupiqueur__Hole__
#define __ChasseTaupiqueur__Hole__

#include <iostream>
#include "cocos2d.h"

class Hole {
public:
    Hole(int holeNo);
    ~Hole();
    bool isAvailable() const;
    void addMole(std::string const& mole);
    void removeMole();
    bool isTouched(cocos2d::CCTouch* touch) const;
    cocos2d::CCSprite* getSprite() const;
    
private:
    cocos2d::CCSprite*  _sprite;
    bool                _available;
    cocos2d::CCPoint    _location;
};

#endif /* defined(__ChasseTaupiqueur__Hole__) */
