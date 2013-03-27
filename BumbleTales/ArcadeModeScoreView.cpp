/*
 *  ArcadeModeScoreView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/3/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ArcadeModeScoreView.h"
#include "AssetList.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;

ArcadeModeScoreView::ArcadeModeScoreView(ArcadeModeScoreData *scoreData)
{
	this->m_scoreData = scoreData;
	
	scoreBaseSprite = graphics_engine->CreateSprite1(false,500);
	scoreBaseSprite->SetImage(CR::AssetList::Score_Base_2);
	scoreBaseSprite->SetDesignSize(320, 480);
	scoreBaseSprite->SetPositionAbsolute(160, 240);
	
	finalScoreSprite = graphics_engine->CreateSprite1(false,400);
	finalScoreSprite->SetImage(CR::AssetList::Final_Score_Tag);
	finalScoreSprite->SetDesignSize(196, 42);
	finalScoreSprite->SetPositionAbsolute(160, 135);
	
	highScoreSprite = graphics_engine->CreateSprite1(false,400);
	highScoreSprite->SetImage(CR::AssetList::High_Score_Tag);
	highScoreSprite->SetDesignSize(250, 38);
	highScoreSprite->SetPositionAbsolute(160, 226);
		
	yesButton = new Input_Button();
	yesButton->SetSpriteAndBounds(96, 400, CR::AssetList::Score_Yes_Button, 400);
	yesButton->DesignSize(108, 65);
	yesButton->OnClicked += Delegate(this, &ArcadeModeScoreView::OnYesButtonPressed);
	yesButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(yesButton);
	
	noButton = new Input_Button();
	noButton->SetSpriteAndBounds(208, 400, CR::AssetList::Score_No_Button, 400);
	noButton->DesignSize(109, 65);
	noButton->OnClicked += Delegate(this, &ArcadeModeScoreView::OnNoButtonPressed);
	noButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(noButton);
	
	smallNumberFont = new NumberFont(CR::AssetList::Font_Score_1, 400);
	smallNumberFont->SetDesignSize(12, 16);
	smallNumberFont->SetAlignment(AlignFontRight);
	bigNumberFont = new NumberFont(CR::AssetList::Font_Score_2, 400);
	bigNumberFont->SetDesignSize(16, 20);
	bigNumberFont->SetAlignment(AlignFontRight);
	scoreNumberFont = new NumberFont(CR::AssetList::Font_Score_3, 400);
	scoreNumberFont->SetDesignSize(43, 50);
	scoreNumberFont->SetAlignment(AlignFontCenter);
	
	timeDisplay = new TimeDisplay();
	timeDisplay->SetSeconds(scoreData->levelTime);
	
	youGotSlider = new YouGotSlider();
	youGotSlider->SetPosition(-105, 30);
	youGotSlider->SetSlideToPoint(110, 30);
	youGotSlider->SetTagDisplay(scoreData->gotTrophy, false);
	//youGotSlider->SetTagDisplay(true, true);
	
	if (scoreData->newHighScore)
	{
		std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
		sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::arcadehigh1a::ID);
		sound->Play();
	}
	else
	{
		std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
		sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::arcadeover1a::ID);
		sound->Play();
	}
}

ArcadeModeScoreView::~ArcadeModeScoreView()
{
	scoreBaseSprite->Release();
	finalScoreSprite->Release();
	highScoreSprite->Release();
	delete yesButton;
	delete noButton;
	delete smallNumberFont;
	delete bigNumberFont;
	delete scoreNumberFont;
	delete timeDisplay;
	delete youGotSlider;
}

void ArcadeModeScoreView::Update()
{
	youGotSlider->Update();
}

void ArcadeModeScoreView::Render()
{
	scoreBaseSprite->Render();
	yesButton->Render();
	noButton->Render();
	
	finalScoreSprite->Render();
	
	if (m_scoreData->newHighScore)
		highScoreSprite->Render();
	
	bigNumberFont->Begin();
	bigNumberFont->SetPosition(240, 267);
	bigNumberFont->RenderNumber(m_scoreData->largestChain);
	
	bigNumberFont->SetPosition(240, 330);
	bigNumberFont->RenderNumber(m_scoreData->level);
	
	bigNumberFont->SetPosition(240, 299);
	bigNumberFont->RenderNumber(m_scoreData->powersUsed);
	bigNumberFont->End();
	
	scoreNumberFont->SetPosition(180, 180);
	scoreNumberFont->RenderNumber(m_scoreData->score);
	
	timeDisplay->SetPosition(227, 361);
	timeDisplay->Render();
	
	youGotSlider->Render();
}

/*void ArcadeModeScoreView::OnOkButtonPressed()
{
	// Reset the score for the next level
	m_scoreData->Reset();
	
	if(OnResumeGameClicked.Size() > 0)
		OnResumeGameClicked();
}*/

void ArcadeModeScoreView::OnYesButtonPressed()
{
	// Reset the score for the next level
	//m_scoreData->Reset();
	
	if(OnYesClicked.Size() > 0)
		OnYesClicked();
}

void ArcadeModeScoreView::OnNoButtonPressed()
{
	// Reset the score for the next level
	//m_scoreData->Reset();
	
	if(OnNoClicked.Size() > 0)
		OnNoClicked();
}