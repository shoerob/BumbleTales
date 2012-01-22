/*
 *  SplashScreenMenu.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SplashScreenMenu.h"
#include "MainMenuGameState.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

SplashScreenMenu::SplashScreenMenu(MainMenuGameState *mainMenuGameState)
{
	this->mainMenuGameState = mainMenuGameState;
	m_requestShowHomeMenu = false;
}

SplashScreenMenu::~SplashScreenMenu()
{
}

bool SplashScreenMenu::Begin()
{
	view = new SplashScreenMenuView();
	view->ExitSplashScreen += Delegate(this, &SplashScreenMenu::OnExitSplashScreen);
	return true;
}

void SplashScreenMenu::End()
{
	delete view;
}

int SplashScreenMenu::Process()
{
	view->Update();
	
	graphics_engine->BeginFrame();
	view->Render();
	graphics_engine->EndFrame();
	
	if (m_requestShowHomeMenu)
	{
		m_requestShowHomeMenu = false;
		return HOME_MENU_STATE;
	}
	
	return CR::Utility::IState::UNCHANGED;
}

void SplashScreenMenu::OnExitSplashScreen()
{
	m_requestShowHomeMenu = true;
}
