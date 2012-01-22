/*
 *  StoryModeScoreData.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

class StoryModeScoreData
{
public:
	StoryModeScoreData();
	//StoryModeScoreData();
	
	int resourceCount[6];
	int largestChain;

	void ResetScore()
	{
		for (int i = 0; i < 6; i++)
			resourceCount[i] = 0;
		
		largestChain = 0;
	}
};