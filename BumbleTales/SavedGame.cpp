/*
 *  SavedGame.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SavedGame.h"

SavedGame::SavedGame()
{
}

SavedGame::~SavedGame()
{
	//[saveData release];
}
/*
NSString* SavedGame::GetDefaultsFilePath()
{
	return [[NSBundle mainBundle] pathForResource:@"savedata" ofType:@"plist"];
}

NSString* SavedGame::GetSaveFilePath()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	return [documentsDirectory stringByAppendingPathComponent:kSaveFileName];
}*/

void SavedGame::Save()
{
	//[saveData writeToFile:GetSaveFilePath() atomically:NO];
}

void SavedGame::Load()
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

void SavedGame::Reset()
{
	//saveData = [[NSMutableDictionary alloc] initWithContentsOfFile:GetDefaultsFilePath()];
}

void SavedGame::SaveOnTerminate()
{
	if (OnSaveOnTerminate.Size() > 0)
		OnSaveOnTerminate();
}

int SavedGame::GetLevel() const
{
	return 0;//GetIntForKey(@"Level");
}

void SavedGame::SetLevel(int _value)
{
	//SetIntForKey(_value, @"Level");
}

int SavedGame::GetStars() const
{
	return 0;//GetIntForKey(@"Stars");
}

void SavedGame::SetStars(int _value)
{
	//SetIntForKey(_value, @"Stars");
}

bool SavedGame::GetOptionsHintsOn() const
{
	return false;//GetBoolForKey(@"OptionsHintsOn");
}

void SavedGame::SetOptionsHintsOn(bool _value)
{
	//SetBoolForKey(_value, @"OptionsHintsOn");
}

bool SavedGame::GetOptionsMusicOn() const
{
	return false;//GetBoolForKey(@"OptionsMusicOn");
}

void SavedGame::SetOptionsMusicOn(bool _value)
{
	//SetBoolForKey(_value, @"OptionsMusicOn");
}

bool SavedGame::GetOptionsSoundOn() const
{
	return false;//GetBoolForKey(@"OptionsSoundOn");
}

void SavedGame::SetOptionsSoundOn(bool _value)
{
	//SetBoolForKey(_value, @"OptionsSoundOn");
}
/*
int SavedGame::GetIntForKey(NSString *key) const
{
	NSNumber *tmp = [saveData objectForKey:key];
	int n = [tmp intValue];
	return n;
}

void SavedGame::SetIntForKey(int _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithInt:_value];
	[saveData setValue: tmp forKey:key];
	[tmp release];
}

bool SavedGame::GetBoolForKey(NSString *key) const
{
	NSNumber *tmp = [saveData objectForKey:key];
	bool n = [tmp boolValue];
	return n;
}

void SavedGame::SetBoolForKey(bool _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithBool:_value];
	[saveData setValue: tmp forKey:key];
	[tmp release];
}*/