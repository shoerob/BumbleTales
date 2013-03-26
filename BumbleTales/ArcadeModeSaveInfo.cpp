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
#include "AppConfig.h"
#include "Game.h"

extern Game* game_class;

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
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->SavecoreloopString("alargest_chain", m_largetsChain);
		game_class->SavecoreloopString("alargest_match", m_largestMatch);
		game_class->SavecoreloopString("amax_points_one_move", m_maxPointsOnOneMove);
		game_class->SavecoreloopString("amax_moves_session", m_maxMovesInSession);
		game_class->SavecoreloopString("alongest_session_time", m_longestSessionTime);
		game_class->SavecoreloopString("atotal_play_time", m_totalPlayTime);
		game_class->SavecoreloopString("ablocks_cleared_1", m_blocksCleared[0]);
		game_class->SavecoreloopString("ablocks_cleared_2", m_blocksCleared[1]);
		game_class->SavecoreloopString("ablocks_cleared_3", m_blocksCleared[2]);
		game_class->SavecoreloopString("ablocks_cleared_4", m_blocksCleared[3]);
		game_class->SavecoreloopString("ablocks_cleared_5", m_blocksCleared[4]);
		game_class->SavecoreloopString("ablocks_cleared_6", m_blocksCleared[5]);
		game_class->SavecoreloopString("ablocks_cleared_7", m_blocksCleared[6]);
		game_class->SavecoreloopString("ablocks_cleared_8", m_blocksCleared[7]);
		game_class->SavecoreloopString("ahigh_scores_1", m_highScores[0]);
		game_class->SavecoreloopString("ahigh_scores_2", m_highScores[1]);
		game_class->SavecoreloopString("ahigh_scores_3", m_highScores[2]);
		game_class->SavecoreloopString("ahigh_scores_4", m_highScores[3]);
		game_class->SavecoreloopString("ahigh_scores_5", m_highScores[4]);
		game_class->SavecoreloopString("ahigh_scores_levels_1", m_highScoreLevels[0]);
		game_class->SavecoreloopString("ahigh_scores_levels_2", m_highScoreLevels[1]);
		game_class->SavecoreloopString("ahigh_scores_levels_3", m_highScoreLevels[2]);
		game_class->SavecoreloopString("ahigh_scores_levels_4", m_highScoreLevels[3]);
		game_class->SavecoreloopString("ahigh_scores_levels_5", m_highScoreLevels[4]);
	}

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
	
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->SaveScoreLoop();
	}
}

void ArcadeModeSaveInfo::Load()
{
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->LoadScoreloopValue("alargest_chain", m_largetsChain, 0);
		game_class->LoadScoreloopValue("alargest_match", m_largestMatch, 0);
		game_class->LoadScoreloopValue("amax_points_one_move", m_maxPointsOnOneMove, 0);
		game_class->LoadScoreloopValue("amax_moves_session", m_maxMovesInSession, 0);
		game_class->LoadScoreloopValue("alongest_session_time", m_longestSessionTime, 0);
		game_class->LoadScoreloopValue("atotal_play_time", m_totalPlayTime, 0);
		game_class->LoadScoreloopValue("ablocks_cleared_1", m_blocksCleared[0], 0);
		game_class->LoadScoreloopValue("ablocks_cleared_2", m_blocksCleared[1], 0);
		game_class->LoadScoreloopValue("ablocks_cleared_3", m_blocksCleared[2], 0);
		game_class->LoadScoreloopValue("ablocks_cleared_4", m_blocksCleared[3], 0);
		game_class->LoadScoreloopValue("ablocks_cleared_5", m_blocksCleared[4], 0);
		game_class->LoadScoreloopValue("ablocks_cleared_6", m_blocksCleared[5], 0);
		game_class->LoadScoreloopValue("ablocks_cleared_7", m_blocksCleared[6], 0);
		game_class->LoadScoreloopValue("ablocks_cleared_8", m_blocksCleared[7], 0);
		game_class->LoadScoreloopValue("ahigh_scores_1", m_highScores[0], 0);
		game_class->LoadScoreloopValue("ahigh_scores_2", m_highScores[1], 0);
		game_class->LoadScoreloopValue("ahigh_scores_3", m_highScores[2], 0);
		game_class->LoadScoreloopValue("ahigh_scores_4", m_highScores[3], 0);
		game_class->LoadScoreloopValue("ahigh_scores_5", m_highScores[4], 0);
		game_class->LoadScoreloopValue("ahigh_scores_levels_1", m_highScoreLevels[0], 0);
		game_class->LoadScoreloopValue("ahigh_scores_levels_2", m_highScoreLevels[1], 0);
		game_class->LoadScoreloopValue("ahigh_scores_levels_3", m_highScoreLevels[2], 0);
		game_class->LoadScoreloopValue("ahigh_scores_levels_4", m_highScoreLevels[3], 0);
		game_class->LoadScoreloopValue("ahigh_scores_levels_5", m_highScoreLevels[4], 0);
	}
	else
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