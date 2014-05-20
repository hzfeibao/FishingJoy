//
//  Weapon.cpp
//  FishingJoy
//
//  Created by Ringo_D on 12-9-15.
//
//

#include "Weapon.h"
#include "StaticData.h"
USING_NS_CC;
Weapon* Weapon::create(CannonType type)
{
    Weapon* weapon = new Weapon();
    weapon->init(type);
    weapon->autorelease();
    return weapon;
}
bool Weapon::init(CannonType type)
{
    _cannon = Cannon::create(type);
    this->addChild(_cannon);
    
    _bullet = Bullet::create();
    _bullet->setVisible(false);
    this->addChild(_bullet);
    
    _fishingNet = FishingNet::create();
    _fishingNet->setVisible(false);
    this->addChild(_fishingNet);
    
    return true;
}
bool Weapon::shootTo(CCPoint touchLocation)
{
	CCLOG("Weapon::shootTo touchLocation.x: %f   y: %f", touchLocation.x , touchLocation.y);
    if(this->weaponStatus() != k_Weapon_Status_None){
		return false;
    }else{
		float distance = 180*(_cannon->getType()+1);
		CCPoint normal = ccpNormalize(ccpSub(touchLocation, this->getParent()->convertToWorldSpace(this->getPosition())));
		CCLOG("Weapon::shootTo normal.x: %f   y:%f" ,normal.x , normal.y);
		CCPoint verctor = ccpMult(normal, distance);
		CCPoint target = ccpAdd(this->getPosition(), verctor);
		CCLOG("Weapon::shootTo target.x: %f   y:%f" ,target.x ,target.y);
		_bullet->flyTo(target);
		return true;
    }
}
void Weapon::aimAt(CCPoint target)
{
    _cannon->aimAt(target);
}
int Weapon::weaponStatus()
{
    if(_bullet->isVisible()){
	return k_Weapon_Status_Bullet;
    }else if(_fishingNet->isVisible()){
	return k_Weapon_Status_Bullet;
    }
    return k_Weapon_Status_None;
}
void Weapon::end()
{
    CCPoint pos = _bullet->getPosition();
    _bullet->end();
    _particle->setPosition(pos);
    _particle->resetSystem();
    _fishingNet->showAt(pos);
}
int Weapon::getCannonType()
{
    return _cannon->getType();
}

CCPoint Weapon::getCollisionPoint()
{
        CCAssert(this->weaponStatus()==k_Weapon_Status_Bullet, "Do Not Call It Before Shooting");
	    if(this->weaponStatus()==k_Weapon_Status_Bullet){
		        return _bullet->getCollisionPoint();
		}
	    return CCPointZero;
}
CCRect Weapon::getCollisionArea()
{
    CCAssert(this->weaponStatus()==k_Weapon_Status_FishingNet, "Do Not Call It Before Collision");
    if(this->weaponStatus()==k_Weapon_Status_FishingNet){
        return _fishingNet->getCollisionArea();
    }
    return CCRectZero;
}
