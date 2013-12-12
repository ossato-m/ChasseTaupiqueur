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

enum PokemonType {
    NONE,
    CLEFAIRY,
    DIGLETT,
    DUGTRIO,
    PARASECT
};

class Hole {
public:
    Hole(int holeNo);
    ~Hole();
    bool isAvailable() const;
    void addMole(std::string const& mole, PokemonType type);
    void removeMole();
    bool isTouched(cocos2d::CCTouch* touch) const;
    cocos2d::CCSprite* getSprite() const;
    PokemonType getMoleType() const;
    bool checkTime(float timer, float dt);
    
private:
    cocos2d::CCSprite*  _sprite;
    PokemonType         _type;
    bool                _available;
    cocos2d::CCPoint    _location;
    float                _moleStayTimer;
};

#endif /* defined(__ChasseTaupiqueur__Hole__) */
