/*
 *  PauseMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Input_Engine.h"
#include "Event.h"
#include "Point.h"
#include "IView.h"

class PauseMenuView : public IView
{
public:
	PauseMenuView();
	~PauseMenuView();
	
	// IView
	void Update();
	void Render();
	
	void OnResumeGameButtonPressed();
	void OnMainMenuButtonPressed();
	void OnHowToPlayButtonPressed();
	void OnOptionsButtonPressed();
	void OnScrapBookButtonPressed();
	
	Event OnResumeGameClicked;
	Event OnMainMenuClicked;
	Event OnHowToPlayClicked;
	Event OnOptionsClicked;
	Event OnScrapbookClicked;
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *pauseBackground;
	Input_Button *scrapBookButton;
	Input_Button *optionsButton;
	Input_Button *howToPlayButton;
	Input_Button *mainMenuButton;
	Input_Button *resumeGameButton;
};