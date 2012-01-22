/*
 *  StoryModeScoreView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "IView.h"
#include "Graphics.h"
#include "Input_Engine.h"
#include "Event.h"
#include "StoryModeScoreInfo.h"
#include "StoryModeStructures.h"
#include "NumberFont.h"
#include "TimeDisplay.h"
#include "YouGotSlider.h"

class StoryModeScoreView : public IView
{
public:
	StoryModeScoreView(StoryModeScoreData *scoreData);
	virtual ~StoryModeScoreView();
	
	// IView
	void Update();
	void Render();
	
	void OnOkButtonPressed();
	
	Event OnResumeGameClicked;
	
private:
	StoryModeScoreData *m_scoreData;
	CR::Graphics::Sprite *scoreBaseSprite;
	Input_Button *okButton;
	NumberFont *smallNumberFont;
	NumberFont *bigNumberFont;
	TimeDisplay *timeDisplay;
	YouGotSlider *youGotSlider;
	CR::Graphics::Sprite *medalIconsSprite;
	CR::Game::RepeatedSpriteHelper m_spriteHelperMedals;
	
	void RenderMedal(MedalType mType, int xLoc, int yLoc);
};