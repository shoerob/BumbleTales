/*
 *  BuildingItem.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/7/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "BuildingLevels.h"
#include "ShopItem.h"

class ShopListing;

class BuildingItem : public ShopItem
{
public:
	BuildingItem(BuildingName buildingName, int level, ShopListing *shopListing);
	virtual ~BuildingItem();

	BuildingName GetBuildingName() const;

	void SetPosition(float xLoc, float yLoc);
	void Render();
	void Update();
	

private:
	BuildingName m_buildingName;
	ShopListing *shopListing;
	bool isLocked;
	CR::Graphics::Sprite *lockedItemsSprite;
};