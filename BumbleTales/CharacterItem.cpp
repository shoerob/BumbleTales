/*
 *  CharacterItem.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/7/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CharacterItem.h"
#include "AssetList.h"

CharacterItem::CharacterItem(CharacterName characterName, int level)
{
	m_characterName = characterName;
	m_level = level;
	m_infoAsset = CR::AssetList::Shop_Info_Characters;
	
	switch (m_characterName)
	{
		case Mayor:
			itemSprite->SetImage(CR::AssetList::Shop_Item_07);
			break;
		case Elder:
			itemSprite->SetImage(CR::AssetList::Shop_Item_08);
			break;
		case Fireman:
			itemSprite->SetImage(CR::AssetList::Shop_Item_09);
			break;
		case Dog:
			itemSprite->SetImage(CR::AssetList::Shop_Item_10);
			break;
		case Baker:
			itemSprite->SetImage(CR::AssetList::Shop_Item_11);
			break;
		case Teacher:
			itemSprite->SetImage(CR::AssetList::Shop_Item_12);
			break;
		case Librarian:
			itemSprite->SetImage(CR::AssetList::Shop_Item_13);
			break;
		case Romeo:
			itemSprite->SetImage(CR::AssetList::Shop_Item_14);
			break;
		case Felicia:
			itemSprite->SetImage(CR::AssetList::Shop_Item_15);
			break;
		case Bruiser:
			itemSprite->SetImage(CR::AssetList::Shop_Item_16);
			break;
		case Marla:
			itemSprite->SetImage(CR::AssetList::Shop_Item_17);
			break;
		case ChopChop:
			itemSprite->SetImage(CR::AssetList::Shop_Item_18);
			break;
		default:
			break;
	};
}

CharacterItem::~CharacterItem()
{
}

CharacterName CharacterItem::GetCharacterName() const
{
	return m_characterName;
}