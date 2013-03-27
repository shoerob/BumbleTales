/*
 *  SBTrophyChapter.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/5/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SBTrophyChapter.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

SBTrophyChapter::SBTrophyChapter()
{
	currPageNum = 0;

	bgSprite = graphics_engine->CreateSprite1(false, 300);
	bgSprite->SetImage(CR::AssetList::Scrapbook_Trophy_Base_1);
	bgSprite->SetDesignSize(320, 347);
	bgSprite->SetPositionAbsolute(160, 250);
	
	trophyName = graphics_engine->CreateSprite1(true, 200);
	trophyName->SetImage(CR::AssetList::Scrapbook_Trophy_Names);
	trophyName->SetDesignSize(289, 186);
	trophyName->SetPositionAbsolute(166, 208);
	
	scrapBookTags = graphics_engine->CreateSprite1(false, 199);
	scrapBookTags->SetImage(CR::AssetList::Scrapbook_Tags_1);
	scrapBookTags->SetDesignSize(193, 23);
	scrapBookTags->SetFrameSet(16);
	scrapBookTags->SetPositionAbsolute(104, 60);
	
	pageTags = graphics_engine->CreateSprite1(false, 199);
	pageTags->SetImage(CR::AssetList::Scrapbook_Tags_2);
	pageTags->SetDesignSize(68, 16);
	pageTags->SetPositionAbsolute(275, 60);
	
	trophyInfo = graphics_engine->CreateSprite1(true, 200);
	trophyInfo->SetImage(CR::AssetList::Scrapbook_Trophy_Info);
	trophyInfo->SetDesignSize(253, 59);
	trophyInfo->SetPositionAbsolute(160, 373);
	
	selectedTrophy = -1;
	isTrophyNameVisible = false;
}

SBTrophyChapter::~SBTrophyChapter()
{
	bgSprite->Release();
	trophyName->Release();
	pageTags->Release();
	trophyInfo->Release();
	scrapBookTags->Release();

	for (int i = 0; i < trophyButtons.size(); i++)
		delete trophyButtons[i];
}

void SBTrophyChapter::Update()
{
	trophyName->SetFrame(currPageNum);
	pageTags->SetFrameSet(3 + currPageNum);
}

void SBTrophyChapter::Render()
{
	bgSprite->Render();
	
	if (isTrophyNameVisible)
		trophyInfo->Render();
	
	scrapBookTags->Render();
	trophyName->Render();
	
	pageTags->Render();
	
	//if (selectedTrophy != -1)
	//	trophyInfo->Render();

	int tOffset = currPageNum * 12;
	for (int i = tOffset; i < tOffset + 12; i++)
		trophyButtons[i]->Render();
}

void SBTrophyChapter::NextPage()
{
	currPageNum++;
	if (currPageNum > 2)
		currPageNum = 0;
	
	isTrophyNameVisible = false;
}

void SBTrophyChapter::PrevPage()
{
	currPageNum--;
	if (currPageNum < 0)
		currPageNum = 2;
	
	isTrophyNameVisible = false;
}

ScrapbookChapter SBTrophyChapter::GetChapterType()
{
	return TrophiesChapter;
}

void SBTrophyChapter::LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo)
{
	trophySaveInfo = saveInfo;
	trophies = trophySaveInfo->GetTrophies();
	SetupTrophies();
}

void SBTrophyChapter::OnTrophyPressed(TrophyName tName)
{
	isTrophyNameVisible = true;
	trophyInfo->SetFrame((int)tName);
}

void SBTrophyChapter::SetupTrophies()
{
	// Create the trophy buttons
	for (int i = 0; i < 36; i++)
	{
		TrophyButton *tButton = new TrophyButton((TrophyName)i, 200);
		tButton->SetHasTrophy(trophies->GetTrophy((TrophyName)i));
		//buildingButtons[i]->OnDown += Delegate1<BuildingHUD, int>(this,&BuildingHUD::OnButtonDown);
		tButton->OnClicked += Delegate1<SBTrophyChapter, TrophyName>(this, &SBTrophyChapter::OnTrophyPressed);
		trophyButtons.push_back(tButton);
	}

	int tOffset = 0;
	int xOffset = 48;
	int yOffset = 126;
	int iX = 0;
	int iY = 0;
	
	for (int i = 0; i < 3; i++)
	{
		tOffset = i * 12;
		iX = 0; iY = 0;
		for (int j = tOffset; j < tOffset + 12; j++)
		{
			trophyButtons[j]->SetPosition(iX * 77 + xOffset, iY * 81 + yOffset);
			
			iX++;
			if (iX > 3)
			{
				iX = 0;
				iY++;
			}
		}
	}
}

void SBTrophyChapter::TouchesBeganImpl(Touch &_touches)
{
	int tOffset = currPageNum * 12;
	for (int i = tOffset; i < tOffset + 12; i++)
	{
		trophyButtons[i]->TouchesBeganImpl(_touches);
	}
}

/*
void SBTrophyChapter::TouchesBeganImpl(UIView *view, NSSet *touches)
{
	int tOffset = currPageNum * 12;
	for (int i = tOffset; i < tOffset + 12; i++)
	{
		trophyButtons[i]->TouchesBeganImpl(view, touches);
	}
}

void SBTrophyChapter::TouchesMovedImpl(UIView *view, NSSet *touches)
{
	int tOffset = currPageNum * 12;
	for (int i = tOffset; i < tOffset + 12; i++)
	{
		trophyButtons[i]->TouchesMovedImpl(view, touches);
	}
}

void SBTrophyChapter::TouchesEndedImpl(UIView *view, NSSet *touches)
{
	int tOffset = currPageNum * 12;
	for (int i = tOffset; i < tOffset + 12; i++)
	{
		trophyButtons[i]->TouchesEndedImpl(view, touches);
	}
}

void SBTrophyChapter::TouchesCancelledImpl(UIView *view, NSSet *touches)
{
	int tOffset = currPageNum * 12;
	for (int i = tOffset; i < tOffset + 12; i++)
	{
		trophyButtons[i]->TouchesCancelledImpl(view, touches);
	}
}*/