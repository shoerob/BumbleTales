/*
 *  BuildingLevels.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/29/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "BuildingLevels.h"
#include <memory.h>
#include "AppConfig.h"
#include "Game.h"

extern Game* game_class;

BuildingLevels::BuildingLevels(/*NSMutableDictionary *buildingLevels*/)
{
	Reset();
}

BuildingLevels::~BuildingLevels()
{
}

void BuildingLevels::Save(FILE *_file)
{
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->SavecoreloopString("blevel_1", m_levels[0]);
		game_class->SavecoreloopString("blevel_2", m_levels[1]);
		game_class->SavecoreloopString("blevel_3", m_levels[2]);
		game_class->SavecoreloopString("blevel_4", m_levels[3]);
		game_class->SavecoreloopString("blevel_5", m_levels[4]);
		game_class->SavecoreloopString("blevel_6", m_levels[5]);
		game_class->SavecoreloopString("blevel_7", m_levels[6]);
	}

	fwrite(m_levels, 1, sizeof(m_levels), _file);
}

void BuildingLevels::Load(FILE *_file)
{
	if(AppConfig::Instance().UseScoreloop())
	{
		game_class->LoadScoreloopValue("blevel_1", m_levels[0], 0);
		game_class->LoadScoreloopValue("blevel_2", m_levels[1], 0);
		game_class->LoadScoreloopValue("blevel_3", m_levels[2], 0);
		game_class->LoadScoreloopValue("blevel_4", m_levels[3], 0);
		game_class->LoadScoreloopValue("blevel_5", m_levels[4], 0);
		game_class->LoadScoreloopValue("blevel_6", m_levels[5], 0);
		game_class->LoadScoreloopValue("blevel_7", m_levels[6], 0);
	}
	else
	{
		fread(m_levels, 1, sizeof(m_levels), _file);
	}
}

void BuildingLevels::Reset()
{
	memset(m_levels, 0, sizeof(m_levels));
}
