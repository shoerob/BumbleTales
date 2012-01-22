/*
 *  ArcadeModeGameState.cpp
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ArcadeModeGameState.h"
#include "Game.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;
extern SaveGameManager *saveGameManager;

ArcadeModeGameState::ArcadeModeGameState()
{
	m_requestMainMenu = false;
	m_requestCloseSubview = false;
	subView = NULL;
	requestSubview = NULL;
}

ArcadeModeGameState::~ArcadeModeGameState()
{
	
}

//IState
bool ArcadeModeGameState::Begin()
{
	storyModeSaveInfo = saveGameManager->LoadStoryModeSaveInfo();
	arcadeModeSaveInfo = saveGameManager->LoadArcadeModeSaveInfo();
	settingsSaveInfo = saveGameManager->LoadSettingsSaveInfo();
	trophySaveInfo = saveGameManager->LoadTrophySaveInfo();
	
	arcadeModeView = new ArcadeModeView();
	arcadeModeView->OnShowPauseMenu += Delegate(this, &ArcadeModeGameState::OnShowPauseMenu);
	arcadeModeView->OnShowScoreScreen += Delegate1<ArcadeModeGameState, ArcadeModeScoreData*>(this, &ArcadeModeGameState::OnShowScoreScreen);
	arcadeModeView->OnShowCharacterBonusMenu += Delegate(this, &ArcadeModeGameState::OnShowCharacterBonusMenu);
	input_engine->RegisterInputController(arcadeModeView);

	arcadeModeView->LoadStarBonusSaveInfo(storyModeSaveInfo);
	arcadeModeView->LoadFromSaveInfo(arcadeModeSaveInfo);
	arcadeModeView->LoadFromTrophySaveInfo(trophySaveInfo);
	arcadeModeView->LoadFromSettingsSaveInfo(settingsSaveInfo);
	saveGameManager->SetCurrentSaveOnTerminate(this);
	ISound::Instance().PlaySong(CR::AssetList::music::BGMArcade::ID);
	return true;
}

void ArcadeModeGameState::End()
{
	OnSaveOnTerminate();
	
	saveGameManager->SetCurrentSaveOnTerminate(NULL);
	input_engine->UnregisterInputController();
		
	if (subView != NULL)
	{
		delete subView;
		subView = NULL;
	}
}

int ArcadeModeGameState::Process()
{
	// Swap out the subview for the requested subview if it has changed
	if (requestSubview != NULL)
	{
		if (subView != NULL)
			delete subView;
		
		subView = requestSubview;
		requestSubview = NULL;
	}
	
	if (!arcadeModeView->IsPaused())
		arcadeModeView->Update();
	
	if (subView != NULL)
		subView->Update();
	
	// Render the views
	graphics_engine->BeginFrame();
	
	arcadeModeView->Render();
	
	if (subView != NULL)
		subView->Render();
	
	graphics_engine->EndFrame();
	
	if (m_requestMainMenu)
	{
		m_requestMainMenu = false;
		return MAIN_MENU_STATE;
	}
	
	// Close the subview and show the main storymodeview if requested
	if (m_requestCloseSubview)
	{
		m_requestCloseSubview = false;
		
		if (subView != NULL)
		{
			delete subView;
			subView = NULL;
		}
		
		arcadeModeView->PauseAnimation(false);
		input_engine->RegisterInputController(arcadeModeView);
	}
	
	return CR::Utility::IState::UNCHANGED;
}

void ArcadeModeGameState::OnShowMainMenu()
{
	// return to main menu
	m_requestMainMenu = true;
}

void ArcadeModeGameState::OnShowPauseMenu()
{
	ISound::Instance().PlaySong(CR::AssetList::music::BGMArcade::ID);
	requestSubview = new PauseMenuView();
	((PauseMenuView *)requestSubview)->OnMainMenuClicked += Delegate(this, &ArcadeModeGameState::OnShowMainMenu);
	((PauseMenuView *)requestSubview)->OnResumeGameClicked += Delegate(this, &ArcadeModeGameState::OnCloseSubview);
	((PauseMenuView *)requestSubview)->OnOptionsClicked += Delegate(this, &ArcadeModeGameState::OnShowOptionsMenu);
	((PauseMenuView *)requestSubview)->OnHowToPlayClicked += Delegate(this, &ArcadeModeGameState::OnShowHowToPlayMenu);
	((PauseMenuView *)requestSubview)->OnScrapbookClicked += Delegate(this, &ArcadeModeGameState::OnShowScrapbookMenu);
	input_engine->RegisterInputController(requestSubview);
	arcadeModeView->PauseAnimation(true);
}

void ArcadeModeGameState::OnShowOptionsMenu()
{
	requestSubview = new OptionsMenuView(false);
	((OptionsMenuView *)requestSubview)->OnExitClicked += Delegate(this, &ArcadeModeGameState::OnCloseOptionsMenu);
	((OptionsMenuView *)requestSubview)->LoadFromSaveInfo(settingsSaveInfo);
	input_engine->RegisterInputController(requestSubview);
	arcadeModeView->PauseAnimation(true);
}

void ArcadeModeGameState::OnCloseOptionsMenu()
{
	((OptionsMenuView *)subView)->WriteToSaveInfo(settingsSaveInfo);
	saveGameManager->SaveSettingsSaveInfo(settingsSaveInfo);
	arcadeModeView->LoadFromSettingsSaveInfo(settingsSaveInfo);
	OnShowPauseMenu();
}

void ArcadeModeGameState::OnCloseCharacterBonusMenu()
{
	((CharacterBonusView *)subView)->WriteToSaveInfo(storyModeSaveInfo);
	//saveGameManager->SaveStoryModeSaveInfo(storyModeSaveInfo);
	arcadeModeView->SetCharacterBonus(((CharacterBonusView *)subView)->GetCurrentCharacter(), ((CharacterBonusView *)subView)->GetCurrentCharacterLevel());
	OnCloseSubview();
}

/*void ArcadeModeGameState::OnCloseStore()
{
	((ShopMenuView *)subView)->WriteToSaveInfo(storyModeSaveInfo);
	arcadeModeView->LoadStarBonusSaveInfo(storyModeSaveInfo);
	OnCloseSubview();
}*/

