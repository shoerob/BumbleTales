/*
 *  StoryModeSaveInfo.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryModeSaveInfo.h"
#include <assert.h>

StoryModeSaveInfo::StoryModeSaveInfo()
{	
	m_blocksCleared.resize(8);
	Reset();
}

StoryModeSaveInfo::~StoryModeSaveInfo()
{
}

void StoryModeSaveInfo::Save()
{
	FILE *file = NULL;
	file = fopen("story.sav", "wb");
	assert(file);
	
	fwrite(&m_level, 1, sizeof(m_level), file);
	fwrite(&m_stars, 1, sizeof(m_stars), file);
	fwrite(&m_starsRecieved, 1, sizeof(m_starsRecieved), file);
	fwrite(&m_bronzeMedals, 1, sizeof(m_bronzeMedals), file);
	fwrite(&m_silverMedals, 1, sizeof(m_silverMedals), file);
	fwrite(&m_goldMedals, 1, sizeof(m_goldMedals), file);
	fwrite(&m_totalPlayTime, 1, sizeof(m_totalPlayTime), file);
	fwrite(&m_hasWonGame, 1, sizeof(m_hasWonGame), file);
	fwrite(&m_largestChain, 1, sizeof(m_largestChain), file);
	fwrite(&m_laregestMatch, 1, sizeof(m_laregestMatch), file);
	fwrite(&m_hasOpenedStore, 1, sizeof(m_hasOpenedStore), file);
	fwrite(&m_currentCharacter, 1, sizeof(m_currentCharacter), file);
	fwrite(&m_blocksCleared[0], sizeof(int), m_blocksCleared.size(), file);

	m_cLevels.Save(file);
	m_bLevels.Save(file);

	fclose(file);
}

void StoryModeSaveInfo::Load()
{
	FILE *file = NULL;
	file = fopen("story.sav", "rb");
	
	if(!file)
	{
		Reset();
		return;
	}
	
	fread(&m_level, 1, sizeof(m_level), file);
	fread(&m_stars, 1, sizeof(m_stars), file);
	fread(&m_starsRecieved, 1, sizeof(m_starsRecieved), file);
	fread(&m_bronzeMedals, 1, sizeof(m_bronzeMedals), file);
	fread(&m_silverMedals, 1, sizeof(m_silverMedals), file);
	fread(&m_goldMedals, 1, sizeof(m_goldMedals), file);
	fread(&m_totalPlayTime, 1, sizeof(m_totalPlayTime), file);
	fread(&m_hasWonGame, 1, sizeof(m_hasWonGame), file);
	fread(&m_largestChain, 1, sizeof(m_largestChain), file);
	fread(&m_laregestMatch, 1, sizeof(m_laregestMatch), file);
	fread(&m_hasOpenedStore, 1, sizeof(m_hasOpenedStore), file);
	fread(&m_currentCharacter, 1, sizeof(m_currentCharacter), file);
	fread(&m_blocksCleared[0], sizeof(int), m_blocksCleared.size(), file);

	m_cLevels.Load(file);
	m_bLevels.Load(file);

	fclose(file);
}

void StoryModeSaveInfo::Reset()
{
	m_level = 1;
	m_stars = 0;
	m_starsRecieved = 0;
	m_bronzeMedals = 0;
	m_silverMedals = 0;
	m_goldMedals = 0;
	m_totalPlayTime = 0;
	m_hasWonGame = 0;
	m_largestChain = 0;
	m_laregestMatch = 0;
	m_hasOpenedStore = 0;
	m_currentCharacter = Mayor;
	memset(&m_blocksCleared[0], 0, m_blocksCleared.size() * sizeof(int));
	
	m_cLevels.Reset();
	m_bLevels.Reset();
}