/*
 *  ScrapbookMenuScreen.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ScrapbookMenuScreen.h"
#include "MainMenuGameState.h"
#include "SaveGameManager.h"


extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;
extern SaveGameManager *saveGameManager;

ScrapbookMenuScreen::ScrapbookMenuScreen(MainMenuGameState *mainMenuGameState)
{
	this->mainMenuGameState = mainMenuGameState;
	m_requestShowHomeMenu = false;
}

ScrapbookMenuScreen::~ScrapbookMenuScreen()
{
}

//IState
bool ScrapbookMenuScreen::Begin()
{
	saveInfo = saveGameManager->LoadStoryModeSaveInfo();
	arcadeModeSaveInfo = saveGameManager->LoadArcadeModeSaveInfo();
	trophySaveInfo = saveGameManager->LoadTrophySaveInfo();
	
	view = new ScrapbookMenuView();
	view->OnExitClicked += Delegate(this, &ScrapbookMenuScreen::OnExitScrapbookMenu);
	view->LoadFromSaveInfo(saveInfo);
	view->LoadFromArcadeSaveInfo(arcadeModeSaveInfo);
	view->LoadFromTrophySaveInfo(trophySaveInfo);
	input_engine->RegisterInputController(view);
	
	
	
	return true;
}

void ScrapbookMenuScreen::End()
{
	input_engine->UnregisterInputController();
	delete view;
	//delete saveInfo;
}

int ScrapbookMenuScreen::Process()
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


void ScrapbookMenuScreen::OnExitScrapbookMenu()
{
	m_requestShowHomeMenu = true;
}