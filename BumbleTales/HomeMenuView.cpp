/*
 *  HomeMenuView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "HomeMenuView.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

HomeMenuView::HomeMenuView()
{
	storyModeButton = new Input_Button();
	storyModeButton->SetSpriteAndBounds(13, 232, CR::AssetList::Menu_Story_Mode_Button, 800);
	storyModeButton->OnClicked += Delegate(this, &HomeMenuView::OnStoryModeClicked);
	storyModeButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(storyModeButton);
	
	arcadeModeButton = new Input_Button();
	arcadeModeButton->SetSpriteAndBounds(13, 292, CR::AssetList::Menu_Arcade_Mode_Button, 800);
	arcadeModeButton->OnClicked += Delegate(this, &HomeMenuView::OnArcadeModeClicked);
	arcadeModeButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(arcadeModeButton);

	scrapbookButton = new Input_Button();
	scrapbookButton->SetSpriteAndBounds(13, 352, CR::AssetList::Menu_Scrapbook_Button, 800);
	scrapbookButton->OnClicked += Delegate(this, &HomeMenuView::OnScrapbookClicked);
	scrapbookButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(scrapbookButton);

	helpButton = new Input_Button();
	helpButton->SetSpriteAndBounds(13, 412, CR::AssetList::Menu_Help_Info_Button, 800);
	//helpButton->SetSpriteAndBounds(13, 412, CR::AssetList::Menu_More_Games_Button, 800);
	helpButton->OnClicked += Delegate(this, &HomeMenuView::OnHelpClicked);
	helpButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(helpButton);

	optionsButton = new Input_Button();
	optionsButton->SetSpriteAndBounds(109, 412, CR::AssetList::Menu_Options_Button, 800);
	optionsButton->OnClicked += Delegate(this, &HomeMenuView::OnOptionsClicked);
	optionsButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(optionsButton);
	
	moreGamesButton = new Input_Button();
	moreGamesButton->SetSpriteAndBounds(205, 412, CR::AssetList::Menu_More_Games_Button, 800);
	moreGamesButton->OnClicked += Delegate(this, &HomeMenuView::OnMoreGamesClicked);
	moreGamesButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(moreGamesButton);
	
	menuBackground = graphics_engine->CreateSprite1(false,1000);
	menuBackground->SetImage(CR::AssetList::Menu_Background);
	menuBackground->SetPositionAbsolute(160, 240);
}

HomeMenuView::~HomeMenuView()
{
	delete storyModeButton;
	delete arcadeModeButton;
	delete scrapbookButton;
	delete helpButton;
	delete optionsButton;
	delete moreGamesButton;
	menuBackground->Release();
}

void HomeMenuView::Update()
{
}

void HomeMenuView::Render()
{
	graphics_engine->BeginFrame();
	menuBackground->Render();
	storyModeButton->Render();
	arcadeModeButton->Render();
	scrapbookButton->Render();
	helpButton->Render();
	optionsButton->Render();
	moreGamesButton->Render();
	graphics_engine->EndFrame();
}

void HomeMenuView::OnStoryModeClicked()
{
	OnStartStoryMode();
}

void HomeMenuView::OnArcadeModeClicked()
{
	OnStartArcadeMode();
}

void HomeMenuView::OnScrapbookClicked()
{
	OnShowScrapbookMenu();
}

void HomeMenuView::OnHelpClicked()
{
	OnShowHelpMenu();
}

void HomeMenuView::OnOptionsClicked()
{
	OnShowOptionsMenu();
}

void HomeMenuView::OnMoreGamesClicked()
{
	OnShowMoreGamesMenu();
}