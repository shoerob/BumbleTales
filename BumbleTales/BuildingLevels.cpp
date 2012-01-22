/*
 *  BuildingLevels.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/29/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "BuildingLevels.h"
#include <memory.h>

BuildingLevels::BuildingLevels(/*NSMutableDictionary *buildingLevels*/)
{
	Reset();
}

BuildingLevels::~BuildingLevels()
{
}

void BuildingLevels::Save(FILE *_file)
{
	fwrite(m_levels, 1, sizeof(m_levels), _file);
}

void BuildingLevels::Load(FILE *_file)
{
	fread(m_levels, 1, sizeof(m_levels), _file);
}

void BuildingLevels::Reset()
{
	memset(m_levels, 0, sizeof(m_levels));
}
