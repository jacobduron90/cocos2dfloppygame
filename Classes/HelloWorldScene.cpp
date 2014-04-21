#include "HelloWorldScene.h"
#include "Constants.h"
#include "CRobin.h"
#include "CCloud.h"
#include "CTube.h"


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
                    StartGame();
                }else{
                    _robin->SetStartSpeed();
                }
            }
		}
	}

}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event) {
	
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event) {
		
}

void HelloWorld::SetSpawnTime(){
    _lastSpawnTime = 0;
    _nextSpawnTime = (float)(rand() % kTubeSpawnVariance) / 10 + kTubeSpawnMinTime;
    
}
void HelloWorld::SpawnNewTubes(){
    int ourChance = rand() % 4 + 1;
    if(ourChance == 1){
        SpawnUpperOrLower(true);
    }else if(ourChance == 2){
        SpawnUpperOrLower(false);
    }else{
        SpawnTubePair();
    }
}
void HelloWorld::SpawnUpperOrLower(bool isUpper){
    int Ymax = isUpper == true ? kSingleGapTop : _middleY;
    int Ymin = isUpper == true ? _middleY : kSingleGapBottom;
    int YRange = abs(Ymax - Ymin);
    
    int Ypos = Ymax - rand() % YRange;
    SpawnATube(isUpper, Ypos);
}
void HelloWorld::SpawnTubePair(){
    int Gap = kDoubleGapMin + (rand() % (kDoubleGapMax - kDoubleGapMin));
    int YRange = kDoubleapTop - Gap - kDoubleGapBottom;
    int TopY = kDoubleapTop - (rand() % YRange);
    int BottomY = TopY - Gap;
    SpawnATube(true, TopY);
    SpawnATube(false, BottomY);
}
void HelloWorld::SpawnATube(bool isUpper, float yPos){
    CTube *tube = GetNextTube();
    if(isUpper == true){
        tube->setAnchorPoint(ccp(0.5, 0));
        tube->setFlipY(false);
    }else{
        tube->setAnchorPoint(ccp(0.5, 1));
        tube->setFlipY(true);
    }
    
    tube->setPositionY(yPos);
    tube->Start();
}
CTube *HelloWorld::GetNextTube(){
    CCObject *it;
    
    CCARRAY_FOREACH(_tubes, it){
        CTube *tube = static_cast<CTube*>(it);
        if(tube->GetState() == kTubeStateInactive){
            return tube;
        }
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CTube *newTube = CTube::createTubeWithFileName("Tube-HD.png");
    newTube->Initialize(kTreeSpeed, visibleSize.width, kTubeOffsetX, kTubeInactiveX);
    this->addChild(newTube, kZindexTube);
    _tubes->addObject(newTube);
    return newTube;
    
}

void HelloWorld::GameUpdate(float dt){
    if(_gameStarted == true){
        _lastSpawnTime += dt;
        if(_lastSpawnTime > _nextSpawnTime){
            SetSpawnTime();
            SpawnNewTubes();
        }
        bool gameOver = false;
        if(_robin->getPositionY() < _floorY){
            
            gameOver = true;
            
        } else{
            CCObject *it;
            CCARRAY_FOREACH(_tubes, it){
                CTube *tube = static_cast<CTube*>(it);
                if(tube->GetState() == kTubeStateActive){
                    if(_robin->TubeCollisionBox().intersectsRect(tube->boundingBox())){
                        gameOver = true;
                    }
                }
            }

        }
        if(gameOver == true){
            GameOver();
        }else{
            _robin->UpdateRobin(dt);
        }
    }
}

void HelloWorld::CreateClouds(){
    _clouds = new CCArray();
    AddCloud(kCloudSpeedSlow, ccp(700, 610), kCloudScaleSlow, kZindexCloudSlow, "Cloud-HD.png", kCloudRestartX);
    AddCloud(kCloudSpeedSlow, ccp(150, 570), kCloudScaleSlow, kZindexCloudSlow, "Cloud-HD.png", kCloudRestartX);
    
    AddCloud(kCloudSpeedFast, ccp(150, 300), kCloudScaleFast, kZindexCloudFast, "Cloud-HD.png", kCloudRestartX);
    AddCloud(kCloudSpeedFast, ccp(400, 500), kCloudScaleFast, kZindexCloudFast, "Cloud-HD.png", kCloudRestartX);
    AddCloud(kCloudSpeedFast, ccp(880, 400), kCloudScaleFast, kZindexCloudFast, "Cloud-HD.png", kCloudRestartX);
    
    AddCloud(kMountSpeed, ccp(300, 170), kMountScale, kZindexBackground, "Mount-HD.png", kMountRestartX);
    AddCloud(kMountSpeed, ccp(800, 170), kMountScale, kZindexBackground, "Mount-HD.png", kMountRestartX);
    
    AddCloud(kTreeSpeed, ccp(128, 72), kTreeScale, kZindexTree, "Tree-HD.png", kCloudRestartX);
    AddCloud(kTreeSpeed, ccp(624, 72), kTreeScale, kZindexTree, "Tree-HD.png", kCloudRestartX);
    AddCloud(kTreeSpeed, ccp(864, 72), kTreeScale, kZindexTree, "Tree-HD.png", kCloudRestartX);
   
    
    
}
void HelloWorld::AddCloud(float speed, cocos2d::CCPoint position, float scale, int zIndex, const char *name, const float xOffset){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCloud *cloud = CCloud::createCloudWithFileName(name);
    cloud->SetSpeedAndWidth(speed, visibleSize.width, xOffset);
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
    CCARRAY_FOREACH(_tubes, it){
        CTube *tube = static_cast<CTube*>(it);
        tube->stopAllActions();
    }
}
void HelloWorld::StartClouds(){
    CCObject *it;
    CCARRAY_FOREACH(_clouds, it){
        CCloud *cloud = static_cast<CCloud*>(it);
        cloud->Start();
    }
    CCARRAY_FOREACH(_tubes, it){
        CTube *tube = static_cast<CTube*>(it);
        tube->Stop();
    }
}

void HelloWorld::StopGame(){
    StopClouds();
    _gameStarted = false;
    _nextSpawnTime = 0.2;
}
void HelloWorld::StartGame(){
    _robin->SetState(kRobinStateMoving);
    _robin->setPositionY(_middleY);
       StartClouds();
    _gameStarted = true;
}

void HelloWorld::GameOver(){
    _robin->Reset();
    StopGame();
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
    
    srand(time(NULL));
    
    const float ScoreFontSize = 24;
    const float ScorePositionX = 24;
    const float ScorePositionY = 12;
    
    
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    _scoreLabel = CCLabelTTF::create("Score 0", kFontName, ScoreFontSize);
    _scoreLabel->setAnchorPoint(ccp(0,1));
    _scoreLabel->setPosition(ccp(ScorePositionX, visibleSize.height - ScorePositionY));
    this->addChild(_scoreLabel, kZindexRobin);
    
    _highScoreLabel = CCLabelTTF::create("Best 0", kFontName, ScoreFontSize);
    _highScoreLabel->setAnchorPoint(ccp(0,1));
    _highScoreLabel->setPosition(ccp(ScorePositionX, _scoreLabel->boundingBox().origin.y - ScorePositionY));
    this->addChild(_highScoreLabel, kZindexRobin);

    
    _middleY = visibleSize.height / 2;
	
	CCSprite *bgSprite = CCSprite::create("BG-HD123.png");
	bgSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgSprite, kZindexBackground);
    
    CCSprite *floorSprite = CCSprite::create("Floor-HD.png");
	floorSprite->setPosition(ccp(0,0));
    floorSprite->setAnchorPoint(ccp(0,0));
    this->addChild(floorSprite, kZindexFloor);
    
    _floorY = floorSprite->boundingBox().size.height / 2;
                             
	
	
	_robin = CRobin::createRobinWithFileName("Robin-HD.png");
	_robin->setPosition(ccp(kRobinStartX, visibleSize.height / 2));
	this->addChild(_robin, kZindexRobin);
    CreateClouds();
    _tubes = new CCArray();
    StopGame();
    
    
	
	this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(HelloWorld::GameUpdate));
	
    return true;
}
