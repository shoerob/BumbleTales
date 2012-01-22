/*
 *  MoreGamesMenuScreen.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "FSM.h"
#include "Input_Engine.h"
#include "MoreGamesMenuView.h"

class MainMenuGameState;

class MoreGamesMenuScreen : public CR::Utility::IState
{
public:
	MoreGamesMenuScreen(MainMenuGameState *mainMenuGameState);
	virtual ~MoreGamesMenuScreen();
	
	void OnExitMoreGamesMenu();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();
	
private:
	MoreGamesMenuView *view;
	MainMenuGameState *mainMenuGameState;
	bool m_requestShowHomeMenu;
};