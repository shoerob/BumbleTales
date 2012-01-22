/*
 *  PauseMenu.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "PauseMenu.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

PauseMenu::PauseMenu()
{
	pauseBackground = graphics_engine->CreateSprite1();
	pauseBackground->SetImage(CR::AssetList::Pause_Menu_Background);
	//pauseBackground->SetPositionAbsolute(160, 240);
	
	resumeGameButton = new Input_Button();
	resumeGameButton->SetSpriteAndBounds(0, 0, CR::AssetList::Pause_Resume_Game_Button);
	resumeGameButton->OnClicked += Delegate(this, &PauseMenu::OnResumeGameButtonPressed);
	input_objects.push_back(resumeGameButton);
	
	mainMenuButton = new Input_Button();
	mainMenuButton->SetSpriteAndBounds(0, 0, CR::AssetList::Pause_Main_Menu_Button);
	mainMenuButton->OnClicked += Delegate(this, &PauseMenu::OnMainMenuButtonPressed);
	input_objects.push_back(mainMenuButton);
	
	// Default position
	SetPosition(160, 240);
}

PauseMenu::~PauseMenu()
{
	pauseBackground->Release();
	//delete scrapBookButton;
	//delete optionsButton;
	//delete howToPlayButton;
	delete mainMenuButton;
	delete resumeGameButton;
}

void PauseMenu::Update()
{
	
}

void PauseMenu::Render()
{
	pauseBackground->Render();
	resumeGameButton->Render();
	mainMenuButton->Render();
}

void PauseMenu::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	// Set Sprite/Button Positions
	pauseBackground->SetPositionAbsolute(offset.X(), offset.Y());
	resumeGameButton->SetPosition(offset.X() - 108, offset.Y() + 115);
	mainMenuButton->SetPosition(offset.X() - 108, offset.Y() + 55);
}

void PauseMenu::PauseAnimation(bool pause)
{
	
}

void PauseMenu::OnResumeGameButtonPressed()
{
	if(OnResumeGame.Size() > 0)
		OnResumeGame();
}

void PauseMenu::OnMainMenuButtonPressed()
{
	if(OnMainMenu.Size() > 0)
		OnMainMenu();
}