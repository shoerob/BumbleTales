/*
 *  ScrapbookMenuScreen.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "FSM.h"
#include "Input_Engine.h"
#include "ScrapbookMenuView.h"
#include "StoryModeSaveInfo.h"

class MainMenuGameState;


class ScrapbookMenuScreen : public CR::Utility::IState
{
public:
	ScrapbookMenuScreen(MainMenuGameState *mainMenuGameState);
	virtual ~ScrapbookMenuScreen();
	
	void OnExitScrapbookMenu();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();
	
private:
	ScrapbookMenuView *view;
	MainMenuGameState *mainMenuGameState;
	bool m_requestShowHomeMenu;
	StoryModeSaveInfo *saveInfo;
	ArcadeModeSaveInfo *arcadeModeSaveInfo;
	TrophySaveInfo *trophySaveInfo;
};