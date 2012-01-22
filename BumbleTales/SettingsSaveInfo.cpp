/*
 *  SettingsSaveInfo.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SettingsSaveInfo.h"
#include <assert.h>

SettingsSaveInfo::SettingsSaveInfo() : m_file(NULL), m_hintsOn(true), m_soundOn(true), m_musicOn(true)
{
}

SettingsSaveInfo::~SettingsSaveInfo()
{
}

void SettingsSaveInfo::Save()
{
	FILE *file = NULL;
	file = fopen("settings.sav", "wb");
	
	if(!file)
	{
		Reset();
		return;
	}

	fwrite(&m_hintsOn, 1, sizeof(m_hintsOn), file);
	fwrite(&m_soundOn, 1, sizeof(m_soundOn), file);
	fwrite(&m_musicOn, 1, sizeof(m_musicOn), file);

	fclose(file);
}

void SettingsSaveInfo::Load()
{
	FILE *file = NULL;
	file = fopen("settings.sav", "rb");
	if(file)
	{
		fread(&m_hintsOn, 1, sizeof(m_hintsOn), file);
		fread(&m_soundOn, 1, sizeof(m_soundOn), file);
		fread(&m_musicOn, 1, sizeof(m_musicOn), file);
	}
	else
		Reset();
	
	fclose(file);
}

void SettingsSaveInfo::Reset()
{
	m_hintsOn = true;
	m_soundOn = true;
	m_musicOn = true;
}