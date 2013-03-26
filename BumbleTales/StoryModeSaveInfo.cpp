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
#include "AppConfig.h"
#include <scoreloop/scoreloopcore.h>
#include <sstream>
#include "Game.h"

extern Game* game_class;

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
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->SavecoreloopString("level", m_level);
		game_class->SavecoreloopString("stars", m_stars);
		game_class->SavecoreloopString("stars_recieved", m_starsRecieved);
		game_class->SavecoreloopString("bronze_medals", m_bronzeMedals);
		game_class->SavecoreloopString("silver_medals", m_silverMedals);
		game_class->SavecoreloopString("gold_medals", m_goldMedals);
		game_class->SavecoreloopString("total_play_time", m_totalPlayTime);
		game_class->SavecoreloopString("has_won_game", m_hasWonGame);
		game_class->SavecoreloopString("largest_chain", m_largestChain);
		game_class->SavecoreloopString("largest_match", m_laregestMatch);
		game_class->SavecoreloopString("has_opened_store", m_hasOpenedStore);
		game_class->SavecoreloopString("current_character", m_currentCharacter);
		game_class->SavecoreloopString("blocks_cleared_1", m_blocksCleared[0]);
		game_class->SavecoreloopString("blocks_cleared_2", m_blocksCleared[1]);
		game_class->SavecoreloopString("blocks_cleared_3", m_blocksCleared[2]);
		game_class->SavecoreloopString("blocks_cleared_4", m_blocksCleared[3]);
		game_class->SavecoreloopString("blocks_cleared_5", m_blocksCleared[4]);
		game_class->SavecoreloopString("blocks_cleared_6", m_blocksCleared[5]);
		game_class->SavecoreloopString("blocks_cleared_7", m_blocksCleared[6]);
		game_class->SavecoreloopString("blocks_cleared_8", m_blocksCleared[7]);		
	}

	//always save locally as well, in case we don't have a scoreloop connection next run.
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
	
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->SaveScoreLoop();
	}
}

void StoryModeSaveInfo::Load()
{
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->LoadScoreloopValue("level", m_level, 1);
		game_class->LoadScoreloopValue("stars", m_stars, 0);
		game_class->LoadScoreloopValue("stars_recieved", m_starsRecieved, 0);
		game_class->LoadScoreloopValue("bronze_medals", m_bronzeMedals, 0);
		game_class->LoadScoreloopValue("silver_medals", m_silverMedals, 0);
		game_class->LoadScoreloopValue("gold_medals", m_goldMedals, 0);
		game_class->LoadScoreloopValue("total_play_time", m_totalPlayTime, 0);
		game_class->LoadScoreloopValue("has_won_game", m_hasWonGame, false);
		game_class->LoadScoreloopValue("largest_chain", m_largestChain, 0);
		game_class->LoadScoreloopValue("largest_match", m_laregestMatch, 0);
		game_class->LoadScoreloopValue("has_opened_store", m_hasOpenedStore, false);
		game_class->LoadScoreloopValue("current_character", m_currentCharacter, Mayor);
		game_class->LoadScoreloopValue("blocks_cleared_1", m_blocksCleared[0], 0);
		game_class->LoadScoreloopValue("blocks_cleared_2", m_blocksCleared[1], 0);
		game_class->LoadScoreloopValue("blocks_cleared_3", m_blocksCleared[2], 0);
		game_class->LoadScoreloopValue("blocks_cleared_4", m_blocksCleared[3], 0);
		game_class->LoadScoreloopValue("blocks_cleared_5", m_blocksCleared[4], 0);
		game_class->LoadScoreloopValue("blocks_cleared_6", m_blocksCleared[5], 0);
		game_class->LoadScoreloopValue("blocks_cleared_7", m_blocksCleared[6], 0);
		game_class->LoadScoreloopValue("blocks_cleared_8", m_blocksCleared[7], 0);
	}
	else
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