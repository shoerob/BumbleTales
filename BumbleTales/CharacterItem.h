/*
 *  CharacterItem.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/7/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "CharacterLevels.h"
#include "ShopItem.h"

class CharacterItem : public ShopItem
{
public:
	CharacterItem(CharacterName characterName, int level);
	virtual ~CharacterItem();
	
	CharacterName GetCharacterName() const;
	
private:
	CharacterName m_characterName;

};