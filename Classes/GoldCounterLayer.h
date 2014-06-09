
#ifndef __FishingJoy__GoldCounter__
#define __FishingJoy__GoldCounter__
#include "cocos2d.h"
class GoldCounterLayer : public cocos2d::CCNode
{
public:
    static GoldCounterLayer* create(int number = 0);
    bool init(int number = 0);
    void setNumber(int number,int ceiling = 999999);
    CC_SYNTHESIZE_READONLY(int, _number, Number);
protected:
    void getNumAtPos(int pos);
};

#endif
