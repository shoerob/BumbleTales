/*
 *  SaveInfo.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SaveInfo.h"

SaveInfo::SaveInfo()
{
}

SaveInfo::~SaveInfo()
{
	//[saveData release];
}

void SaveInfo::Save()
{
	//[saveData writeToFile:GetSaveFilePath() atomically:NO];
}

void SaveInfo::Load()
{	
	// Load current save settings if possible, otherwise, revert to defaults
	/*if ([[NSFileManager defaultManager] fileExistsAtPath:GetSaveFilePath()])
	{
		saveData = [[NSMutableDictionary alloc] initWithContentsOfFile:GetSaveFilePath()];
	}
	else
	{
		saveData = [[NSMutableDictionary alloc] initWithContentsOfFile:GetDefaultsFilePath()];
	}*/
}

void SaveInfo::Reset()
{
	//saveData = [[NSMutableDictionary alloc] initWithContentsOfFile:GetDefaultsFilePath()];
	Save();
}
/*
int SaveInfo::GetIntForKey(NSString *key) const
{
	NSNumber *tmp = [saveData objectForKey:key];
	int n = [tmp intValue];
	return n;
}

void SaveInfo::SetIntForKey(int _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithInt:_value];
	[saveData setValue: tmp forKey:key];
	[tmp release];
}

bool SaveInfo::GetBoolForKey(NSString *key) const
{
	NSNumber *tmp = [saveData objectForKey:key];
	bool n = [tmp boolValue];
	return n;
}

void SaveInfo::SetBoolForKey(bool _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithBool:_value];
	[saveData setValue: tmp forKey:key];
	[tmp release];
}

NSMutableDictionary *SaveInfo::GetDictionaryForKey(NSString *key) const
{
	NSMutableDictionary *tmp = [saveData objectForKey:key];
	NSMutableDictionary *newDict = [[NSMutableDictionary alloc] initWithDictionary:tmp];
	return newDict;
}

void SaveInfo::SetDictionaryForKey(NSMutableDictionary *dict, NSString *key)
{
	//NSMutableDictionary *tmp = [saveData objectForKey:key];
	//[tmp release];
	[saveData removeObjectForKey:key];
	NSMutableDictionary *newDict = [[NSMutableDictionary alloc] initWithDictionary:dict];
	[saveData setObject:newDict forKey:key];
}

NSMutableArray *SaveInfo::GetArrayForKey(NSString *key) const
{
	NSMutableArray *tmp = [saveData objectForKey:key];
	NSMutableArray *newArr = [[NSMutableArray alloc] initWithArray:tmp];
	return newArr;
}

void SaveInfo::SetArrayForKey(NSMutableArray *array, NSString *key)
{
	[saveData removeObjectForKey:key];
	NSMutableArray *newArr = [[NSMutableArray alloc] initWithArray:array];
	[saveData setObject:newArr forKey:key];
}*/
