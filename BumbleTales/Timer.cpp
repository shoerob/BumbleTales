/*
 *  Timer.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "Timer.h"
#include <algorithm>
#include <s3e.h>
using namespace std;
using namespace CR::Game;

Timer::Timer()
{
	starttime = s3eTimerGetMs();
		
	timerFreqInv = 1/1000.0f;
	time_passed = 0;	
}

Timer::~Timer()
{
}

void Timer::Update()
{
	currenttime = s3eTimerGetMs();
	time_passed = (currenttime - starttime)*timerFreqInv;
	starttime = currenttime;
}