void ArcadeModeGameState::OnShowHowToPlayMenu()
{
	requestSubview = new HelpMenuView(false);
	((HelpMenuView *)requestSubview)->OnExitClicked += Delegate(this, &ArcadeModeGameState::OnShowPauseMenu);
	input_engine->RegisterInputController(requestSubview);
	arcadeModeView->PauseAnimation(true);
}

void ArcadeModeGameState::OnShowScrapbookMenu()
{
	requestSubview = new ScrapbookMenuView();
	((ScrapbookMenuView *)requestSubview)->OnExitClicked += Delegate(this, &ArcadeModeGameState::OnShowPauseMenu);
	arcadeModeView->WriteToSaveInfo(arcadeModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromSaveInfo(storyModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromArcadeSaveInfo(arcadeModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromTrophySaveInfo(trophySaveInfo);
	input_engine->RegisterInputController(requestSubview);
	arcadeModeView->PauseAnimation(true);
}

void ArcadeModeGameState::OnShowScoreScreen(ArcadeModeScoreData *scoreData)
{
	//m_requestScoreScreen = true;
	requestSubview = new ArcadeModeScoreView(scoreData);
	((ArcadeModeScoreView *)requestSubview)->OnYesClicked += Delegate(this, &ArcadeModeGameState::OnStartNewGame);
	((ArcadeModeScoreView *)requestSubview)->OnNoClicked += Delegate(this, &ArcadeModeGameState::OnShowMainMenu);
	input_engine->RegisterInputController(requestSubview);
	arcadeModeView->PauseAnimation(true);
}

void ArcadeModeGameState::OnShowCharacterBonusMenu()
{
	requestSubview = new CharacterBonusView();
	((CharacterBonusView *)requestSubview)->OnClose += Delegate(this, &ArcadeModeGameState::OnCloseCharacterBonusMenu);
	((CharacterBonusView *)requestSubview)->OnChangeCharacter += Delegate(this, &ArcadeModeGameState::OnChangeCharacter);
	((CharacterBonusView *)requestSubview)->LoadFromSaveInfo(storyModeSaveInfo);
	input_engine->RegisterInputController(requestSubview);
	arcadeModeView->PauseAnimation(true);
}

void ArcadeModeGameState::OnStartNewGame()
{
	OnCloseSubview();
}

void ArcadeModeGameState::OnCloseSubview()
{
	ISound::Instance().PlaySong(CR::AssetList::music::BGMArcade::ID);
	m_requestCloseSubview = true;
}

void ArcadeModeGameState::OnChangeCharacter()
{
	if (subView != NULL)
		arcadeModeView->SetCharacterBonus(((CharacterBonusView *)subView)->GetCurrentCharacter(), ((CharacterBonusView *)subView)->GetCurrentCharacterLevel());
}

void ArcadeModeGameState::OnSaveOnTerminate()
{
	// if options menu is currently being displayed, save its info
	//if (((OptionsMenuView *)subView) != NULL)
	//	((OptionsMenuView *)subView)->WriteToSaveInfo(settingsSaveInfo);
	if (dynamic_cast<OptionsMenuView*> (subView) != NULL)
		((OptionsMenuView *)subView)->WriteToSaveInfo(settingsSaveInfo);
	//else if (dynamic_cast<CharacterBonusView*> (subView) != NULL)
	//	((CharacterBonusView *)subView)->WriteToSaveInfo(storyModeSaveInfo);
	
	arcadeModeView->WriteToSaveInfo(arcadeModeSaveInfo);
	arcadeModeView->WriteToTrophySaveInfo(trophySaveInfo);
	//saveGameManager->SaveStoryModeSaveInfo(storyModeSaveInfo);
	saveGameManager->SaveArcadeModeSaveInfo(arcadeModeSaveInfo);
	saveGameManager->SaveSettingsSaveInfo(settingsSaveInfo);
	saveGameManager->SaveTrophySaveInfo(trophySaveInfo);
}