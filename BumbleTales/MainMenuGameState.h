/*
 *  MainMenuGameState.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "FSM.h"
#include "HomeMenuScreen.h"
#include "OptionsMenuScreen.h"
#include "HelpMenuScreen.h"
#include "MoreGamesMenuScreen.h"
#include "ScrapbookMenuScreen.h"
#include "SplashScreenMenu.h"

#define SPLASH_MENU_STATE 0
#define HOME_MENU_STATE 1
#define OPTIONS_MENU_STATE 2
#define HELP_MENU_STATE 3
#define MORE_GAMES_MENU_STATE 4
#define SCRAPBOOK_MENU_STATE 5

class MainMenuGameState : public CR::Utility::IState
{
public:
	MainMenuGameState();
	virtual ~MainMenuGameState();
	
	void StartStoryMode();
	void StartArcadeMode();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();

private:
	CR::Utility::FSM stateMachine;
	bool m_requestStartStoryMode;
	bool m_requestStartArcadeMode;
	//bool m_requestShowOptionsMenu;
	bool m_showSplashScreen;
};