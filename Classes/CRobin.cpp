//
//  CRobin.cpp
//  HelloCpp
//
//  Created by Jacob Duron on 4/18/14.
//
//

#include "CRobin.h"
#include "Constants.h"


USING_NS_CC;

CRobin* CRobin::createRobinWithFileName(const char *fileName) {
	
	CRobin *sprite = new CRobin();
	if(sprite && sprite->initWithFile(fileName)) {
        sprite->Reset();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void CRobin::UpdateRobin(float dt) {
	if(_state == kRobinStateMoving){
        float distance = 0;
        float newSpeed = 0;
        
        distance = _speedY * dt + 0.5 * GRAVITY * dt * dt;
        newSpeed = _speedY + GRAVITY * dt;
        
        this->setPositionY(this->getPositionY() + distance);
        _speedY = newSpeed;
        
        
        
    }
}

// dis = speed * dt + 0.5 * acc * dt * dt
//new speed = speed + acc * dt
void CRobin::Reset() {
    _state = kRobinStateStopped;
    SetStartSpeed();
	
}

int CRobin::GetState() {
	return _state;
}

void CRobin::SetState(int st) {
	_state = st;
}

void CRobin::SetStartSpeed() {
	_speedY = StartSpeedY;
}
