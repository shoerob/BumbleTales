/*
 *  TileDropRates.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/28/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "ResourceTile.h"

class TileDropRates
{
public:
	TileDropRates();
	~TileDropRates();
	
	void RestoreDefaults();
	void SetDropRate(ResourceType rType, int dropRate);
	int GetDropRate(ResourceType rType);
private:
	int dropRates[ResourceTile::tile_types];
};