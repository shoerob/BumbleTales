/*
 *  CharacterLevels.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CharacterLevels.h"
#include <string>

CharacterLevels::CharacterLevels(/*NSMutableDictionary *characterLevels*/)
{
	Reset();
	//m_characterLevels = characterLevels;
}

CharacterLevels::~CharacterLevels()
{
	//Reset();
	//[m_characterLevels release];
}

void CharacterLevels::Save(FILE *_file)
{
	fwrite(m_levels, 1, sizeof(m_levels), _file);
}

void CharacterLevels::Load(FILE *_file)
{
	fread(m_levels, 1, sizeof(m_levels), _file);
}

void CharacterLevels::Reset()
{
	memset(m_levels, 0, sizeof(m_levels));
}
