/*
 *  SaveGameManager.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SaveGameManager.h"

SaveGameManager::SaveGameManager()
{
	m_saveOnTerminate = NULL;
}

SaveGameManager::~SaveGameManager()
{
}

StoryModeSaveInfo *SaveGameManager::LoadStoryModeSaveInfo()
{
	StoryModeSaveInfo *info = new StoryModeSaveInfo();
	info->Load();
	return info;
}

void SaveGameManager::SaveStoryModeSaveInfo(StoryModeSaveInfo *info)
{
	info->Save();
}

ArcadeModeSaveInfo *SaveGameManager::LoadArcadeModeSaveInfo()
{
	ArcadeModeSaveInfo *info = new ArcadeModeSaveInfo();
	info->Load();
	return info;
}

void SaveGameManager::SaveArcadeModeSaveInfo(ArcadeModeSaveInfo *info)
{
	info->Save();
}

TrophySaveInfo *SaveGameManager::LoadTrophySaveInfo()
{
	TrophySaveInfo *info = new TrophySaveInfo();
	info->Load();
	return info;
}

void SaveGameManager::SaveTrophySaveInfo(TrophySaveInfo *info)
{
	info->Save();
}

SettingsSaveInfo *SaveGameManager::LoadSettingsSaveInfo()
{
	SettingsSaveInfo *info = new SettingsSaveInfo();
	info->Load();
	return info;
}

void SaveGameManager::SaveSettingsSaveInfo(SettingsSaveInfo *info)
{
	info->Save();
}

void SaveGameManager::SaveOnTerminate()
{
	if (m_saveOnTerminate != NULL)
		m_saveOnTerminate->OnSaveOnTerminate();
}

void SaveGameManager::SetCurrentSaveOnTerminate(ISaveOnTerminate *saveOnTerminate)
{
	m_saveOnTerminate = saveOnTerminate;
}

void SaveGameManager::Reset()
{
	StoryModeSaveInfo* storySave = LoadStoryModeSaveInfo();
	storySave->Reset();
	storySave->Save();

	ArcadeModeSaveInfo* arcadeSave = LoadArcadeModeSaveInfo();
	arcadeSave->Reset();
	arcadeSave->Save();

	SettingsSaveInfo* settingsSave = LoadSettingsSaveInfo();
	settingsSave->Reset();
	settingsSave->Save();

	TrophySaveInfo* trophySave = LoadTrophySaveInfo();
	trophySave->Reset();
	trophySave->Save();

}