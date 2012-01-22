/*
 *  StoryModeGameState.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryModeGameState.h"
#include "Game.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

/*
 Change the pause menu to a View, make the storyModeView a special view that is always rendered, used the m_request stuff
 to show pause menu, and its submenu stuff
 */


extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;
extern SaveGameManager *saveGameManager;
//extern SavedGame *saved_game;

StoryModeGameState::StoryModeGameState()
{
	m_requestMainMenu = false;
	m_requestCloseSubview = false;
	subView = NULL;
	requestSubview = NULL;
	m_requestWonGame = false;
}

StoryModeGameState::~StoryModeGameState()
{

}

//IState
bool StoryModeGameState::Begin()
{
	storyModeSaveInfo = saveGameManager->LoadStoryModeSaveInfo();
	settingsSaveInfo = saveGameManager->LoadSettingsSaveInfo();
	trophySaveInfo = saveGameManager->LoadTrophySaveInfo();
	arcadeModeSaveInfo = saveGameManager->LoadArcadeModeSaveInfo();
	
	storyModeView = new StoryModeView();
	//view->OnMainMenu += Delegate(this, &StoryModeGameState::OnMainMenu);
	storyModeView->OnShowPauseMenu += Delegate(this, &StoryModeGameState::OnShowPauseMenu);
	storyModeView->OnShowStore += Delegate(this, &StoryModeGameState::OnShowStore);
	storyModeView->OnShowScoreScreen += Delegate1<StoryModeGameState, StoryModeScoreData*>(this, &StoryModeGameState::OnShowScoreScreen);
	storyModeView->OnShowCharacterBonusMenu += Delegate(this, &StoryModeGameState::OnShowCharacterBonusMenu);
	input_engine->RegisterInputController(storyModeView);
	
	//saved_game->OnSaveOnTerminate += Delegate(this, &StoryModeGameState::OnSaveOnTerminate);
	storyModeView->LoadFromSaveInfo(storyModeSaveInfo);
	storyModeView->LoadFromTrophySaveInfo(trophySaveInfo);
	storyModeView->LoadArcadeBlocksCleared(arcadeModeSaveInfo);
	storyModeView->LoadFromSettingsSaveInfo(settingsSaveInfo);
	saveGameManager->SetCurrentSaveOnTerminate(this);
	return true;
}

void StoryModeGameState::End()
{
	OnSaveOnTerminate();
	
	//saved_game->OnSaveOnTerminate.Clear();
	saveGameManager->SetCurrentSaveOnTerminate(NULL);
	input_engine->UnregisterInputController();
		
	if (subView != NULL)
	{
		delete subView;
		subView = NULL;
	}
}

int StoryModeGameState::Process()
{
	// Swap out the subview for the requested subview if it has changed
	if (requestSubview != NULL)
	{
		if (subView != NULL)
			delete subView;
		
		subView = requestSubview;
		requestSubview = NULL;
	}
	
	if (!storyModeView->IsPaused())
		storyModeView->Update();
	
	if (subView != NULL)
		subView->Update();

	// Render the views
	graphics_engine->BeginFrame();
	
	storyModeView->Render();
	
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
		
		storyModeView->PauseAnimation(false);
		input_engine->RegisterInputController(storyModeView);
	}

	if (m_requestWonGame)
	{
		// update save info
		storyModeSaveInfo->SetHasWonGame(true);
		//storyModeSaveInfo->Save();
		saveGameManager->SaveStoryModeSaveInfo(storyModeSaveInfo);
		saveGameManager->SaveTrophySaveInfo(trophySaveInfo);
		ShowWinningScrapbookMenu(); // won game
		storyModeView->LoadStarBonusSaveInfo(storyModeSaveInfo);
		m_requestWonGame = false;
	}
	
	return CR::Utility::IState::UNCHANGED;
}

void StoryModeGameState::OnShowMainMenu()
{
	// return to main menu
	m_requestMainMenu = true;
}

