/*
 *  ConfirmEraseDialog.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ConfirmEraseDialog.h"
#include "AssetList.h"
#include "SaveGameManager.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ConfirmEraseDialog::ConfirmEraseDialog()
{
	confirmEraseSprite = graphics_engine->CreateSprite1(false,300);
	confirmEraseSprite->SetImage(CR::AssetList::Options_Confirm_Erase);
	confirmEraseSprite->SetDesignSize(320, 480);
	//confirmEraseSprite->Visible(false);
	
	yesButton = new Input_Button();
	yesButton->SetSpriteAndBounds(0, 0, CR::AssetList::Options_Yes_Button, 200);
	yesButton->DesignSize(128, 99);
	yesButton->OnClicked += Delegate(this, &ConfirmEraseDialog::OnYesClicked);
	yesButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(yesButton);
	
	noButton = new Input_Button();
	noButton->SetSpriteAndBounds(0, 0, CR::AssetList::Options_No_Button, 200);
	noButton->DesignSize(129, 99);
	noButton->OnClicked += Delegate(this, &ConfirmEraseDialog::OnNoClicked);
	noButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(noButton);
	
	SetPosition(160, 240);
}

ConfirmEraseDialog::~ConfirmEraseDialog()
{
}

//IRenderable
void ConfirmEraseDialog::Update()
{
}

void ConfirmEraseDialog::Render()
{
	confirmEraseSprite->Render();
	yesButton->Render();
	noButton->Render();
}

void ConfirmEraseDialog::SetPosition(float xLoc, float yLoc)
{
	confirmEraseSprite->SetPositionAbsolute(xLoc, yLoc);
	yesButton->SetPosition(xLoc - 135, yLoc + 5);
	noButton->SetPosition(xLoc + 8, yLoc + 5);
}

void ConfirmEraseDialog::PauseAnimation(bool pause)
{
}

void ConfirmEraseDialog::OnYesClicked()
{
	OnYes();
	//OnCloseDialog();
}

void ConfirmEraseDialog::OnNoClicked()
{
	OnNo();
	//OnCloseDialog();
}