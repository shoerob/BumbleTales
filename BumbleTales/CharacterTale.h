/*
 *  CharacterTale.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/5/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "Graphics.h"
#include "CharacterLevels.h"

class CharacterTale
{
public:
	CharacterTale(CharacterName characterName, int level);
	virtual ~CharacterTale();


	void SetPage(int page, CR::Graphics::Sprite *pageSprite);
	//int GetAsset() const;
	bool IsPageUnlocked(int page);
	
private:
	int m_currPage;
	//CR::Graphics::Sprite *pageSprite;
	int pageAssets[3];
};