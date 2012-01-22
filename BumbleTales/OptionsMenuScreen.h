/*
 *  OptionsMenuScreen.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "FSM.h"
#include "Input_Engine.h"
#include "OptionsMenuView.h"
#include "SettingsSaveInfo.h"
#include "ISaveOnTerminate.h"

class MainMenuGameState;

class OptionsMenuScreen : public CR::Utility::IState, public ISaveOnTerminate
{
public:
	OptionsMenuScreen(MainMenuGameState *mainMenuGameState);
	virtual ~OptionsMenuScreen();
	
	//void OnStartStoryMode();
	void OnExitOptionsMenu();
	void OnEraseData();
	
	//IState
	virtual bool Begin();
	virtual void End();
	virtual int Process();
	
	// Save
	void OnSaveOnTerminate();
	
private:
	OptionsMenuView *view;
	MainMenuGameState *mainMenuGameState;
	bool m_requestShowHomeMenu;
	SettingsSaveInfo *saveInfo;
};