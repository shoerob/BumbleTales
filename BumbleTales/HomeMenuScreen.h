/*
 *  HomeMenuScreen.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "FSM.h"
#include "Input_Engine.h"
#include "HomeMenuView.h"

class MainMenuGameState;

class HomeMenuScreen : public CR::Utility::IState
{
public:
	HomeMenuScreen(MainMenuGameState *mainMenuGameState);
	virtual ~HomeMenuScreen();
	
	void OnStartStoryMode();
	void OnStartArcadeMode();
	void OnShowOptionsMenu();
	void OnShowHelpMenu();
	void OnShowMoreGamesMenu();
	void OnShowScrapbookMenu();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();
	
private:
	HomeMenuView *view;
	MainMenuGameState *mainMenuGameState;
	
	bool m_requestShowOptionsMenu;
	bool m_requestShowHelpMenu;
	bool m_requestShowMoreGamesMenu;
	bool m_requestShowScrapbookMenu;
};