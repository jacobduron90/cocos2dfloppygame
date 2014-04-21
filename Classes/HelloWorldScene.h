#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CRobin.h"

class CRobin;
class CTube;
class HelloWorld : public cocos2d::CCLayer
{
private:
	CRobin *_robin;
    float _middleY;
    cocos2d::CCArray* _clouds;
    cocos2d::CCArray* _tubes;
    
    cocos2d::CCLabelTTF *_scoreLabel;
    cocos2d::CCLabelTTF *_highScoreLabel;
    
    float _nextSpawnTime;
    float _lastSpawnTime;
    float _floorY;
    bool _gameStarted;
    
    
    void GameUpdate(float dt);
    void CreateClouds();
    void AddCloud(float speed, cocos2d::CCPoint position, float scale, int zIndex, const char *name, const float xOffset);
    void StopClouds();
    void StartClouds();
    void StopGame();
    void StartGame();
    void GameOver();
    void SetSpawnTime();
    void SpawnNewTubes();
    
    void SpawnUpperOrLower(bool isUpper);
    void SpawnTubePair();
    void SpawnATube(bool isUpper, float yPos);
    CTube *GetNextTube();
	
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
};

#endif // __HELLOWORLD_SCENE_H__
