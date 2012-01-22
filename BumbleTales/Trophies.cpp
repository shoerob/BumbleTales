/*
 *  Trophies.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "Trophies.h"
#include <memory.h>
#include <stdio.h>
#include <assert.h>

Trophies::Trophies(/*NSMutableDictionary *trophies*/)
{
	Reset();
	//m_trophies = trophies;
}

Trophies::~Trophies()
{
	//[m_trophies release];
}

void Trophies::Reset()
{
	memset(m_trophies, 0, sizeof(m_trophies)*sizeof(bool));
}

void Trophies::Load()
{
	FILE *file = NULL;
	file = fopen("trophies.sav", "rb");
	if(file)
	{
		fread(m_trophies, 1, sizeof(m_trophies), file);
		fclose(file);
	}
	else
		Reset();	
}

void Trophies::Save()
{
	FILE *file = NULL;
	file = fopen("trophies.sav", "wb");
	assert(file);

	fwrite(m_trophies, 1, sizeof(m_trophies), file);

	fclose(file);
}

bool Trophies::GetTrophy(TrophyName trophyName) const
{
	return m_trophies[trophyName];//GetBoolForKey(TrophyNameStrings[(int)trophyName]);
}

void Trophies::SetTrophy(TrophyName trophyName, bool _value)
{
	m_trophies[trophyName] = _value;
	//SetBoolForKey(_value, TrophyNameStrings[(int)trophyName]);
}

/*
NSMutableDictionary *Trophies::GetDictionary()
{
	return m_trophies;
}

bool Trophies::GetBoolForKey(NSString *key) const
{
	NSNumber *tmp = [m_trophies objectForKey:key];
	bool n = [tmp boolValue];
	return n;
}

void Trophies::SetBoolForKey(bool _value, NSString *key)
{
	NSNumber *tmp = [[NSNumber alloc] initWithBool:_value];
	[m_trophies setValue: tmp forKey:key];
	[tmp release];
}*/