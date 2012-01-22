/*
 *  SaveGameManager.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
//#import <UIKit/UIKit.h>
//#import <Foundation/Foundation.h>

#include "StoryModeSaveInfo.h"
#include "ArcadeModeSaveInfo.h"
#include "TrophySaveInfo.h"
#include "SettingsSaveInfo.h"
#include "ISaveOnTerminate.h"

class SaveGameManager
{
public:
	SaveGameManager();
	virtual ~SaveGameManager();
	
	StoryModeSaveInfo *LoadStoryModeSaveInfo();
	void SaveStoryModeSaveInfo(StoryModeSaveInfo *info);
	
	ArcadeModeSaveInfo *LoadArcadeModeSaveInfo();
	void SaveArcadeModeSaveInfo(ArcadeModeSaveInfo *info);
	
	TrophySaveInfo *LoadTrophySaveInfo();
	void SaveTrophySaveInfo(TrophySaveInfo *info);
	
	SettingsSaveInfo *LoadSettingsSaveInfo();
	void SaveSettingsSaveInfo(SettingsSaveInfo *info);
	
	void SaveOnTerminate();
	void SetCurrentSaveOnTerminate(ISaveOnTerminate *saveOnTerminate);
	
	void Reset();
	
private:
	ISaveOnTerminate *m_saveOnTerminate;
};