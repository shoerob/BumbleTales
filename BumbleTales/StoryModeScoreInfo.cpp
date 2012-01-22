/*
 *  StoryModeScoreInfo.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryModeScoreInfo.h"
#include <sstream>
#include <string>
#include <iostream>

StoryModeScoreInfo::StoryModeScoreInfo()
{
	//scoreInfo = [[NSMutableDictionary alloc] initWithCapacity:20];
}

StoryModeScoreInfo::~StoryModeScoreInfo()
{
	//[scoreInfo release];
}

void StoryModeScoreInfo::ResetScore()
{
	// TODO: Update/Save New High Score Info
	
//	[scoreInfo release];
	//scoreInfo = [[NSMutableDictionary alloc] initWithCapacity:20];
}

void StoryModeScoreInfo::SetResourceCount(ResourceType resourceType, int _value)
{
	/*stringstream sValue;
	sValue << "ResourceTypeCount_" << (int)resourceType;
	NSString *tmpString = [[NSString alloc] initWithCString: sValue.str().c_str()];
	SetIntForKey(_value, tmpString);*/
}

int StoryModeScoreInfo::GetResourceCount(ResourceType resourceType)
{
	/*stringstream sValue;
	sValue << "ResourceTypeCount_" << (int)resourceType;
	NSString *tmpString = [[NSString alloc] initWithCString: sValue.str().c_str()];
	return GetIntForKey(tmpString);*/
	return 0;
}

void StoryModeScoreInfo::SetLargestChain(int _value)
{
	//SetIntForKey(_value, @"LargestChain");
}

int StoryModeScoreInfo::GetLargestChain() const
{
	return 0;//GetIntForKey(@"LargestChain");
}

void StoryModeScoreInfo::SetLevelTime(float _value)
{
	//SetFloatForKey(_value, @"LevelTime");
}

float StoryModeScoreInfo::GetLevelTime() const
{
	return 0;//GetFloatForKey(@"LevelTime");
}
/*
int StoryModeScoreInfo::GetIntForKey(NSString *key) const
{
	NSNumber *tmp = [scoreInfo objectForKey:key];
	int n = [tmp intValue];
	return n;
}

void StoryModeScoreInfo::SetIntForKey(int _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithInt:_value];
	[scoreInfo setValue: tmp forKey:key];
	[tmp release];
}

float StoryModeScoreInfo::GetFloatForKey(NSString *key) const
{
	NSNumber *tmp = [scoreInfo objectForKey:key];
	float n = [tmp floatValue];
	return n;
}

void StoryModeScoreInfo::SetFloatForKey(float _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithFloat:_value];
	[scoreInfo setValue: tmp forKey:key];
	[tmp release];
}

bool StoryModeScoreInfo::GetBoolForKey(NSString *key) const
{
	NSNumber *tmp = [scoreInfo objectForKey:key];
	bool n = [tmp boolValue];
	return n;
}

void StoryModeScoreInfo::SetBoolForKey(bool _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithBool:_value];
	[scoreInfo setValue: tmp forKey:key];
	[tmp release];
}*/