/*
 *  SBRecordChapter.cpp
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/5/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SBRecordChapter.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

SBRecordChapter::SBRecordChapter()
{
	currPageNum = 0;
	currPage = NULL;
	
	pageTags = graphics_engine->CreateSprite1(false, 199);
	pageTags->SetImage(CR::AssetList::Scrapbook_Tags_2);
	pageTags->SetPositionAbsolute(275, 60);
	
	scrapBookTags = graphics_engine->CreateSprite1(false, 199);
	scrapBookTags->SetImage(CR::AssetList::Scrapbook_Tags_1);
	scrapBookTags->SetFrameSet(16);
	scrapBookTags->SetPositionAbsolute(104, 60);
	
	//SetCurrentPage();
}

SBRecordChapter::~SBRecordChapter()
{
	if (currPage != NULL)
		delete currPage;
	
	pageTags->Release();
	scrapBookTags->Release();
}

void SBRecordChapter::Update()
{
	currPage->Update();
	pageTags->SetFrameSet(7 + currPageNum);
	scrapBookTags->SetFrameSet(13 + currPageNum);
}

void SBRecordChapter::Render()
{
	currPage->Render();
	pageTags->Render();
	scrapBookTags->Render();
}

void SBRecordChapter::NextPage()
{
	currPageNum++;
	if (currPageNum > 1)
		currPageNum = 0;
	
	SetCurrentPage();
}

void SBRecordChapter::PrevPage()
{
	currPageNum--;
	if (currPageNum < 0)
		currPageNum = 1;
	
	SetCurrentPage();
}

ScrapbookChapter SBRecordChapter::GetChapterType()
{
	return RecordsChapter;
}

void SBRecordChapter::SetCurrentPage()
{
	if (currPage != NULL)
		delete currPage;
	
	switch (currPageNum)
	{
		case 0: // Story Records
			currPage = new StoryRecords();
			currPage->SetPosition(160, 240);
			((StoryRecords *)currPage)->LoadFromStorySaveInfo(storySaveInfo);
			break;
		case 1: // Arcade Records
			currPage = new ArcadeRecords();
			currPage->SetPosition(160, 240);
			((ArcadeRecords *)currPage)->LoadFromArcadeSaveInfo(arcadeSaveInfo);
			break;
		default:
			break;
	}
}

void SBRecordChapter::LoadFromArcadeSaveInfo(ArcadeModeSaveInfo *saveInfo)
{
	arcadeSaveInfo = saveInfo;
}

void SBRecordChapter::LoadFromStorySaveInfo(StoryModeSaveInfo *saveInfo)
{
	storySaveInfo = saveInfo;
	SetCurrentPage();
}