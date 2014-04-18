#include "HelloWorldScene.h"
#include "Constants.h"
#include "CRobin.h"
#include "CCloud.h"


USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event) {
	
}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event) {
	
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event) {
	CCSetIterator i;
	CCTouch *touch;
	CCPoint tap;
	
	for (i = pTouches->begin(); i != pTouches->end(); i++) {
		touch = (CCTouch *)(*i);
		if(touch) {
			tap = touch->getLocation();
			CCLOG("Touched at %.2f,%.2f",tap.x,tap.y);
            
            if(_robin->boundingBox().containsPoint(tap)){
                if(_robin->GetState() == kRobinStateStopped){
                    _robin->SetState(kRobinStateMoving);
                    StartClouds();
                }else{
                    _robin->SetStartSpeed();
                }
            }
		}
	}
	
}

void HelloWorld::GameUpdate(float dt){
    if(_robin->getPositionY() < 0){
        _robin->setPositionY(_middleY);
        _robin->Reset();
        StopClouds();
        
    } else{
        _robin->UpdateRobin(dt);
    }
}

void HelloWorld::CreateClouds(){
    _clouds = new CCArray();
    AddCloud(kCloudSpeedSlow, ccp(700, 610), kCloudScaleSlow, kZindexCloudSlow);
    AddCloud(kCloudSpeedSlow, ccp(150, 570), kCloudScaleSlow, kZindexCloudSlow);
    
    AddCloud(kCloudSpeedFast, ccp(150, 300), kCloudScaleFast, kZindexCloudFast);
    AddCloud(kCloudSpeedFast, ccp(400, 500), kCloudScaleFast, kZindexCloudFast);
    AddCloud(kCloudSpeedFast, ccp(880, 400), kCloudScaleFast, kZindexCloudFast);
    
    
}
void HelloWorld::AddCloud(float speed, cocos2d::CCPoint position, float scale, int zIndex){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCloud *cloud = CCloud::createCloudWithFileName("Cloud-HD.png");
    cloud->SetSpeedAndWidth(speed, visibleSize.width);
    cloud->setPosition(position);
    cloud->setScale(scale);
    this->addChild(cloud, zIndex);
    _clouds->addObject(cloud);
}
void HelloWorld::StopClouds(){
    CCObject *it;
    CCARRAY_FOREACH(_clouds, it){
        CCloud *cloud = static_cast<CCloud*>(it);
        cloud->Stop();
    }
}
void HelloWorld::StartClouds(){
    CCObject *it;
    CCARRAY_FOREACH(_clouds, it){
        CCloud *cloud = static_cast<CCloud*>(it);
        cloud->Start();
    }
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    _middleY = visibleSize.height / 2;
	
	CCSprite *bgSprite = CCSprite::create("BG-HD123.png");
	bgSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgSprite, kZindexBackground);
    
    CCSprite *floorSprite = CCSprite::create("Floor-HD.png");
	floorSprite->setPosition(ccp(0,0));
    floorSprite->setAnchorPoint(ccp(0,0));
    this->addChild(floorSprite, kZindexFloor);
                             
	
	
	_robin = CRobin::createRobinWithFileName("Robin-HD.png");
	_robin->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_robin, kZindexRobin);
    CreateClouds();
    
    
	
	this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(HelloWorld::GameUpdate));
	
    return true;
}