void StoryModeGameState::OnShowPauseMenu()
{
	// Save info about trophies, etc
	storyModeView->WriteToTrophySaveInfo(trophySaveInfo);
	
	requestSubview = new PauseMenuView();
	((PauseMenuView *)requestSubview)->OnMainMenuClicked += Delegate(this, &StoryModeGameState::OnShowMainMenu);
	((PauseMenuView *)requestSubview)->OnResumeGameClicked += Delegate(this, &StoryModeGameState::OnCloseSubview);
	((PauseMenuView *)requestSubview)->OnOptionsClicked += Delegate(this, &StoryModeGameState::OnShowOptionsMenu);
	((PauseMenuView *)requestSubview)->OnHowToPlayClicked += Delegate(this, &StoryModeGameState::OnShowHowToPlayMenu);
	((PauseMenuView *)requestSubview)->OnScrapbookClicked += Delegate(this, &StoryModeGameState::OnShowScrapbookMenu);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
	
	
	int modLevel = (storyModeView->GetCurrentLevel()-1) % 10;
	if (modLevel < 5)
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory1::ID);
	else
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory2::ID);
}

void StoryModeGameState::OnShowOptionsMenu()
{	
	requestSubview = new OptionsMenuView(false);
	((OptionsMenuView *)requestSubview)->OnExitClicked += Delegate(this, &StoryModeGameState::OnCloseOptionsMenu);
	((OptionsMenuView *)requestSubview)->LoadFromSaveInfo(settingsSaveInfo);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
}

void StoryModeGameState::OnCloseOptionsMenu()
{
	((OptionsMenuView *)subView)->WriteToSaveInfo(settingsSaveInfo);
	saveGameManager->SaveSettingsSaveInfo(settingsSaveInfo);
	storyModeView->LoadFromSettingsSaveInfo(settingsSaveInfo);
	OnShowPauseMenu();
}

void StoryModeGameState::OnCloseCharacterBonusMenu()
{
	((CharacterBonusView *)subView)->WriteToSaveInfo(storyModeSaveInfo);
	//saveGameManager->SaveStoryModeSaveInfo(storyModeSaveInfo);
	storyModeView->SetCharacterBonus(((CharacterBonusView *)subView)->GetCurrentCharacter(), ((CharacterBonusView *)subView)->GetCurrentCharacterLevel());
	OnCloseSubview();
}

void StoryModeGameState::OnCloseStore()
{
	((ShopMenuView *)subView)->WriteToSaveInfo(storyModeSaveInfo);
	
	// Special check that automatically sets the character if one has been purchased and one has not yet been selected
	if (storyModeSaveInfo->GetCurrentCharacter() == NoCharacter)
	{
		CharacterLevels *cLevels = storyModeSaveInfo->GetCharacterLevels();
		if(cLevels->GetCharacterLevel(Mayor) > 0) storyModeSaveInfo->SetCurrentCharacter(Mayor);
		if(cLevels->GetCharacterLevel(Elder) > 0) storyModeSaveInfo->SetCurrentCharacter(Elder);
		if(cLevels->GetCharacterLevel(Fireman) > 0) storyModeSaveInfo->SetCurrentCharacter(Fireman);
		if(cLevels->GetCharacterLevel(Dog) > 0) storyModeSaveInfo->SetCurrentCharacter(Dog);
		if(cLevels->GetCharacterLevel(Baker) > 0) storyModeSaveInfo->SetCurrentCharacter(Baker);
		if(cLevels->GetCharacterLevel(Teacher) > 0) storyModeSaveInfo->SetCurrentCharacter(Teacher);
		if(cLevels->GetCharacterLevel(Librarian) > 0) storyModeSaveInfo->SetCurrentCharacter(Librarian);
		if(cLevels->GetCharacterLevel(Romeo) > 0) storyModeSaveInfo->SetCurrentCharacter(Romeo);
		if(cLevels->GetCharacterLevel(Felicia) > 0) storyModeSaveInfo->SetCurrentCharacter(Felicia);
		if(cLevels->GetCharacterLevel(Bruiser) > 0) storyModeSaveInfo->SetCurrentCharacter(Bruiser);
		if(cLevels->GetCharacterLevel(Marla) > 0) storyModeSaveInfo->SetCurrentCharacter(Marla);
		if(cLevels->GetCharacterLevel(ChopChop) > 0) storyModeSaveInfo->SetCurrentCharacter(ChopChop);
		//delete cLevels;
	 }
	
	storyModeView->LoadStarBonusSaveInfo(storyModeSaveInfo);
	OnCloseSubview();

	if (!storyModeSaveInfo->GetHasWonGame()) // player has beaten the game (all items bought)
	{
		// check all items
		//storyModeView->WriteToSaveInfo(storyModeSaveInfo);
		//storyModeView->WriteToTrophySaveInfo(trophySaveInfo);
		if 	(((ShopMenuView *)subView)->GetHasEverything())
			m_requestWonGame = true;
	}
}

