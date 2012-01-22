/*
 *  TrophySaveInfo.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "SaveInfo.h"
//#import <UIKit/UIKit.h>
#include "BuildingLevels.h"
#include "CharacterLevels.h"
#include "Trophies.h"

class TrophySaveInfo : public SaveInfo
	{
	public:
		TrophySaveInfo();
		virtual ~TrophySaveInfo();
		
		Trophies *GetTrophies();
		void SetTrophies(Trophies *trophies);
		
		virtual void Save();
		virtual void Load();
		virtual void Reset();
	private:
		Trophies m_trophies;
		/*NSString* GetDefaultsFilePath();
		NSString* GetSaveFilePath();*/
	};