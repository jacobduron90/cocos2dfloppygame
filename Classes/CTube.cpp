//
//  CTube.cpp
//  HelloCpp
//
//  Created by Jacob Duron on 4/19/14.
//
//

#include "CTube.h"
#include "Constants.h"


USING_NS_CC;

CTube* CTube::createTubeWithFileName(const char *fileName){
    CTube *sprite = new CTube();
	if(sprite && sprite->initWithFile(fileName)) {
        sprite->setVisible(false);
        return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
    
}
void CTube::Start(){
    this->stopAllActions();
    
    

    float distance = _xOffset + _screenWidth + _xOffset;
    float time = distance / _pixelsPerSec;
    
    CCPoint destination = ccp(-_xOffset, this->getPositionY());
    this->setPosition(ccp(_xOffset + _screenWidth, this->getPositionY()));
    
    CCMoveTo *actionMove = CCMoveTo::create(time, destination);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(CTube::ReachedDestination));
    _state = kTubeStateActive;
    this->setVisible(true);
    this->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
    
}
void CTube::Stop(){
    this->stopAllActions();
    this->setVisible(false);
    _state = kTubeStateInactive;
    this->setPosition(ccp(_InactiveX, this->getPositionY()));
    
}
void CTube::Initialize(const float speed, const float width, const float xOffSet, const float InactiveX){
    _speed = speed;
    _screenWidth = width;
    _pixelsPerSec = _screenWidth / _speed;
    _InactiveX = InactiveX;
    this->setPosition(ccp(_InactiveX, 0));
    _state = kTubeStateInactive;

}
void CTube::ReachedDestination(){
    Stop();
}

int CTube::GetState(){
    return _state;
}


