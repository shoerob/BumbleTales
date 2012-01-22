/*
 *  HelpMenuScreen.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "HelpMenuScreen.h"
#include "MainMenuGameState.h"

extern Input_Engine *input_engine;

HelpMenuScreen::HelpMenuScreen(MainMenuGameState *mainMenuGameState)
{
	this->mainMenuGameState = mainMenuGameState;
	m_requestShowHomeMenu = false;
}

HelpMenuScreen::~HelpMenuScreen()
{
	
}

//IState
bool HelpMenuScreen::Begin()
{
	view = new HelpMenuView(true);
	view->OnExitClicked += Delegate(this, &HelpMenuScreen::OnExitHelpMenu);
	input_engine->RegisterInputController(view);
	return true;
}

void HelpMenuScreen::End()
{
	input_engine->UnregisterInputController();
	delete view;
}

int HelpMenuScreen::Process()
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

void HelpMenuScreen::OnExitHelpMenu()
{
	m_requestShowHomeMenu = true;
}
