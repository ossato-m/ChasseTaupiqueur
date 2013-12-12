//
//  Hole.cpp
//  ChasseTaupiqueur
//
//  Created by kmu on 13. 12. 5..
//
//

#include "Hole.h"

cocos2d::CCPoint holePositions[9] = {
    ccp(267, 140), ccp(494, 140), ccp(721, 140), ccp(267, 320), ccp(494, 320), ccp(721, 320), ccp(267, 480), ccp(494, 480), ccp(721, 480)
};

Hole::Hole(int holeNo) {
    _location = holePositions[holeNo];
    _sprite = cocos2d::CCSprite::create("hole.png");
    _sprite->retain();
    _sprite->setPosition(_location);
    _type = NONE;
    _available = true;
    _moleStayTimer = 0;
}

Hole::~Hole() {
}

bool Hole::checkTime(float moleStayInterval, float dt) {
    if (_moleStayTimer > moleStayInterval) {
        return true;
    }
    _moleStayTimer += dt;
    return false;
}

void Hole::addMole(std::string const& sprite, PokemonType type) {
    _sprite->release();    
    _sprite = cocos2d::CCSprite::create(sprite.c_str());
    _sprite->retain();
    _sprite->setPosition(_location);
    _available = false;
    _type = type;
    _moleStayTimer = 0;
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
    _type = NONE;
    _moleStayTimer = 0;
}

bool Hole::isAvailable() const {
    return (_available);
}

PokemonType Hole::getMoleType() const {
    return (_type);
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