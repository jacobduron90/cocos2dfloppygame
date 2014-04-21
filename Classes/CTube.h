//
//  CTube.h
//  HelloCpp
//
//  Created by Jacob Duron on 4/19/14.
//
//

#ifndef __HelloCpp__CTube__
#define __HelloCpp__CTube__

#include "cocos2d.h"

class CTube : public cocos2d::CCSprite {
	
public:
    
	static CTube* createTubeWithFileName(const char *fileName);
	void Start();
    void Stop();
    void Initialize(const float speed, const float width, const float xOffSet, const float InactiveX);
    int GetState();
    
	
private:
    
    void ReachedDestination();
    
    int _state;
    float _speed;
    float _screenWidth;
    float _pixelsPerSec;
    float _xOffset;
    float _InactiveX;
    
	
};


#endif /* defined(__HelloCpp__CTube__) */
