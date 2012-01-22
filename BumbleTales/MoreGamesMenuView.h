/*
 *  MoreGamesMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Input_Engine.h"
#include "Graphics.h"
#include "IView.h"

class MoreGamesMenuView : public IView
{
public:
	MoreGamesMenuView();
	virtual ~MoreGamesMenuView();
	
	void Update();
	void Render();
	
	Event OnExitClicked;
	
	void OnExitButtonClicked();
	void OnBoBClicked();
	void OnAFTBClicked();
	void OnDOHClicked();
	
private:
	CR::Graphics::Sprite *menuBackground;
	CR::Graphics::Sprite *titleSprite;
	Input_Button *exitButton;
	Input_Button *BoBButton;
	Input_Button *AFTBButton;
	Input_Button *DOHButton;
};