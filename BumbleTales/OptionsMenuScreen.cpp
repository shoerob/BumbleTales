/*
 *  OptionsMenuScreen.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "OptionsMenuScreen.h"
#include "MainMenuGameState.h"
#include "SaveGameManager.h"

extern Input_Engine *input_engine;
extern SaveGameManager *saveGameManager;

OptionsMenuScreen::OptionsMenuScreen(MainMenuGameState *mainMenuGameState)
{
	this->mainMenuGameState = mainMenuGameState;
	m_requestShowHomeMenu = false;
}

OptionsMenuScreen::~OptionsMenuScreen()
{
	
}

//IState
bool OptionsMenuScreen::Begin()
{
	saveInfo = saveGameManager->LoadSettingsSaveInfo();
	
	view = new OptionsMenuView(true);
	view->OnExitClicked += Delegate(this, &OptionsMenuScreen::OnExitOptionsMenu);
	view->OnEraseData += Delegate(this, &OptionsMenuScreen::OnEraseData);
	view->LoadFromSaveInfo(saveInfo);
	input_engine->RegisterInputController(view);
	
	saveGameManager->SetCurrentSaveOnTerminate(this);
	return true;
}

void OptionsMenuScreen::End()
{
	OnSaveOnTerminate();
	saveGameManager->SetCurrentSaveOnTerminate(NULL);
	//delete saveInfo;
	//view->WriteToSaveInfo(saveInfo);
	input_engine->UnregisterInputController();
	delete view;
}

int OptionsMenuScreen::Process()
{
	view->Update();
	view->Render();
	
	if (m_requestShowHomeMenu)
	{
		m_requestShowHomeMenu = false;
		return HOME_MENU_STATE;
	}
	
	return CR::Utility::IState::UNCHANGED;
}

void OptionsMenuScreen::OnExitOptionsMenu()
{
	m_requestShowHomeMenu = true;
}

void OptionsMenuScreen::OnEraseData()
{
	saveGameManager->Reset();
	saveInfo = saveGameManager->LoadSettingsSaveInfo();
	view->LoadFromSaveInfo(saveInfo);
}

void OptionsMenuScreen::OnSaveOnTerminate()
{
	view->WriteToSaveInfo(saveInfo);
	saveGameManager->SaveSettingsSaveInfo(saveInfo);
}