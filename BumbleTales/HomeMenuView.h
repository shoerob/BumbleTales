/*
 *  HomeMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#include "Input_Engine.h"
#include "Event.h"
#include "Graphics.h"
#include "IView.h"

class HomeMenuView : public IView
{
public:
	HomeMenuView();
	~HomeMenuView();

	void Update();
	void Render();
	
	Event OnStartStoryMode;
	Event OnStartArcadeMode;
	Event OnShowOptionsMenu;
	Event OnShowHelpMenu;
	Event OnShowMoreGamesMenu;
	Event OnShowScrapbookMenu;
	
	// Delegate Methods
	void OnStoryModeClicked();
	void OnArcadeModeClicked();
	void OnScrapbookClicked();
	void OnHelpClicked();
	void OnOptionsClicked();
	void OnMoreGamesClicked();
	
private:
	CR::Graphics::Sprite *menuBackground;
	Input_Button *storyModeButton;
	Input_Button *arcadeModeButton;
	Input_Button *scrapbookButton;
	Input_Button *helpButton;
	Input_Button *optionsButton;
	Input_Button *moreGamesButton;
};