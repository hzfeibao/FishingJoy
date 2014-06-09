
#ifndef __FishingJoy__ScheduleCounterProtocol__
#define __FishingJoy__ScheduleCounterProtocol__
class ScheduleCounterDelegate
{
public:
    /**
     *	@brief	    Required
     */
    virtual void scheduleTimeUp() = 0;
    /**
     *	@brief	    Optional
     *
     *	@param 	number 	需要设置的数字
     */
    virtual void setScheduleNumber(int number){return;};
};

#endif
