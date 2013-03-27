/*
 *  BuildingItem.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/7/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "BuildingItem.h"
#include "AssetList.h"
#include "ShopListing.h"

using namespace CR::Math;

extern CR::Graphics::GraphicsEngine *graphics_engine;

BuildingItem::BuildingItem(BuildingName buildingName, int level, ShopListing *shopListing)
{
	lockedItemsSprite = graphics_engine->CreateSprite1(false, 265);
	lockedItemsSprite->SetImage(CR::AssetList::Shop_Locks);
	lockedItemsSprite->SetDesignSize(254, 69);
	lockedItemsSprite->SetFrameSet((int)buildingName);
	
	this->shopListing = shopListing;
	m_buildingName = buildingName;
	m_level = level;
	isLocked = true;
	switch (m_buildingName)
	{
		case TownHall:
			itemSprite->SetImage(CR::AssetList::Shop_Item_01);
			itemSprite->SetDesignSize(248, 70);
			m_infoAsset = CR::AssetList::Shop_Info_Gold;
			m_infoDesignSize = int2(239, 40);
			break;
		case PoliceStation:
			itemSprite->SetImage(CR::AssetList::Shop_Item_02);
			itemSprite->SetDesignSize(248, 70);
			m_infoAsset = CR::AssetList::Shop_Info_Blue;
			m_infoDesignSize = int2(241, 40);
			break;
		case Firehouse:
			itemSprite->SetImage(CR::AssetList::Shop_Item_03);
			itemSprite->SetDesignSize(248, 70);
			m_infoAsset = CR::AssetList::Shop_Info_Fire;
			m_infoDesignSize = int2(251, 39);
			break;
		case Lodge:
			itemSprite->SetImage(CR::AssetList::Shop_Item_04);
			itemSprite->SetDesignSize(248, 70);
			m_infoAsset = CR::AssetList::Shop_Info_Brown;
			m_infoDesignSize = int2(261, 39);
			break;
		case Theatre:
			itemSprite->SetImage(CR::AssetList::Shop_Item_05);
			itemSprite->SetDesignSize(248, 70);
			m_infoAsset = CR::AssetList::Shop_Info_Pink;
			m_infoDesignSize = int2(221, 40);
			break;
		case Greenhouse:
			itemSprite->SetImage(CR::AssetList::Shop_Item_06);
			itemSprite->SetDesignSize(248, 70);
			m_infoAsset = CR::AssetList::Shop_Info_Green;
			m_infoDesignSize = int2(247, 40);
			break;
		default:
			break;
	}
}

BuildingItem::~BuildingItem()
{
	lockedItemsSprite->Release();
}

BuildingName BuildingItem::GetBuildingName() const
{
	return m_buildingName;
}

void BuildingItem::SetPosition(float xLoc, float yLoc)
{
	ShopItem::SetPosition(xLoc, yLoc);
	lockedItemsSprite->SetPositionAbsolute(xLoc, yLoc);
}

void BuildingItem::Update()
{
	//ShopItem::Update();
	
	starMeter->SetFilledStars(m_level);
	
	if (isLocked)
	{
		isLocked = shopListing->IsBuildingLocked(m_buildingName);
	}
	
	if (starMeter->GetStarIndicator() <= 0 || starMeter->GetFilledStars() >= 5 || isLocked)
		plusButton->Disabled(true);
	else
		plusButton->Disabled(false);
}

void BuildingItem::Render()
{
	ShopItem::Render();
	
	if (isLocked)
	{
		lockedItemsSprite->Render();
	}
}