void StoryModeGameState::OnShowHowToPlayMenu()
{
	requestSubview = new HelpMenuView(false);
	((HelpMenuView *)requestSubview)->OnExitClicked += Delegate(this, &StoryModeGameState::OnShowPauseMenu);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
}

void StoryModeGameState::OnShowScrapbookMenu()
{
	requestSubview = new ScrapbookMenuView();
	((ScrapbookMenuView *)requestSubview)->OnExitClicked += Delegate(this, &StoryModeGameState::OnShowPauseMenu);
	storyModeView->WriteToSaveInfo(storyModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromSaveInfo(storyModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromArcadeSaveInfo(arcadeModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromTrophySaveInfo(trophySaveInfo);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
}

void StoryModeGameState::ShowWinningScrapbookMenu()
{
	requestSubview = new ScrapbookMenuView(true);
	((ScrapbookMenuView *)requestSubview)->OnExitClicked += Delegate(this, &StoryModeGameState::OnShowPauseMenu);
	storyModeView->WriteToSaveInfo(storyModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromSaveInfo(storyModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromArcadeSaveInfo(arcadeModeSaveInfo);
	((ScrapbookMenuView *)requestSubview)->LoadFromTrophySaveInfo(trophySaveInfo);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
}

void StoryModeGameState::OnShowScoreScreen(StoryModeScoreData *scoreData)
{
	//m_requestScoreScreen = true;
	requestSubview = new StoryModeScoreView(scoreData);
	((StoryModeScoreView *)requestSubview)->OnResumeGameClicked += Delegate(this, &StoryModeGameState::OnCloseScoreView);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
}

void StoryModeGameState::OnCloseScoreView()
{
	OnCloseSubview();
	
	int modLevel = (storyModeView->GetCurrentLevel()-1) % 10;
	if (modLevel < 5)
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory1::ID);
	else
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory2::ID);
	
	storyModeView->TriggerTouchToEnterStore();
}

void StoryModeGameState::OnShowCharacterBonusMenu()
{
	requestSubview = new CharacterBonusView();
	((CharacterBonusView *)requestSubview)->OnClose += Delegate(this, &StoryModeGameState::OnCloseCharacterBonusMenu);
	((CharacterBonusView *)requestSubview)->OnChangeCharacter += Delegate(this, &StoryModeGameState::OnChangeCharacter);
	((CharacterBonusView *)requestSubview)->LoadFromSaveInfo(storyModeSaveInfo);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
}

void StoryModeGameState::OnShowStore()
{
	requestSubview = new ShopMenuView();
	((ShopMenuView *)requestSubview)->OnClose += Delegate(this, &StoryModeGameState::OnCloseStore);
	storyModeView->WriteToSaveInfo(storyModeSaveInfo);
	((ShopMenuView *)requestSubview)->LoadFromSaveInfo(storyModeSaveInfo);
	input_engine->RegisterInputController(requestSubview);
	storyModeView->PauseAnimation(true);
}

void StoryModeGameState::OnCloseSubview()
{
	m_requestCloseSubview = true;
}

void StoryModeGameState::OnChangeCharacter()
{
	if (subView != NULL)
		storyModeView->SetCharacterBonus(((CharacterBonusView *)subView)->GetCurrentCharacter(), ((CharacterBonusView *)subView)->GetCurrentCharacterLevel());
}

void StoryModeGameState::OnSaveOnTerminate()
{
	// if options menu is currently being displayed, save its info
	//if (((OptionsMenuView *)subView) != NULL)
	//	((OptionsMenuView *)subView)->WriteToSaveInfo(settingsSaveInfo);
	if (dynamic_cast<OptionsMenuView*> (subView) != NULL)
		((OptionsMenuView *)subView)->WriteToSaveInfo(settingsSaveInfo);
	//else if (dynamic_cast<CharacterBonusView*> (subView) != NULL)
	//	((CharacterBonusView *)subView)->WriteToSaveInfo(storyModeSaveInfo);
	storyModeView->WriteToTrophySaveInfo(trophySaveInfo);
	storyModeView->WriteToSaveInfo(storyModeSaveInfo);
	saveGameManager->SaveStoryModeSaveInfo(storyModeSaveInfo);
	saveGameManager->SaveSettingsSaveInfo(settingsSaveInfo);
	saveGameManager->SaveTrophySaveInfo(trophySaveInfo);
}