/*
 *  StoryModeStructures.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "ResourceTile.h"

enum MedalType { NoMedal, BronzeMedal, SilverMedal, GoldMedal };

struct StoryModeScoreData
{
	int resourceCount[ResourceTile::tile_types];
	int largestChain;
	int levelTime;
	int powersUsed;
	bool gotTrophy;
	bool gotStar;
	
	MedalType tileMedals[ResourceTile::tile_types];
	MedalType chainMedal;
	MedalType powersUsedMedal;
	MedalType levelTimeMedal;
	
	StoryModeScoreData()
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
		gotTrophy = false;
		gotStar = false;
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