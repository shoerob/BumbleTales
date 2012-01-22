/*
 *  StoryModeScoreView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryModeScoreView.h"
#include "AssetList.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;

StoryModeScoreView::StoryModeScoreView(StoryModeScoreData *scoreData) : m_spriteHelperMedals(CR::AssetList::Medal_Icons,true,400)
{
	this->m_scoreData = scoreData;
	
	scoreBaseSprite = graphics_engine->CreateSprite1(false,500);
	scoreBaseSprite->SetImage(CR::AssetList::Score_Base_1);
	scoreBaseSprite->SetPositionAbsolute(160, 240);
	
	medalIconsSprite = graphics_engine->CreateSprite1(false,400);
	medalIconsSprite->SetImage(CR::AssetList::Medal_Icons);
	
	okButton = new Input_Button();
	okButton->SetSpriteAndBounds(96, 400, CR::AssetList::Score_Ok_Button, 400);
	okButton->OnClicked += Delegate(this, &StoryModeScoreView::OnOkButtonPressed);
	okButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(okButton);
	
	//resourceCounter = new CounterFont(CR::AssetList::Font_Score_1,200,300);
	//resourceCounter->SetCount(0);
	
	//bigCounter = new CounterFont(CR::AssetList::Font_Score_2, 200, 300);
	//bigCounter->SetCount(0);
	smallNumberFont = new NumberFont(CR::AssetList::Font_Score_1, 400);
	smallNumberFont->SetAlignment(AlignFontRight);
	bigNumberFont = new NumberFont(CR::AssetList::Font_Score_2, 400);
	bigNumberFont->SetAlignment(AlignFontRight);
	
	timeDisplay = new TimeDisplay();
	timeDisplay->SetSeconds(scoreData->levelTime);
	
	youGotSlider = new YouGotSlider();
	youGotSlider->SetPosition(-105, 30);
	youGotSlider->SetSlideToPoint(110, 30);
	youGotSlider->SetTagDisplay(scoreData->gotTrophy, scoreData->gotStar);
}

StoryModeScoreView::~StoryModeScoreView()
{
	scoreBaseSprite->Release();
	medalIconsSprite->Release();
	delete okButton;
	//delete resourceCounter;
	//delete bigCounter;
	delete smallNumberFont;
	delete bigNumberFont;
	delete timeDisplay;
	delete youGotSlider;
}

// IView
void StoryModeScoreView::Update()
{
	//resourceCounter->Update();
	youGotSlider->Update();
}

void StoryModeScoreView::Render()
{
	scoreBaseSprite->Render();
	okButton->Render();
	
	smallNumberFont->Begin();
	bigNumberFont->Begin();
	
	m_spriteHelperMedals.Start();
	smallNumberFont->SetPosition(80, 144);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(Brick));
	RenderMedal(m_scoreData->tileMedals[Brick], 130, 144);
	
	smallNumberFont->SetPosition(80, 174);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(Wood));
	RenderMedal(m_scoreData->tileMedals[Wood], 130, 174);
	
	smallNumberFont->SetPosition(80, 204);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(Leaf));
	RenderMedal(m_scoreData->tileMedals[Leaf], 130, 204);
	
	// TODO: ? Resource Type
	smallNumberFont->SetPosition(80, 234);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(QTile));
	RenderMedal(m_scoreData->tileMedals[QTile], 130, 234);
	
	smallNumberFont->SetPosition(217, 144);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(Gold));
	RenderMedal(m_scoreData->tileMedals[Gold], 267, 144);
	
	smallNumberFont->SetPosition(217, 174);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(Crystal));
	RenderMedal(m_scoreData->tileMedals[Crystal], 267, 174);
	
	smallNumberFont->SetPosition(217, 204);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(Diamond));
	RenderMedal(m_scoreData->tileMedals[Diamond], 267, 204);
	
	// TODO: M Resource Type
	smallNumberFont->SetPosition(217, 234);
	smallNumberFont->RenderNumber(m_scoreData->GetResourceCount(MTile));
	RenderMedal(m_scoreData->tileMedals[MTile], 267, 234);
	
	bigNumberFont->SetPosition(245, 283);
	bigNumberFont->RenderNumber(m_scoreData->largestChain);
	RenderMedal(m_scoreData->chainMedal, 290, 283);
	
	bigNumberFont->SetPosition(245, 318);
	bigNumberFont->RenderNumber(m_scoreData->powersUsed);
	RenderMedal(m_scoreData->powersUsedMedal, 290, 318);
	
	timeDisplay->SetPosition(215, 358);
	timeDisplay->Render();
	RenderMedal(m_scoreData->levelTimeMedal, 290, 358);
	
	youGotSlider->Render();
	
	smallNumberFont->End();
	bigNumberFont->End();
	m_spriteHelperMedals.End();
}

void StoryModeScoreView::RenderMedal(MedalType mType, int xLoc, int yLoc)
{
	/*medalIconsSprite->SetFrameSet((int)mType);
	medalIconsSprite->SetPositionAbsolute(xLoc, yLoc);
	medalIconsSprite->Render();*/
	
	m_spriteHelperMedals.NewSprite();
	m_spriteHelperMedals.SetPosition(xLoc, yLoc);
	m_spriteHelperMedals.SetFrame((int)mType);
}

void StoryModeScoreView::OnOkButtonPressed()
{
	// Reset the score for the next level
	m_scoreData->Reset();
	
	if(OnResumeGameClicked.Size() > 0)
		OnResumeGameClicked();
}