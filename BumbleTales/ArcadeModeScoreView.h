/*
 *  ArcadeModeScoreView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/3/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "IView.h"
#include "Graphics.h"
#include "Input_Engine.h"
#include "Event.h"
//#include "ArcadeModeScoreInfo.h"
#include "ArcadeModeStructures.h"
#include "NumberFont.h"
#include "TimeDisplay.h"
#include "YouGotSlider.h"

class ArcadeModeScoreView : public IView
	{
	public:
		ArcadeModeScoreView(ArcadeModeScoreData *scoreData);
		virtual ~ArcadeModeScoreView();
		
		// IView
		void Update();
		void Render();
		
		//void OnOkButtonPressed();
		void OnYesButtonPressed();
		void OnNoButtonPressed();
		
		//Event OnResumeGameClicked;
		Event OnYesClicked;
		Event OnNoClicked;
		
	private:
		ArcadeModeScoreData *m_scoreData;
		CR::Graphics::Sprite *scoreBaseSprite;
		CR::Graphics::Sprite *finalScoreSprite;
		CR::Graphics::Sprite *highScoreSprite;
		YouGotSlider *youGotSlider;
		//Input_Button *okButton;
		Input_Button *yesButton;
		Input_Button *noButton;
		NumberFont *smallNumberFont;
		NumberFont *bigNumberFont;
		NumberFont *scoreNumberFont;
		TimeDisplay *timeDisplay;
	};