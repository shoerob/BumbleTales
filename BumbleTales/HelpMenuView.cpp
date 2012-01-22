/*
 *  HelpMenuView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "HelpMenuView.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;

HelpMenuView::HelpMenuView(bool showCredits)
{
	exitButton = new Input_Button();
	exitButton->OnClicked += Delegate(this, &HelpMenuView::OnExitButtonClicked);
	exitButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(exitButton);
	
	howToPlayButton = new Input_Button();
	howToPlayButton->OnClicked += Delegate(this, &HelpMenuView::OnHowToPlayClicked);
	howToPlayButton->SetSpriteAndBounds(161, 432, CR::AssetList::InfoHelp_How_to_Play_Button, 400);
	howToPlayButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(howToPlayButton);
	
	leftButton = new Input_Button();
	leftButton->OnClicked += Delegate(this, &HelpMenuView::OnLeftClicked);
	leftButton->SetSpriteAndBounds(2, 432, CR::AssetList::Scrapbook_LArrow_Button, 400);
	leftButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(leftButton);
	
	rightButton = new Input_Button();
	rightButton->OnClicked += Delegate(this, &HelpMenuView::OnRightClicked);
	rightButton->SetSpriteAndBounds(221, 432, CR::AssetList::Scrapbook_RArrow_Button, 400);
	rightButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(rightButton);
	
	menuBackground = graphics_engine->CreateSprite1(false,500);
	menuBackground->SetImage(CR::AssetList::InfoHelp_Background);
	menuBackground->SetPositionAbsolute(160, 240);
	
	m_currScreenSprite = graphics_engine->CreateSprite1(false,400);
	
	if (showCredits)
		SetScreen(InfoHelpCredits);
	else
		SetScreen(InfoHelp1);
}

HelpMenuView::~HelpMenuView()
{
	delete exitButton;
	delete leftButton;
	delete rightButton;
	delete howToPlayButton;
	
	menuBackground->Release();
	m_currScreenSprite->Release();
}

void HelpMenuView::Update()
{
}

void HelpMenuView::Render()
{
	graphics_engine->BeginFrame();
	
	menuBackground->Render();
	m_currScreenSprite->Render();
	exitButton->Render();
	
	if (m_currScreen == InfoHelpCredits)
	{
		howToPlayButton->Render();
	}
	else
	{
		if (m_currScreen != InfoHelp1)
			leftButton->Render();
		
		if (m_currScreen != InfoHelp4)
			rightButton->Render();
	}
	
	
	graphics_engine->EndFrame();
}

void HelpMenuView::SetScreen(HelpMenuScreenType screenType)
{
	m_currScreen = screenType;
	
	// Screen Backdrop
	switch (screenType)
	{
		case InfoHelpCredits:
			m_currScreenSprite->SetImage(CR::AssetList::InfoHelp_Credits);
			break;
		case InfoHelp1:
			m_currScreenSprite->SetImage(CR::AssetList::InfoHelp_Help1);
			break;
		case InfoHelp2:
			m_currScreenSprite->SetImage(CR::AssetList::InfoHelp_Help2);
			break;
		case InfoHelp3:
			m_currScreenSprite->SetImage(CR::AssetList::InfoHelp_Help3);
			break;
		case InfoHelp4:
			m_currScreenSprite->SetImage(CR::AssetList::InfoHelp_Help4);
			break;
		default:
			break;
	}
	
	// Screen Buttons
	if (screenType == InfoHelpCredits)
	{
		howToPlayButton->Disabled(false);
		rightButton->Disabled(true);
		leftButton->Disabled(true);
		exitButton->SetSpriteAndBounds(2, 432, CR::AssetList::InfoHelp_Main_Menu_Button, 400);
		m_currScreenSprite->SetPositionAbsolute(158, 213);
	}
	else
	{
		howToPlayButton->Disabled(true);
		
		if (screenType == InfoHelp1)
			leftButton->Disabled(true);			
		else
			leftButton->Disabled(false);
		
		if (screenType == InfoHelp4)
			rightButton->Disabled(true);
		else
			rightButton->Disabled(false);

		exitButton->SetSpriteAndBounds(112, 432, CR::AssetList::Scrapbook_Exit_Button, 400);
		m_currScreenSprite->SetPositionAbsolute(156, 213);
	}
}

void HelpMenuView::OnExitButtonClicked()
{
	OnExitClicked();
}

void HelpMenuView::OnHowToPlayClicked()
{
	SetScreen(InfoHelp1);
}

void HelpMenuView::OnLeftClicked()
{
	SetScreen((HelpMenuScreenType)((int)m_currScreen - 1));
}

void HelpMenuView::OnRightClicked()
{
	SetScreen((HelpMenuScreenType)((int)m_currScreen + 1));
}