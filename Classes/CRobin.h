//
//  CRobin.h
//  HelloCpp
//
//  Created by Jacob Duron on 4/18/14.
//
//

#ifndef __HelloCpp__CRobin__
#define __HelloCpp__CRobin__

#include "cocos2d.h"

class CRobin : public cocos2d::CCSprite {
	
public:
    
	static CRobin* createRobinWithFileName(const char *fileName);
	void UpdateRobin(float dt);
	void Reset();
	int GetState();
	void SetState(int st);
	void SetStartSpeed();
	
private:
	
	
	int _state;
	float _speedY;
};

#endif /* defined(__HelloCpp__CRobin__) */
