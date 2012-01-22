/*
 *  CharacterBonus.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/1/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CharacterBonus.h"

CharacterBonus::CharacterBonus()
{
}

CharacterBonus::~CharacterBonus()
{
}

CharBonus CharacterBonus::GetBonus(CharacterName charName, int level)
{
	if (level == 0)
		return CharBonus();
	
	switch (charName)
	{
		case Mayor:
			if (level == 1) return CharBonus(0, 0, 0, 0, 0, 1, NoTile);
			else if (level == 2) return CharBonus(0, 0, 0, 1, 0, 1, NoTile);
			else if (level == 3) return CharBonus(0, 0, 0, 1, 0, 2, NoTile);
			else if (level == 4) return CharBonus(0, 0, 0, 2, 0, 2, NoTile);
			else if (level == 5) return CharBonus(0, 0, 0, 2, 0, 2, Gold);
			break;
		case Elder:
			if (level == 1) return CharBonus(1, 0, 0, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(1, 0, 0, 0, 0, 1, NoTile);
			else if (level == 3) return CharBonus(2, 0, 0, 0, 0, 1, NoTile);
			else if (level == 4) return CharBonus(2, 0, 1, 0, 0, 1, NoTile);
			else if (level == 5) return CharBonus(2, 0, 1, 1, 0, 1, NoTile);
			break;
		case Fireman:
			if (level == 1) return CharBonus(0, 1, 0, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(0, 1, 1, 0, 0, 0, NoTile);
			else if (level == 3) return CharBonus(0, 2, 1, 0, 0, 0, NoTile);
			else if (level == 4) return CharBonus(0, 2, 2, 0, 0, 0, NoTile);
			else if (level == 5) return CharBonus(0, 2, 2, 0, 0, 0, Brick);
			break;
		case Dog:
			if (level == 1) return CharBonus(0, 1, 0, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(0, 1, 1, 0, 0, 0, NoTile);
			else if (level == 3) return CharBonus(1, 1, 1, 0, 0, 0, NoTile);
			else if (level == 4) return CharBonus(2, 1, 1, 0, 0, 0, NoTile);
			else if (level == 5) return CharBonus(2, 2, 1, 0, 0, 0, NoTile);
			break;
		case Baker:
			if (level == 1) return CharBonus(0, 0, 0, 1, 0, 0, NoTile);
			else if (level == 2) return CharBonus(0, 0, 0, 1, 1, 0, NoTile);
			else if (level == 3) return CharBonus(0, 0, 0, 2, 1, 0, NoTile);
			else if (level == 4) return CharBonus(0, 0, 0, 2, 1, 1, NoTile);
			else if (level == 5) return CharBonus(0, 0, 0, 2, 1, 1, Crystal);
			break;
		case Teacher:
			if (level == 1) return CharBonus(1, 0, 0, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(1, 1, 0, 0, 0, 0, NoTile);
			else if (level == 3) return CharBonus(2, 1, 0, 0, 0, 0, NoTile);
			else if (level == 4) return CharBonus(2, 1, 0, 0, 0, 1, NoTile);
			else if (level == 5) return CharBonus(2, 1, 0, 0, 0, 1, Leaf);
			break;
		case Librarian:
			if (level == 1) return CharBonus(0, 0, 1, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(1, 0, 1, 0, 0, 0, NoTile);
			else if (level == 3) return CharBonus(1, 1, 1, 0, 0, 0, NoTile);
			else if (level == 4) return CharBonus(2, 1, 1, 0, 0, 0, NoTile);
			else if (level == 5) return CharBonus(2, 1, 2, 0, 0, 0, NoTile);
			break;
		case Romeo:
			if (level == 1) return CharBonus(0, 0, 0, 0, 1, 0, NoTile);
			else if (level == 2) return CharBonus(0, 0, 0, 0, 2, 0, NoTile);
			else if (level == 3) return CharBonus(0, 0, 0, 0, 2, 1, NoTile);
			else if (level == 4) return CharBonus(0, 0, 0, 1, 2, 1, NoTile);
			else if (level == 5) return CharBonus(0, 0, 0, 2, 2, 1, NoTile);
			break;
		case Felicia:
			if (level == 1) return CharBonus(0, 0, 0, 0, 1, 0, NoTile);
			else if (level == 2) return CharBonus(0, 0, 0, 1, 1, 0, NoTile);
			else if (level == 3) return CharBonus(0, 0, 0, 1, 2, 0, NoTile);
			else if (level == 4) return CharBonus(1, 0, 0, 1, 2, 0, NoTile);
			else if (level == 5) return CharBonus(1, 0, 0, 1, 2, 0, Diamond);
			break;
		case Bruiser:
			if (level == 1) return CharBonus(0, 1, 0, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(0, 2, 0, 0, 0, 0, NoTile);
			else if (level == 3) return CharBonus(0, 2, 0, 0, 0, 1, NoTile);
			else if (level == 4) return CharBonus(1, 2, 0, 0, 0, 1, NoTile);
			else if (level == 5) return CharBonus(1, 2, 0, 1, 0, 1, NoTile);
			break;
		case Marla:
			if (level == 1) return CharBonus(1, 0, 0, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(1, 0, 0, 1, 0, 0, NoTile);
			else if (level == 3) return CharBonus(1, 1, 0, 1, 0, 0, NoTile);
			else if (level == 4) return CharBonus(1, 1, 1, 1, 0, 0, NoTile);
			else if (level == 5) return CharBonus(1, 2, 1, 1, 0, 0, NoTile);
			break;
		case ChopChop:
			if (level == 1) return CharBonus(0, 0, 1, 0, 0, 0, NoTile);
			else if (level == 2) return CharBonus(0, 0, 1, 0, 0, 1, NoTile);
			else if (level == 3) return CharBonus(0, 0, 2, 0, 0, 1, NoTile);
			else if (level == 4) return CharBonus(0, 1, 2, 0, 0, 1, NoTile);
			else if (level == 5) return CharBonus(0, 1, 2, 0, 0, 1, Wood);
			break;
		default:
			return CharBonus();
			break;
	}
	
	return CharBonus();
}

CharBonus CharacterBonus::GetBonusDiff(CharacterName charName, int level)
{
	//if (level == 0)
	//	return GetBonus(charName, level);
	//else
	//{
		CharBonus cBonus1 = GetBonus(charName, level + 1);
		CharBonus cBonus2 = GetBonus(charName, level);
		
		cBonus1.resourceBonus[0] = cBonus1.resourceBonus[0] - cBonus2.resourceBonus[0];
		cBonus1.resourceBonus[1] = cBonus1.resourceBonus[1] - cBonus2.resourceBonus[1];
		cBonus1.resourceBonus[2] = cBonus1.resourceBonus[2] - cBonus2.resourceBonus[2];
		cBonus1.resourceBonus[3] = cBonus1.resourceBonus[3] - cBonus2.resourceBonus[3];
		cBonus1.resourceBonus[4] = cBonus1.resourceBonus[4] - cBonus2.resourceBonus[4];
		cBonus1.resourceBonus[5] = cBonus1.resourceBonus[5] - cBonus2.resourceBonus[5];
		
		return cBonus1;
	//}
}

int CharacterBonus::GetBonusAsset(CharacterName charName, int level)
{
	CharBonus cBonus = GetBonusDiff(charName, level);
	
	if (level >= 5)
		return 12;
	
	if (cBonus.resourceBonus[0] > 0)
	{
		return 2;
	}
	else if (cBonus.resourceBonus[1] > 0)
	{
		return 0;
	}
	else if (cBonus.resourceBonus[2] > 0)
	{
		return 1;
	}
	else if (cBonus.resourceBonus[3] > 0)
	{
		return 3;
	}
	else if (cBonus.resourceBonus[4] > 0)
	{
		return 5;
	}
	else if (cBonus.resourceBonus[5] > 0)
	{
		return 4;
	}
	else if (cBonus.dropRateBonusType == Leaf)
	{
		return 8;
	}
	else if (cBonus.dropRateBonusType == Brick)
	{
		return 6;
	}
	else if (cBonus.dropRateBonusType == Wood)
	{
		return 7;
	}
	else if (cBonus.dropRateBonusType == Crystal)
	{
		return 9;
	}
	else if (cBonus.dropRateBonusType == Diamond)
	{
		return 11;
	}
	else if (cBonus.dropRateBonusType == Gold)
	{
		return 10;
	}
}