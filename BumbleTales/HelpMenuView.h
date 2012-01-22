/*
 *  HelpMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Input_Engine.h"
#include "Event.h"
#include "Graphics.h"
#include "ConfirmEraseDialog.h"
#include "IView.h"

enum HelpMenuScreenType { InfoHelpCredits, InfoHelp1, InfoHelp2, InfoHelp3, InfoHelp4 };

class HelpMenuView : public IView
{
public:
	HelpMenuView(bool showCredits);
	~HelpMenuView();
	
	void Update();
	void Render();
	
	Event OnExitClicked;
	
	// Delegate Methods
	void OnExitButtonClicked();
	void OnLeftClicked();
	void OnRightClicked();
	void OnHowToPlayClicked();
	
private:
	void SetScreen(HelpMenuScreenType screenType);
	
	bool showCredits;
	CR::Graphics::Sprite *menuBackground;
	Input_Button *exitButton;
	Input_Button *howToPlayButton;
	Input_Button *leftButton;
	Input_Button *rightButton;
	
	HelpMenuScreenType m_currScreen;
	CR::Graphics::Sprite *m_currScreenSprite;
};