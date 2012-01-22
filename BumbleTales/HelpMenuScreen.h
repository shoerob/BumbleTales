/*
 *  HelpMenuScreen.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "FSM.h"
#include "Input_Engine.h"
#include "HelpMenuView.h"

class MainMenuGameState;

class HelpMenuScreen : public CR::Utility::IState
{
public:
	HelpMenuScreen(MainMenuGameState *mainMenuGameState);
	virtual ~HelpMenuScreen();
	
	void OnExitHelpMenu();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();
	
private:
	HelpMenuView *view;
	MainMenuGameState *mainMenuGameState;
	bool m_requestShowHomeMenu;
};