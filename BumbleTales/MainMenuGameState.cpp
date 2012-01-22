/*
 *  MainMenuGameState.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "MainMenuGameState.h"
#include "Game.h"

MainMenuGameState::MainMenuGameState()
{
	stateMachine << new SplashScreenMenu(this) << new HomeMenuScreen(this) << new OptionsMenuScreen(this) << new HelpMenuScreen(this) << new MoreGamesMenuScreen(this) << new ScrapbookMenuScreen(this);
	stateMachine.State = SPLASH_MENU_STATE;
	m_showSplashScreen = true;
}

MainMenuGameState::~MainMenuGameState()
{
}

bool MainMenuGameState::Begin()
{
	if (m_showSplashScreen)
	{
		stateMachine.State = SPLASH_MENU_STATE;
		m_showSplashScreen = false;
	}
	else
		stateMachine.State = HOME_MENU_STATE;
	
	m_requestStartStoryMode = false;
	m_requestStartArcadeMode = false;
	return true;
}

void MainMenuGameState::End()
{
	stateMachine.Reset();
}

int MainMenuGameState::Process()
{
	stateMachine();
	
	if (m_requestStartStoryMode)
	{
		m_requestStartStoryMode = false;
		return STORY_MODE_STATE;
	}
	else if (m_requestStartArcadeMode)
	{
		m_requestStartArcadeMode = false;
		return ARCADE_MODE_STATE;
	}
	/*else if (m_requestShowOptionsMenu)
	{
		m_requestShowOptionsMenu = false;
		return OPTIONS_MENU_STATE;
	}*/
	
	return CR::Utility::IState::UNCHANGED;
}

void MainMenuGameState::StartStoryMode()
{
	m_requestStartStoryMode = true;
}

void MainMenuGameState::StartArcadeMode()
{
	m_requestStartArcadeMode = true;
}