//
//  FishLayer.cpp
//  FishingJoy
//
//  Created by Ringo_D on 12-9-8.
//
//

#include "FishLayer.h"
USING_NS_CC;
bool FishLayer::init()
{
    if(CCLayer::init()){
        int capacity = 50;
        _fishes = CCArray::createWithCapacity(capacity);
        CC_SAFE_RETAIN(_fishes);
        
        for(int i = 0;i < capacity;i++){
            int type = CCRANDOM_0_1()*2;
            Fish* fish = Fish::create((FishType)type);
            _fishes->addObject(fish);
        }
        this->schedule(schedule_selector(FishLayer::addFish), 3.0);
        return true;
    }
    return false;
}
void FishLayer::addFish(float dt)
{
   // CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int countToAdd = CCRANDOM_0_1() * 10 + 1;
    int countHasAdded = 0;
    CCObject* iterator;
    CCARRAY_FOREACH(_fishes,  iterator){
        Fish* fish = (Fish*)iterator;
        if(fish->isRunning() == false){
            this->addChild(fish);
			this->resetFish(fish);
            //todo 后期应重设Fish产生时的随机坐标
           // int randomX = CCRANDOM_0_1() * winSize.width;
           // int randomY = CCRANDOM_0_1() * winSize.height;
           // fish->setPosition(CCPointMake(randomX, randomY));
            countHasAdded++;
            if(countToAdd == countHasAdded){
                break;
            }
        }
    }
}
FishLayer::~FishLayer()
{
    CC_SAFE_RELEASE(_fishes);
}

void FishLayer::resetFish(Fish* fish)
{
    fish->reset();
    CCPoint start, destination;
    float startX, startY, endX, endY;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize fishSize = fish->getFishSprite()->getContentSize();
    int direction = CCRANDOM_0_1()*2;
    if(direction){
	fish->setRotation(180);
	startX= winSize.width + fishSize.width*0.5;
	endX = -fishSize.width*0.5;
    }else{
	fish->setRotation(0);
	startX = -fishSize.width*0.5;
	endX = winSize.width + fishSize.width*0.5;
    }
    startY = CCRANDOM_0_1()*(winSize.height-2*fishSize.height) + fishSize.height;
    endY = startY;

    start = CCPointMake(startX, startY);
    destination = CCPointMake(endX, endY);
    fish->setPosition(start);
    fish->moveTo(destination);

}
