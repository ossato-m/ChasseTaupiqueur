//
//  Hole.cpp
//  ChasseTaupiqueur
//
//  Created by kmu on 13. 12. 5..
//
//

#include "Hole.h"

cocos2d::CCPoint holePositions[9] = {
    ccp(267, 180), ccp(494, 180), ccp(721, 180), ccp(267, 280), ccp(494, 280), ccp(721, 280), ccp(267, 380), ccp(494, 380), ccp(721, 380)
};

Hole::Hole(int holeNo) {
    _location = holePositions[holeNo];
    _sprite = cocos2d::CCSprite::create("hole.png");
    _sprite->retain();
    _sprite->setPosition(_location);
    
    std::cout << "new sprite" << std::endl;
    
    _available = true;
}

Hole::~Hole() {
}

void Hole::addMole(std::string const& sprite) {
    _sprite->release();    
    _sprite = cocos2d::CCSprite::create(sprite.c_str());
    _sprite->retain();
    _sprite->setPosition(_location);
    _available = false;
}

cocos2d::CCSprite* Hole::getSprite() const {
    return _sprite;
}

void Hole::removeMole() {
    _sprite->release();
    _sprite = cocos2d::CCSprite::create("hole.png");
    _sprite->retain();
    _sprite->setPosition(_location);
    _available = true;
}

bool Hole::isAvailable() const {
    return (_available);
}

bool Hole::isTouched(cocos2d::CCTouch* t) const {
    cocos2d::CCPoint p = _sprite->getPosition();
    cocos2d::CCSize s = _sprite->getContentSize();
    cocos2d::CCPoint tl = t->getLocation();
    
    if (tl.x >= (p.x - s.width / 2) && tl.x <= (p.x + s.width / 2) &&
        tl.y >= (p.y - s.height / 2) && tl.y <= (p.y + s.height / 2)) {
        return true;
    }
    return false;
}