/*
 *  StoryModeScore.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/19/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryModeScore.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

StoryModeScore::StoryModeScore()
{
	scoreBaseSprite = graphics_engine->CreateSprite1();
	scoreBaseSprite->SetImage(CR::AssetList::Score_Base_1);
	SetPosition(160, 240);
	
	okButton = new Input_Button();
	okButton->SetSpriteAndBounds(96, 400, CR::AssetList::Score_Ok_Button);
	okButton->OnClicked += Delegate(this, &StoryModeScore::OnOkButtonPressed);
	input_objects.push_back(okButton);
	
	counterFont = new CounterFont(CR::AssetList::Font_Score_1,0,0);
}

StoryModeScore::~StoryModeScore()
{
	scoreBaseSprite->Release();
	delete okButton;
	delete counterFont;
}

void StoryModeScore::Update()
{
}

void StoryModeScore::Render()
{
	scoreBaseSprite->Render();
	okButton->Render();
}

void StoryModeScore::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	scoreBaseSprite->SetPositionAbsolute(offset.X(), offset.Y());
}

void StoryModeScore::PauseAnimation(bool pause)
{
}

void StoryModeScore::OnOkButtonPressed()
{
	if(OnResumeGame.Size() > 0)
		OnResumeGame();
}