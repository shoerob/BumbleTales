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
#include "AppConfig.h"
#include "Game.h"

extern Game* game_class;

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
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->SavecoreloopString("clevel_1", m_levels[0]);
		game_class->SavecoreloopString("clevel_2", m_levels[1]);
		game_class->SavecoreloopString("clevel_3", m_levels[2]);
		game_class->SavecoreloopString("clevel_4", m_levels[3]);
		game_class->SavecoreloopString("clevel_5", m_levels[4]);
		game_class->SavecoreloopString("clevel_6", m_levels[5]);
		game_class->SavecoreloopString("clevel_7", m_levels[6]);
		game_class->SavecoreloopString("clevel_8", m_levels[7]);
		game_class->SavecoreloopString("clevel_9", m_levels[8]);
		game_class->SavecoreloopString("clevel_10", m_levels[9]);
		game_class->SavecoreloopString("clevel_11", m_levels[10]);
		game_class->SavecoreloopString("clevel_12", m_levels[11]);
		game_class->SavecoreloopString("clevel_13", m_levels[12]);
		game_class->SavecoreloopString("clevel_14", m_levels[13]);
	}
	fwrite(m_levels, 1, sizeof(m_levels), _file);
}

void CharacterLevels::Load(FILE *_file)
{
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->LoadScoreloopValue("clevel_1", m_levels[0], 0);
		game_class->LoadScoreloopValue("clevel_2", m_levels[1], 0);
		game_class->LoadScoreloopValue("clevel_3", m_levels[2], 0);
		game_class->LoadScoreloopValue("clevel_4", m_levels[3], 0);
		game_class->LoadScoreloopValue("clevel_5", m_levels[4], 0);
		game_class->LoadScoreloopValue("clevel_6", m_levels[5], 0);
		game_class->LoadScoreloopValue("clevel_7", m_levels[6], 0);
		game_class->LoadScoreloopValue("clevel_8", m_levels[7], 0);
		game_class->LoadScoreloopValue("clevel_9", m_levels[8], 0);
		game_class->LoadScoreloopValue("clevel_10", m_levels[9], 0);
		game_class->LoadScoreloopValue("clevel_11", m_levels[10], 0);
		game_class->LoadScoreloopValue("clevel_12", m_levels[11], 0);
		game_class->LoadScoreloopValue("clevel_13", m_levels[12], 0);
		game_class->LoadScoreloopValue("clevel_14", m_levels[13], 0);
	}
	else
	{
		fread(m_levels, 1, sizeof(m_levels), _file);
	}
}

void CharacterLevels::Reset()
{
	memset(m_levels, 0, sizeof(m_levels));
}
