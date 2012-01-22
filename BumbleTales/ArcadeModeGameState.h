/*
 *  ArcadeModeGameState.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "FSM.h"
#include "Graphics.h"
#include "ResourcePuzzle.h"
#include "ArcadeModeView.h"
#include "PauseMenuView.h"
#include "ArcadeModeScoreView.h"
#include "SaveGameManager.h"
#include "ISaveOnTerminate.h"
#include "StoryModeSaveInfo.h"
#include "OptionsMenuView.h"
#include "HelpMenuView.h"
#include "CharacterBonusView.h"
#include "ScrapbookMenuView.h"
class ArcadeModeGameState: public CR::Utility::IState, public ISaveOnTerminate
{
public:
	ArcadeModeGameState();
	virtual ~ArcadeModeGameState();
	
	//IState
	bool Begin();
	void End();
	int Process();
	
	// Event Handlers
	void OnShowMainMenu();
	void OnShowPauseMenu();
	void OnShowOptionsMenu();
	void OnShowHowToPlayMenu();
	void OnShowScrapbookMenu();
	void OnShowScoreScreen(ArcadeModeScoreData *scoreData);
	void OnShowCharacterBonusMenu();
	void OnCloseSubview();
	void OnCloseOptionsMenu();
	void OnCloseCharacterBonusMenu();
	//void OnCloseStore();
	void OnStartNewGame();
	void OnChangeCharacter();
	
	// Save
	void OnSaveOnTerminate();
	StoryModeSaveInfo *storyModeSaveInfo;
	ArcadeModeSaveInfo *arcadeModeSaveInfo;
	SettingsSaveInfo *settingsSaveInfo;
	TrophySaveInfo *trophySaveInfo;
	
private:
	ArcadeModeView *arcadeModeView;
	IView *subView;
	IView *requestSubview;
	bool m_requestMainMenu;
	bool m_requestCloseSubview;
};