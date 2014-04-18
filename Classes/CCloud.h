//
//  CCloud.h
//  HelloCpp
//
//  Created by Jacob Duron on 4/18/14.
//
//

#ifndef __HelloCpp__CCloud__
#define __HelloCpp__CCloud__

#include "cocos2d.h"

class CCloud : public cocos2d::CCSprite {
	
public:
    
	static CCloud* createCloudWithFileName(const char *fileName);
	void Start();
    void Stop();
    void SetSpeedAndWidth(const float speed, const float width);
    
	
private:
    
    void ReachedDestination();
    
    float _speed;
    float _screenWidth;
    float _pixelsPerSec;
    
	
};


#endif /* defined(__HelloCpp__CCloud__) */
