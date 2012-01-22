/*
 *  ArcadeModeStructures.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/3/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "ResourceTile.h"

struct ArcadeModeScoreData
{
	int resourceCount[ResourceTile::tile_types];
	int largestChain;
	int levelTime;
	int powersUsed;
	int score;
	int level;
	bool newHighScore;
	bool gotTrophy;
	
	ArcadeModeScoreData()
	{
		Reset();
	}
	
	void Reset()
	{
		for (int i = 0; i < ResourceTile::tile_types; i++)
			resourceCount[i] = 0;
		
		largestChain = 0;
		levelTime = 0;
		powersUsed = 0;
		score = 0;
		level = 0;
		newHighScore = false;
		gotTrophy = false;
	}
	
	int GetResourceCount(ResourceType rType)
	{
		return resourceCount[(int)rType];
	}
	
	void SetResourceCount(ResourceType rType, int _value)
	{
		resourceCount[(int)rType] = _value;
	}
};