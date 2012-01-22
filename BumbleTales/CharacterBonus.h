/*
 *  CharacterBonus.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/1/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "CharacterLevels.h"
#include "ResourceTile.h"

struct CharBonus
{
	//int leaf;
	//int brick;
	//int wood;
	//int crystal;
	//int diamond;
	//int gold;

	int resourceBonus[6];
	
	ResourceType dropRateBonusType;
	
	CharBonus()
	{
		for (int i = 0; i < 6; i++)
			resourceBonus[i] = 0;
		
		dropRateBonusType = NoTile;
	}
	
	/*CharBonus(CharBonus &cBonus)
	{
		resourceBonus[0] = cBonus.resourceBonus[0];
		resourceBonus[1] = cBonus.resourceBonus[1];
		resourceBonus[2] = cBonus.resourceBonus[2];
		resourceBonus[3] = cBonus.resourceBonus[3];
		resourceBonus[4] = cBonus.resourceBonus[4];
		resourceBonus[5] = cBonus.resourceBonus[5];
		
		dropRateBonusType = cBonus.dropRateBonusType;
	}*/
	
	CharBonus(int _leaf, int _brick, int _wood, int _crystal, int _diamond, int _gold, ResourceType _dropRateBonusType)
	{
		resourceBonus[0] = _leaf;
		resourceBonus[1] = _brick;
		resourceBonus[2] = _wood;
		resourceBonus[3] = _crystal;
		resourceBonus[4] = _diamond;
		resourceBonus[5] = _gold;
		
		dropRateBonusType = _dropRateBonusType;
	}
	
	int GetResourceBonus(ResourceType rType)
	{
		return resourceBonus[(int)rType];
	}
};

class CharacterBonus
{
public:
	CharacterBonus();
	virtual ~CharacterBonus();
	
	CharBonus GetBonus(CharacterName charName, int level);
	CharBonus GetBonusDiff(CharacterName charName, int level);
	int GetBonusAsset(CharacterName charName, int level);
private:
	
};