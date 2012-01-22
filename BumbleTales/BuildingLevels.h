/*
 *  BuildingLevels.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/29/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
//#import <UIKit/UIKit.h>
#include <stdio.h>

enum BuildingName { TownHall = 0, PoliceStation = 1, Firehouse = 2, Lodge = 3, Theatre = 4, Greenhouse = 5, NoBuilding = 6, NUM_BUILDING_NAMES = 7 };
//static const NSString *BuildingNameStrings[] = {@"TownHall", @"PoliceStation", @"Firehouse", @"Lodge", @"Theatre", @"Greenhouse" };

class BuildingLevels
{
public:
	BuildingLevels(/*NSMutableDictionary *buildingLevels*/);
	virtual ~BuildingLevels();
	
	int GetBuildingLevel(BuildingName bName) const { return m_levels[bName]; }
	void SetBuildingLevel(BuildingName bName, int _value) { m_levels[bName] = _value; }
	
	void Save(FILE *_file);
	void Load(FILE *_file);
	void Reset();

private:
	int m_levels[NUM_BUILDING_NAMES];

	/*NSMutableDictionary *GetDictionary();
	
private:
	NSMutableDictionary *m_buildingLevels;
	
	int GetIntForKey(NSString *key) const;
	void SetIntForKey(int _value, NSString *key);*/
};