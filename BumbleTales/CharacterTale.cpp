/*
 *  CharacterTale.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/5/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CharacterTale.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

CharacterTale::CharacterTale(CharacterName characterName, int level)
{
	//pageSprite = graphics_engine->CreateSprite1();
	m_currPage = 0;
	
	pageAssets[0] = CR::AssetList::Scrapbook_Locked_Tale;
	pageAssets[1] = CR::AssetList::Scrapbook_Locked_Tale;
	pageAssets[2] = CR::AssetList::Scrapbook_Locked_Tale;
	
	switch (characterName)
	{
		case Mayor:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_1A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_1B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_1C;
			break;
		case Elder:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_2A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_2B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_2C;
			break;
		case Fireman:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_3A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_3B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_3C;
			break;
		case Dog:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_4A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_4B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_4C;
			break;
		case Baker:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_5A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_5B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_5C;
			break;
		case Teacher:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_6A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_6B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_6C;
			break;
		case Librarian:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_7A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_7B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_7C;
			break;
		case Romeo:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_8A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_8B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_8C;
			break;
		case Felicia:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_9A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_9B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_9C;
			break;
		case Bruiser:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_10A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_10B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_10C;
			break;
		case Marla:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_11A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_11B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_11C;
			break;
		case ChopChop:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_12A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_12B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_12C;
			break;
		case WonGameChapter:
			if (level >= 1) pageAssets[0] = CR::AssetList::Scrapbook_Character_Tale_13A;
			if (level >= 3) pageAssets[1] = CR::AssetList::Scrapbook_Character_Tale_13B;
			if (level >= 5) pageAssets[2] = CR::AssetList::Scrapbook_Character_Tale_13C;			
			break;
		default:
			break;
	}
	
	m_currPage = 0;
	//SetPage(0);
}

CharacterTale::~CharacterTale()
{
}

void CharacterTale::SetPage(int page, CR::Graphics::Sprite *pageSprite)
{
	m_currPage = page;
	pageSprite->SetImage(pageAssets[page]);
	
	//position
	if (pageAssets[page] == CR::AssetList::Scrapbook_Locked_Tale)
	{
		pageSprite->SetPositionAbsolute(160, 250);
	}
	else
	{
		pageSprite->SetPositionAbsolute(160, 250);
	}
}

bool CharacterTale::IsPageUnlocked(int page)
{
	return pageAssets[page] != CR::AssetList::Scrapbook_Locked_Tale;
}