/*
 *  ArcadeModeSaveInfo.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ArcadeModeSaveInfo.h"
#include <stdio.h>
#include <assert.h>

ArcadeModeSaveInfo::ArcadeModeSaveInfo()
{
	m_blocksCleared.resize(8);
	m_highScores.resize(5);
	m_highScoreLevels.resize(5);

}

ArcadeModeSaveInfo::~ArcadeModeSaveInfo()
{
}

void ArcadeModeSaveInfo::Save()
{
	FILE *file = NULL;
	file = fopen("arcade.sav", "wb");
	assert(file);
	
	fwrite(&m_largetsChain, 1, sizeof(m_largetsChain), file);
	fwrite(&m_largestMatch, 1, sizeof(m_largestMatch), file);
	fwrite(&m_maxPointsOnOneMove, 1, sizeof(m_maxPointsOnOneMove), file);
	fwrite(&m_maxMovesInSession, 1, sizeof(m_maxMovesInSession), file);
	fwrite(&m_longestSessionTime, 1, sizeof(m_longestSessionTime), file);
	fwrite(&m_totalPlayTime, 1, sizeof(m_totalPlayTime), file);
	fwrite(&m_blocksCleared[0], sizeof(int), m_blocksCleared.size(), file);
	fwrite(&m_highScores[0], sizeof(int), m_highScores.size(), file);
	fwrite(&m_highScoreLevels[0], sizeof(int), m_highScoreLevels.size(), file);
	
	fclose(file);
}

void ArcadeModeSaveInfo::Load()
{
	FILE *file = NULL;
	file = fopen("arcade.sav", "rb");
	if(!file)
	{
		Reset();
		return;
	}
	
	fread(&m_largetsChain, 1, sizeof(m_largetsChain), file);
	fread(&m_largestMatch, 1, sizeof(m_largestMatch), file);
	fread(&m_maxPointsOnOneMove, 1, sizeof(m_maxPointsOnOneMove), file);
	fread(&m_maxMovesInSession, 1, sizeof(m_maxMovesInSession), file);
	fread(&m_longestSessionTime, 1, sizeof(m_longestSessionTime), file);
	fread(&m_totalPlayTime, 1, sizeof(m_totalPlayTime), file);
	fread(&m_blocksCleared[0], sizeof(int), m_blocksCleared.size(), file);
	fread(&m_highScores[0], sizeof(int), m_highScores.size(), file);
	fread(&m_highScoreLevels[0], sizeof(int), m_highScoreLevels.size(), file);
	
	fclose(file);
}

void ArcadeModeSaveInfo::Reset()
{
	m_largetsChain = 0;
	m_largestMatch = 0;
	m_maxPointsOnOneMove = 0;
	m_maxMovesInSession = 0;
	m_maxPowerUsedInSession = 0;
	m_longestSessionTime = 0;
	m_totalPlayTime = 0;

	memset(&m_blocksCleared[0], 0, m_blocksCleared.size() * sizeof(int));
	memset(&m_highScores[0], 0, m_highScores.size() * sizeof(int));
	memset(&m_highScoreLevels[0], 0, m_highScoreLevels.size() * sizeof(int));
}