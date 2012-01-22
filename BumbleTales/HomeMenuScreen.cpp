/*
 *  HomeMenuScreen.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "HomeMenuScreen.h"
#include "MainMenuGameState.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern Input_Engine *input_engine;

HomeMenuScreen::HomeMenuScreen(MainMenuGameState *mainMenuGameState)
{
	this->mainMenuGameState = mainMenuGameState;
	m_requestShowOptionsMenu = false;
	m_requestShowHelpMenu = false;
	m_requestShowMoreGamesMenu = false;
	m_requestShowScrapbookMenu = false;
}

HomeMenuScreen::~HomeMenuScreen()
{

}

//IState
bool HomeMenuScreen::Begin()
{
	view = new HomeMenuView();
	view->OnStartStoryMode += Delegate(this, &HomeMenuScreen::OnStartStoryMode);
	view->OnStartArcadeMode += Delegate(this, &HomeMenuScreen::OnStartArcadeMode);
	view->OnShowOptionsMenu += Delegate(this, &HomeMenuScreen::OnShowOptionsMenu); 
	view->OnShowHelpMenu += Delegate(this, &HomeMenuScreen::OnShowHelpMenu);
	view->OnShowMoreGamesMenu += Delegate(this, &HomeMenuScreen::OnShowMoreGamesMenu);
	view->OnShowScrapbookMenu += Delegate(this, &HomeMenuScreen::OnShowScrapbookMenu);
	
	input_engine->RegisterInputController(view);
	
	ISound::Instance().PlaySong(CR::AssetList::music::BGMMenu::ID);
	
	return true;
}

void HomeMenuScreen::End()
{
	input_engine->UnregisterInputController();
	delete view;
}

int HomeMenuScreen::Process()
{
	view->Update();
	view->Render();
	
	if (m_requestShowOptionsMenu)
	{
		m_requestShowOptionsMenu = false;
		return OPTIONS_MENU_STATE;
	}
	else if (m_requestShowHelpMenu)
	{
		m_requestShowHelpMenu = false;
		return HELP_MENU_STATE;
	}
	else if (m_requestShowMoreGamesMenu)
	{
		m_requestShowMoreGamesMenu = false;
		return MORE_GAMES_MENU_STATE;
	}
	else if (m_requestShowScrapbookMenu)
	{
		m_requestShowScrapbookMenu = false;
		return SCRAPBOOK_MENU_STATE;
	}
	
	return CR::Utility::IState::UNCHANGED;
}

void HomeMenuScreen::OnStartStoryMode()
{
	mainMenuGameState->StartStoryMode();
}

void HomeMenuScreen::OnStartArcadeMode()
{
	mainMenuGameState->StartArcadeMode();
}

void HomeMenuScreen::OnShowOptionsMenu()
{
	//mainMenuGameState->ShowOptionsMenu();
	m_requestShowOptionsMenu = true;
}

void HomeMenuScreen::OnShowHelpMenu()
{
	m_requestShowHelpMenu = true;
}

void HomeMenuScreen::OnShowMoreGamesMenu()
{
	m_requestShowMoreGamesMenu = true;
}

void HomeMenuScreen::OnShowScrapbookMenu()
{
	m_requestShowScrapbookMenu = true;
}