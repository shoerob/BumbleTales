/*
 *  OptionsMenuView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "OptionsMenuView.h"
#include "AssetList.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;

OptionsMenuView::OptionsMenuView(bool allowEraseData)
{
	eraseDataVisible = allowEraseData;
	
	exitButton = new Input_Button();
	exitButton->SetSpriteAndBounds(51, 420, CR::AssetList::Options_Exit_Button, 400);
	exitButton->OnClicked += Delegate(this, &OptionsMenuView::OnExitButtonClicked);
	exitButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(exitButton);
	
	headerSprite = graphics_engine->CreateSprite1(false,400);
	headerSprite->SetImage(CR::AssetList::Options_Header);
	headerSprite->SetPositionAbsolute(160, 48);
	
	eraseDataButton = NULL;
	if (eraseDataVisible)
	{
		eraseDataButton = new Input_Button();
		eraseDataButton->SetSpriteAndBounds(202, 8, CR::AssetList::Options_Erase_Data_Button, 400);
		eraseDataButton->OnClicked += Delegate(this, &OptionsMenuView::OnEraseDataButtonClicked);
		eraseDataButton->SetSound(CR::AssetList::sounds::shopopen::ID);
		input_objects.push_back(eraseDataButton);
		headerSprite->SetPositionAbsolute(105, 48);
	}
	
	menuBackground = graphics_engine->CreateSprite1(false,500);
	menuBackground->SetImage(CR::AssetList::Options_Base);
	menuBackground->SetPositionAbsolute(160, 240);
	
	confirmEraseDialog = new ConfirmEraseDialog();
	confirmEraseDialog->OnYes += Delegate(this, &OptionsMenuView::OnConfirmEraseYes);
	confirmEraseDialog->OnNo += Delegate(this, &OptionsMenuView::OnConfirmEraseNo);
	m_RenderConfirmEraseDialog = false;
	
	// Checkboxes
	hintsCheckbox = new CheckboxControl();
	hintsCheckbox->SetSpriteAndPosition(CR::AssetList::Options_Check, 47, 90);
	hintsCheckbox->SetButtonBounds(30, 102, 70, 70);
	//hintsCheckbox->SetSpriteAndBounds(47, 90, CR::AssetList::Options_Check);
	input_objects.push_back(hintsCheckbox);
	
	musicCheckbox = new CheckboxControl();
	musicCheckbox->SetSpriteAndPosition(CR::AssetList::Options_Check, 47, 194);
	musicCheckbox->SetButtonBounds(30, 207, 70, 70);
	musicCheckbox->OnCheckChanged += Delegate(this, &OptionsMenuView::OnMusicToggled);
	//musicCheckbox->SetSpriteAndBounds(47, 194, CR::AssetList::Options_Check);
	input_objects.push_back(musicCheckbox);
	
	soundCheckbox = new CheckboxControl();
	soundCheckbox->SetSpriteAndPosition(CR::AssetList::Options_Check, 47, 300);
	soundCheckbox->SetButtonBounds(30, 313, 70, 70);
	soundCheckbox->OnCheckChanged += Delegate(this, &OptionsMenuView::OnSoundToggled);
	//soundCheckbox->SetSpriteAndBounds(47, 300, CR::AssetList::Options_Check);
	input_objects.push_back(soundCheckbox);
}

OptionsMenuView::~OptionsMenuView()
{
	if (eraseDataButton != NULL)
		delete eraseDataButton;
	
	if (confirmEraseDialog != NULL)
		delete confirmEraseDialog;
	
	delete hintsCheckbox;
	delete musicCheckbox;
	delete soundCheckbox;
	delete exitButton;
	menuBackground->Release();
	headerSprite->Release();
}

void OptionsMenuView::Update()
{
}

void OptionsMenuView::Render()
{
	graphics_engine->BeginFrame();
	menuBackground->Render();
	headerSprite->Render();
	hintsCheckbox->Render();
	musicCheckbox->Render();
	soundCheckbox->Render();
	exitButton->Render();
	
	if (eraseDataButton != NULL)
		eraseDataButton->Render();
	
	if (m_RenderConfirmEraseDialog)
		confirmEraseDialog->Render();
	
	graphics_engine->EndFrame();
}

void OptionsMenuView::LoadFromSaveInfo(SettingsSaveInfo *saveInfo)
{
	hintsCheckbox->SetChecked(saveInfo->GetOptionsHintsOn());
	musicCheckbox->SetChecked(saveInfo->GetOptionsMusicOn());
	soundCheckbox->SetChecked(saveInfo->GetOptionsSoundOn());
}

void OptionsMenuView::WriteToSaveInfo(SettingsSaveInfo *saveInfo)
{
	saveInfo->SetOptionsHintsOn(hintsCheckbox->IsChecked());
	saveInfo->SetOptionsMusicOn(musicCheckbox->IsChecked());
	saveInfo->SetOptionsSoundOn(soundCheckbox->IsChecked());
}

void OptionsMenuView::OnExitButtonClicked()
{
	OnExitClicked();
}

void OptionsMenuView::OnEraseDataButtonClicked()
{
	input_engine->RegisterInputController(confirmEraseDialog);
	m_RenderConfirmEraseDialog = true;
}

void OptionsMenuView::OnConfirmEraseYes()
{
	m_RenderConfirmEraseDialog = false;
	OnEraseData();
	input_engine->RegisterInputController(this);
	
	OnMusicToggled();
	OnSoundToggled();
}

void OptionsMenuView::OnConfirmEraseNo()
{
	m_RenderConfirmEraseDialog = false;
	input_engine->RegisterInputController(this);
}

void OptionsMenuView::OnMusicToggled()
{
	ISound::Instance().MuteMusic(!musicCheckbox->IsChecked());
}

void OptionsMenuView::OnSoundToggled()
{
	ISound::Instance().MuteSounds(!soundCheckbox->IsChecked());
}
