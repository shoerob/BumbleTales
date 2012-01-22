/*
 *  StoryModeGameState.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "FSM.h"
#include "Graphics.h"
#include "ResourcePuzzle.h"
#include "StoryModeView.h"
#include "PauseMenuView.h"
#include "StoryModeScoreView.h"
#include "SaveGameManager.h"
#include "ISaveOnTerminate.h"
#include "StoryModeSaveInfo.h"
#include "TrophySaveInfo.h"
#include "OptionsMenuView.h"
#include "HelpMenuView.h"
#include "CharacterBonusView.h"
#include "ShopMenuView.h"
#include "ScrapbookMenuView.h"

class StoryModeGameState : public CR::Utility::IState, public ISaveOnTerminate
{
public:
	StoryModeGameState();
	virtual ~StoryModeGameState();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();
	
	// Event Handlers
	void OnShowMainMenu();
	void OnShowPauseMenu();
	void OnShowOptionsMenu();
	void OnShowHowToPlayMenu();
	void OnShowScrapbookMenu();
	void ShowWinningScrapbookMenu();
	void OnShowScoreScreen(StoryModeScoreData *scoreData);
	void OnShowCharacterBonusMenu();
	void OnShowStore();
	void OnCloseSubview();
	void OnCloseOptionsMenu();
	void OnCloseCharacterBonusMenu();
	void OnCloseStore();
	void OnCloseScoreView();
	void OnChangeCharacter();
	
	// Save
	void OnSaveOnTerminate();
	StoryModeSaveInfo *storyModeSaveInfo;
	SettingsSaveInfo *settingsSaveInfo;
	TrophySaveInfo *trophySaveInfo;
	ArcadeModeSaveInfo *arcadeModeSaveInfo;
	
private:
	StoryModeView *storyModeView;
	IView *subView;
	IView *requestSubview;
	bool m_requestMainMenu;
	bool m_requestCloseSubview;
	bool m_requestWonGame;
};