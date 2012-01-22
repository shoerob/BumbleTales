/*
 *  SeparatorItem.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SeparatorItem.h"
#include "AssetList.h"

SeparatorItem::SeparatorItem(HeaderType headerType)
{
	m_headerType = headerType;
	
	switch (m_headerType)
	{
		case CharacterHeader:
			itemSprite->SetImage(CR::AssetList::Shop_Header_Characters);
			break;
		case BuildingHeader:
			itemSprite->SetImage(CR::AssetList::Shop_Header_Buildings);
			break;
		default:
			break;
	}
	
	m_height = 45;
	//plusButton->Disabled(true);
	disableInput = true;
}

SeparatorItem::~SeparatorItem()
{
}

HeaderType SeparatorItem::GetHeaderType() const
{
	return m_headerType;
}