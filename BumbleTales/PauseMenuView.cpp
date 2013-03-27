/*
 *  PauseMenuView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "PauseMenuView.h"
#include "AssetListFull.h"
#include "NewAssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

PauseMenuView::PauseMenuView()
{
	pauseBackground = graphics_engine->CreateSprite1(false,500);
	pauseBackground->SetImage(CR::AssetList::Pause_Menu_Background);
	pauseBackground->SetPositionAbsolute(160, 240);
	pauseBackground->SetDesignSize(320, 480);
	
	resumeGameButton = new Input_Button();
	resumeGameButton->SetSpriteAndBounds(52, 353, CR::AssetList::Pause_Resume_Game_Button, 400);
	resumeGameButton->DesignSize(217, 53);
	resumeGameButton->OnClicked += Delegate(this, &PauseMenuView::OnResumeGameButtonPressed);
	resumeGameButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(resumeGameButton);
	
	mainMenuButton = new Input_Button();
	mainMenuButton->SetSpriteAndBounds(52, 293, CR::AssetList::Pause_Main_Menu_Button, 400);
	mainMenuButton->DesignSize(217, 53);
	mainMenuButton->OnClicked += Delegate(this, &PauseMenuView::OnMainMenuButtonPressed);
	mainMenuButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(mainMenuButton);
	
	howToPlayButton = new Input_Button();
	howToPlayButton->SetSpriteAndBounds(52, 233, CR::AssetList::Pause_How_To_Play_Button, 400);
	howToPlayButton->DesignSize(218, 52);
	howToPlayButton->OnClicked += Delegate(this, &PauseMenuView::OnHowToPlayButtonPressed);
	howToPlayButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(howToPlayButton);
	
	optionsButton = new Input_Button();
	optionsButton->SetSpriteAndBounds(52, 173, CR::AssetList::Pause_Options_Button, 400);
	optionsButton->DesignSize(217, 52);
	optionsButton->OnClicked += Delegate(this, &PauseMenuView::OnOptionsButtonPressed);
	optionsButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(optionsButton);
	
	scrapBookButton = new Input_Button();
	scrapBookButton->SetSpriteAndBounds(52, 113, CR::AssetList::Pause_Scrapbook_Button, 400);
	scrapBookButton->DesignSize(218, 52);
	scrapBookButton->OnClicked += Delegate(this, &PauseMenuView::OnScrapBookButtonPressed);
	scrapBookButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(scrapBookButton);
}

PauseMenuView::~PauseMenuView()
{
	pauseBackground->Release();
	delete mainMenuButton;
	delete resumeGameButton;
	delete howToPlayButton;
	delete optionsButton;
	delete scrapBookButton;
}

void PauseMenuView::Update()
{
	
}

void PauseMenuView::Render()
{
	pauseBackground->Render();
	resumeGameButton->Render();
	mainMenuButton->Render();
	howToPlayButton->Render();
	optionsButton->Render();
	scrapBookButton->Render();
}


void PauseMenuView::OnResumeGameButtonPressed()
{
	if(OnResumeGameClicked.Size() > 0)
		OnResumeGameClicked();
}

void PauseMenuView::OnMainMenuButtonPressed()
{
	if(OnMainMenuClicked.Size() > 0)
		OnMainMenuClicked();
}

void PauseMenuView::OnHowToPlayButtonPressed()
{
	if (OnHowToPlayClicked.Size() > 0)
		OnHowToPlayClicked();
}

void PauseMenuView::OnOptionsButtonPressed()
{
	if (OnOptionsClicked.Size() > 0)
		OnOptionsClicked();
}

void PauseMenuView::OnScrapBookButtonPressed()
{
	if (OnScrapbookClicked.Size() > 0)
		OnScrapbookClicked();
}