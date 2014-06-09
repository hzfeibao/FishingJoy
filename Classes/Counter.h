
#ifndef __FishingJoy__Counter__

#define __FishingJoy__Counter__

#include "cocos2d.h"

class Counter : public cocos2d::CCNode

{

public:
    Counter();
    static Counter* create(cocos2d::CCArray* presenters, int digit = 0);
    bool init(cocos2d::CCArray* presenters, int digit = 0);
    CC_PROPERTY(int, _digit, Digit);
protected:
    void visit();
    //存放0-9数字对应的节点
    cocos2d::CCNode* _presenters;
    //改变数字时播放滚动动画
    void animation(int digit);
};
#endif
