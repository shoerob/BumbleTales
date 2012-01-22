//#include "StdAfx.h"
#include "Timer.h"

using namespace CR::Utility;

Timer::Timer(void)
{
	Reset();
}

Timer::~Timer(void)
{
}

/*!
	Reset the total time back to 0. Also resets the last frame time back to 0.
	Generally only used when total time is needed.
*/
void Timer::Reset(void)
{
#ifndef WIN32
	starttime = mach_absolute_time();
	
	mach_timebase_info_data_t time_info;
	mach_timebase_info(&time_info);
	timerFreqInv = time_info.numer/(double)time_info.denom;
	timerFreqInv /= 1000000000.0f;
	
	totalTime = 0;
	timeLastFrame = 0;
#endif
}

/*!
	Updates the last frame time, and the total time. 
*/
void Timer::Update(void)
{
#ifndef WIN32
	currenttime = mach_absolute_time();
	timeLastFrame = (currenttime - starttime)*timerFreqInv;
	starttime = currenttime;
	totalTime += timeLastFrame;
#endif
}
