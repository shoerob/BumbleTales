/*
 *  SplashScreenMenu.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "FSM.h"
#include "Input_Engine.h"
#include "SplashScreenMenuView.h"

class MainMenuGameState;

class SplashScreenMenu : public CR::Utility::IState
{
public:
	SplashScreenMenu(MainMenuGameState *mainMenuGameState);
	virtual ~SplashScreenMenu();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();
	
	void OnExitSplashScreen();
	
private:
	SplashScreenMenuView *view;
	MainMenuGameState *mainMenuGameState;
	bool m_requestShowHomeMenu;
};