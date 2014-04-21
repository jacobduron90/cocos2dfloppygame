//
//  CCloud.cpp
//  HelloCpp
//
//  Created by Jacob Duron on 4/18/14.
//
//

#include "CCloud.h"
#include "Constants.h"


USING_NS_CC;

CCloud* CCloud::createCloudWithFileName(const char *fileName){
    CCloud *sprite = new CCloud();
	if(sprite && sprite->initWithFile(fileName)) {
       		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
    
}
void CCloud::Start(){
    this->stopAllActions();
    float currentX = this->getPositionX();
    float distance = currentX - -(_xOffset);
    
    float time = distance / _pixelsPerSec;
    CCPoint destination = ccp(-_xOffset, this->getPositionY());
    
    CCMoveTo *actionMove = CCMoveTo::create(time, destination);
    CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(CCloud::ReachedDestination));
    
    this->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
    
}
void CCloud::Stop(){
    this->stopAllActions();
    
}
void CCloud::SetSpeedAndWidth(const float speed, const float width, const float xOffset){
    _speed = speed;
    _screenWidth = width;
    _pixelsPerSec = _screenWidth / _speed;
    _xOffset = xOffset;
    
}
void CCloud::ReachedDestination(){
    this->setPositionX(kCloudRestartX + _screenWidth);
    this->Start();
}

