//
//  GameScene.cpp
//  FishingJoy
//
//  Created by Ringo_D on 12-9-8.
//
//

#include "GameScene.h"
#include "StaticData.h"
#include "FishingJoyData.h"
USING_NS_CC;
//todo 预载入资源，实现StartScene后将其删除
void GameScene::preloadResources()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fishingjoy_resource.plist");
    
    int frameCount = STATIC_DATA_INT("fish_frame_count");
    for (int type = k_Fish_Type_Red; type < k_Fish_Type_Count; type++) {
        CCArray* spriteFrames = CCArray::createWithCapacity(frameCount);
        for(int i = 0;i < frameCount;i++){
            CCString* filename = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_name_format"),type,i);
            CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
            spriteFrames->addObject(spriteFrame);
        }
        CCAnimation* fishAnimation = CCAnimation::createWithSpriteFrames(spriteFrames);
        fishAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));
        CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation"), type);
        CCAnimationCache::sharedAnimationCache()->addAnimation(fishAnimation, animationName->getCString());
    }
}
bool GameScene::init()
{
    preloadResources();
    if(CCScene::init()){
        _backgroundLayer = BackgroundLayer::create();
        this->addChild(_backgroundLayer);
        
        _fishLayer = FishLayer::create();
        this->addChild(_fishLayer);
        
        _cannonLayer = CannonLayer::create();
        this->addChild(_cannonLayer);
        
        _panelLayer = PanelLayer::create();
        this->addChild(_panelLayer);

        _menuLayer = MenuLayer::create();
        CC_SAFE_RETAIN(_menuLayer);
        
		_touchLayer = TouchLayer::create();
		this->addChild(_touchLayer);

	this->scheduleUpdate();
        return true;
    }
    return false;
}
void GameScene::pause()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Pause);
    this->addChild(_menuLayer);
}
void GameScene::resume()
{
    this->operateAllSchedulerAndActions(this, k_Operate_Resume);
    this->removeChild(_menuLayer, false);
}
void GameScene::sound()
{
}
void GameScene::music()
{
}
void GameScene::reset()
{
}
void GameScene::transToMainMenu()
{
}
GameScene::~GameScene()
{
    CC_SAFE_RELEASE(_menuLayer);
}
void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case k_Operate_Pause:
                node->pauseSchedulerAndActions();
                break;
            case k_Operate_Resume:
                node->resumeSchedulerAndActions();
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();
        if(array != NULL && array->count()>0){
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}
void GameScene::cannonAimat(CCPoint target)
{
    _cannonLayer->aimAt(target);
}
void GameScene::cannonShootTo(CCPoint target)
{
	CCLOG("GameScene::cannonShootTo target.x: %f   y: %f" ,target.x , target.y);
    _cannonLayer->shootTo(target);
}
void GameScene::update(float delta)
{
    CCLOG("GameScene::update() begin");
    checkOutCollision();
    CCLOG("GameScene::update() end");
}
//监测碰撞
void GameScene::checkOutCollision()
{
    CCLOG("GameScene::checkOutCollision() begin");
    Weapon* weapon = _cannonLayer->getWeapon();
    if(weapon->weaponStatus() == k_Weapon_Status_Bullet){
	bool flag = this->checkOutCollisionBetweenFishesAndBullet();
	if(flag){
	    this->checkOutCollisionBetweenFishesAndFishingNet();
	}
    }
    CCLOG("GameScene::checkOutCollision() end");
}
bool GameScene::checkOutCollisionBetweenFishesAndBullet()
{
    CCLOG("GameScene::checkOutCollisionBetweenFishesAndBullet() begin");
    Weapon* weapon = _cannonLayer->getWeapon();
    CCLOG("log 140");
    CCPoint bulletCollision = weapon->getCollisionPoint();
    CCLOG("log 142");
    CCArray* fishes = _fishLayer->getFishes();
    CCLOG("log 144");
    CCObject* iterator;
    CCLOG("log 146");
    CCARRAY_FOREACH(fishes, iterator){
	CCLOG("log 148");
	Fish* fish = (Fish*)iterator;
	CCLOG("log 150");
	if(fish->isRunning()){
	    CCLOG("log 152");
	    CCRect fishCollisionArea = fish->getCollisionArea();
	    CCLOG("log 154");
	    bool isCollision = fishCollisionArea.containsPoint(bulletCollision);
	    CCLOG("log 156");
	    if(isCollision){
		CCLOG("log 158");
		weapon->end();
		CCLOG("GameScene::checkOutCollisionBetweenFishesAndBullet() end true");
		return true;
	    }
	}
    }
    CCLOG("GameScene::checkOutCollisionBetweenFishesAndBullet() false");
    return false;
}
void GameScene::checkOutCollisionBetweenFishesAndFishingNet()
{
	
	/**/
	CCLOG("checkOutCollisionBetweenFishesAndFishingNet begin");
    Weapon* weapon = _cannonLayer->getWeapon();
    CCRect bulletCollision = weapon->getCollisionArea();
    CCArray* fishes = _fishLayer->getFishes();
    CCObject* iterator;
    CCLOG("test before foreach");
    CCARRAY_FOREACH(fishes, iterator){
	Fish* fish = (Fish*)iterator;
	if(fish->isRunning()){
	    CCRect fishCollisionArea = fish->getCollisionArea();
	    CCLOG("before fishCollisionArea.intersectsRect");
	    bool isCollision = fishCollisionArea.intersectsRect(bulletCollision);
	    CCLOG("after fishCollisionArea.intersectsRect");
	    if(isCollision){
		this->fishWillBeCaught(fish);
		CCLOG("after fishWillBeCaught");
	    }
	}
    }
	CCLOG("checkOutCollisionBetweenFishesAndFishingNet end");
}
void GameScene::fishWillBeCaught(Fish* fish)
{
	CCLOG("fishWillBeCaught begin");
    int weaponType = _cannonLayer->getWeapon()->getCannonType();
    int fishType = fish->getType();
    float fish_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("fish_percentage_format"),fishType)->getCString());
    float weapon_percentage = STATIC_DATA_FLOAT(CCString::createWithFormat(STATIC_DATA_STRING("weapon_percentage_format"), weaponType)->getCString());
    float percentage = weapon_percentage * fish_percentage;
    if(CCRANDOM_0_1() < percentage){
	fish->beCaught();
    }
	CCLOG("fishWillBeCaught end");
}
