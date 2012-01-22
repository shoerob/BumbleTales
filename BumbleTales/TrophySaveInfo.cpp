/*
 *  TrophySaveInfo.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "TrophySaveInfo.h"

TrophySaveInfo::TrophySaveInfo()
{
}

TrophySaveInfo::~TrophySaveInfo()
{
}

Trophies *TrophySaveInfo::GetTrophies()
{
	return &m_trophies;//(/*GetDictionaryForKey(@"Trophies")*/);
}

void TrophySaveInfo::SetTrophies(Trophies *trophies)
{
	//SetDictionaryForKey(trophies->GetDictionary(), @"Trophies");
}

void TrophySaveInfo::Save()
{
	m_trophies.Save();
}

void TrophySaveInfo::Load()
{
	m_trophies.Load();
}

void TrophySaveInfo::Reset()
{
	m_trophies.Reset();
}

/*
NSString* TrophySaveInfo::GetDefaultsFilePath()
{
	return [[NSBundle mainBundle] pathForResource:@"TrophySaveInfoDefaults" ofType:@"plist"];
}

NSString* TrophySaveInfo::GetSaveFilePath()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	return [documentsDirectory stringByAppendingPathComponent:@"TrophySaveInfo.plist"];
}*/