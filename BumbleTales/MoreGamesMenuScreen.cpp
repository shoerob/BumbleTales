/*
 *  MoreGamesMenuScreen.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "MoreGamesMenuScreen.h"
#include "MainMenuGameState.h"

extern Input_Engine *input_engine;

MoreGamesMenuScreen::MoreGamesMenuScreen(MainMenuGameState *mainMenuGameState)
{
	this->mainMenuGameState = mainMenuGameState;
	m_requestShowHomeMenu = false;
}

MoreGamesMenuScreen::~MoreGamesMenuScreen()
{
	
}

//IState
bool MoreGamesMenuScreen::Begin()
{
	view = new MoreGamesMenuView();
	view->OnExitClicked += Delegate(this, &MoreGamesMenuScreen::OnExitMoreGamesMenu);
	input_engine->RegisterInputController(view);
	return true;
}

void MoreGamesMenuScreen::End()
{
	input_engine->UnregisterInputController();
	delete view;
}

int MoreGamesMenuScreen::Process()
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

void MoreGamesMenuScreen::OnExitMoreGamesMenu()
{
	m_requestShowHomeMenu = true;
}
