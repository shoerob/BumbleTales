/*
 *  SBRecordChapter.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/5/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "IScrapbookChapter.h"
#include "Graphics.h"
#include "CharacterLevels.h"
#include "CharacterTale.h"
#include "StoryRecords.h"
#include "ArcadeRecords.h"
#include "StoryModeSaveInfo.h"
#include "ArcadeModeSaveInfo.h"

#include <vector>

using namespace std;

class SBRecordChapter : public IScrapbookChapter
	{
	public:
		SBRecordChapter();
		virtual ~SBRecordChapter();
		
		// IScrapbookChapter
		void Update();
		void Render();
		void NextPage();
		void PrevPage();
		ScrapbookChapter GetChapterType();
		
		void LoadFromArcadeSaveInfo(ArcadeModeSaveInfo *saveInfo);
		void LoadFromStorySaveInfo(StoryModeSaveInfo *saveInfo);
		
	private:
		StoryModeSaveInfo *storySaveInfo;
		ArcadeModeSaveInfo *arcadeSaveInfo;
		
		int currPageNum;
		IRenderable *currPage;
		void SetCurrentPage();
		
		CR::Graphics::Sprite *scrapBookTags;
		CR::Graphics::Sprite *pageTags;
	};