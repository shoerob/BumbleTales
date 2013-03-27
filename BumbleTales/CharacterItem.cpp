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

using namespace CR::Math;

CharacterItem::CharacterItem(CharacterName characterName, int level)
{
	m_characterName = characterName;
	m_level = level;
	m_infoAsset = CR::AssetList::Shop_Info_Characters;
	m_infoDesignSize = int2(212, 39);

	switch (m_characterName)
	{
		case Mayor:
			itemSprite->SetImage(CR::AssetList::Shop_Item_07);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Elder:
			itemSprite->SetImage(CR::AssetList::Shop_Item_08);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Fireman:
			itemSprite->SetImage(CR::AssetList::Shop_Item_09);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Dog:
			itemSprite->SetImage(CR::AssetList::Shop_Item_10);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Baker:
			itemSprite->SetImage(CR::AssetList::Shop_Item_11);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Teacher:
			itemSprite->SetImage(CR::AssetList::Shop_Item_12);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Librarian:
			itemSprite->SetImage(CR::AssetList::Shop_Item_13);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Romeo:
			itemSprite->SetImage(CR::AssetList::Shop_Item_14);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Felicia:
			itemSprite->SetImage(CR::AssetList::Shop_Item_15);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Bruiser:
			itemSprite->SetImage(CR::AssetList::Shop_Item_16);
			itemSprite->SetDesignSize(248, 70);
			break;
		case Marla:
			itemSprite->SetImage(CR::AssetList::Shop_Item_17);
			itemSprite->SetDesignSize(248, 70);
			break;
		case ChopChop:
			itemSprite->SetImage(CR::AssetList::Shop_Item_18);
			itemSprite->SetDesignSize(248, 70);
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