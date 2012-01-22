/*
 *  SeparatorItem.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "ShopItem.h"

enum HeaderType { CharacterHeader, BuildingHeader };

class SeparatorItem : public ShopItem
{
public:
	SeparatorItem(HeaderType headerType);
	virtual ~SeparatorItem();
	
	HeaderType GetHeaderType() const;
	
private:
	HeaderType m_headerType;
};