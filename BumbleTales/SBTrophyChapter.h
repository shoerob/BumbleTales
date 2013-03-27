/*
 *  SBTrophyChapter.h
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
#include "TrophySaveInfo.h"
#include "TrophyButton.h"
#include "Input_Object.h"
#include <vector>
using namespace std;

class SBTrophyChapter : public IScrapbookChapter
{
public:
	SBTrophyChapter();
	virtual ~SBTrophyChapter();
	
	// IScrapbookChapter
	void Update();
	void Render();
	void NextPage();
	void PrevPage();
	ScrapbookChapter GetChapterType();

	void LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo);

	// Input_Object
	virtual void TouchesBeganImpl(Touch &_touches);

	void Reset(){};
	void FreeResources(){};
	
	void OnTrophyPressed(TrophyName tName);
private:
	int currPageNum;
	TrophySaveInfo *trophySaveInfo;
	CR::Graphics::Sprite *bgSprite;
	//CR::Graphics::Sprite *trophyIcons[];
	//vector<CR::Graphics::Sprite*> trophyIcons;
	vector<TrophyButton*> trophyButtons;
	bool isTrophyNameVisible;
	CR::Graphics::Sprite *trophyName;
	CR::Graphics::Sprite *pageTags;
	CR::Graphics::Sprite *trophyInfo;
	CR::Graphics::Sprite *scrapBookTags;
	Trophies *trophies;
	int selectedTrophy;
	
	void SetupTrophies();
	//void CreateTrophyIcons();
	//void DestroyTrophyIcons();
	//void SetupPageTrophyItems();
};