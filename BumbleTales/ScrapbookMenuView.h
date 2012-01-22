/*
 *  ScrapbookMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Input_Engine.h"
#include "Graphics.h"
#include "IView.h"
#include "IScrapbookChapter.h"
#include "SBCharacterChapter.h"
#include "SBTrophyChapter.h"
#include "SBRecordChapter.h"
#include "StoryModeSaveInfo.h"
#include "ArcadeModeSaveInfo.h"
#include "TrophySaveInfo.h"
#include "BuildingLevels.h"
#include "CharacterLevels.h"

class ScrapbookMenuView : public IView
{
public:
	ScrapbookMenuView(bool wonGame = false);
	virtual ~ScrapbookMenuView();
	
	void Update();
	void Render();
	
	void OnExitButtonClicked();
	void OnPrevButtonClicked();
	void OnNextButtonClicked();
	void OnCharactersButtonClicked();
	void OnRecordsButtonClicked();
	void OnTrophiesButtonClicked();
	
	
	void LoadFromArcadeSaveInfo(ArcadeModeSaveInfo *saveInfo);
	void LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo);
	void LoadFromSaveInfo(StoryModeSaveInfo *saveInfo);
	
	Event OnExitClicked;
	
	// Input_Controller
	/*void TouchesBegan(UIView *view, NSSet *touches);
	void TouchesMoved(UIView *view, NSSet *touches);
	void TouchesEnded(UIView *view, NSSet *touches);
	void TouchesCancelled(UIView *view, NSSet *touches);*/
	
private:
	IScrapbookChapter *m_currChapter;
	CR::Graphics::Sprite *baseSprite;
	CR::Graphics::Sprite *rimSprite;
	
	Input_Button *nextButton;
	Input_Button *prevButton;
	Input_Button *exitButton;
	
	Input_Button *charactersButton;
	Input_Button *recordsButton;
	Input_Button *trophiesButton;
	
	CharacterLevels *characterLevels;
	BuildingLevels *buildingLevels;
	
	StoryModeSaveInfo *storyModeSaveInfo;
	ArcadeModeSaveInfo *arcadeModeSaveInfo;
	TrophySaveInfo *trophySaveInfo;
	
	//void UnregisterInput();
};