/*
 *  PauseMenu.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#include "Graphics.h"
#include "Input_Engine.h"
#include "Event.h"
#include "Point.h"
#include "IRenderable.h"

class PauseMenu : public Input_Controller, public IRenderable
{
public:
	PauseMenu();
	~PauseMenu();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void OnResumeGameButtonPressed();
	void OnMainMenuButtonPressed();
	
	Event OnResumeGame;
	Event OnMainMenu;
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *pauseBackground;
	Input_Button *scrapBookButton;
	Input_Button *optionsButton;
	Input_Button *howToPlayButton;
	Input_Button *mainMenuButton;
	Input_Button *resumeGameButton;
};