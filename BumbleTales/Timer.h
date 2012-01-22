/*
 *  Timer.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once

namespace CR {
	namespace Game {
		class Timer
		{
		public:
			Timer();
			virtual ~Timer();
			
			void Update();
			float GetTimePassed() const { return time_passed; }
			
		private:
			unsigned int starttime;
			unsigned int currenttime;
			double time_passed;
			double timerFreqInv;
		};
	}
}