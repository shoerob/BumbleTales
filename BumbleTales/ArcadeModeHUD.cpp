/*
 *  ArcadeModeHUD.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ArcadeModeHUD.h"
#include "AssetList.h"
#include "Globals.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ArcadeModeHUD::ArcadeModeHUD(int xLoc, int yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	hudSprite = graphics_engine->CreateSprite1(false, 900);
	hudSprite->SetImage(CR::AssetList::Arcade_Mode_HUD);
	hudSprite->SetPositionAbsolute(offset.X(), offset.Y());
	
	timerBar = new TimerBar(xLoc - 108, yLoc);
	timerBar->TimerExpired += Delegate(this, &ArcadeModeHUD::OnTimerExpired);
	
	// Create resource bars
	resourceBars[Brick] = new ResourceBar(offset.X() - 32, offset.Y() - 16, TinyResourceBar);
	resourceBars[Gold] = new ResourceBar(offset.X()  - 3, offset.Y() - 16, TinyResourceBar);
	resourceBars[Wood] = new ResourceBar(offset.X() + 27, offset.Y() - 16, TinyResourceBar);
	resourceBars[Crystal] = new ResourceBar(offset.X() + 56, offset.Y() - 16, TinyResourceBar);
	resourceBars[Leaf] = new ResourceBar(offset.X() + 85, offset.Y() - 16, TinyResourceBar);
	resourceBars[Diamond] = new ResourceBar(offset.X() + 114, offset.Y() - 16, TinyResourceBar);
	
	// Create level counter
	numberFont = new NumberFont(CR::AssetList::Arcade_Mode_Font_Level2, 800);
	numberFont->SetPosition(offset.X() - 71, offset.Y() - 17);
	
	scoreFont = new NumberFont(CR::AssetList::Arcade_Mode_Font_HUDScore, 800);
	scoreFont->SetPosition(offset.X() - 40, offset.Y() + 15);
	scoreFont->SetAlignment(AlignFontRight);
	m_currLevel = 1;
	m_score = 0;
}

ArcadeModeHUD::~ArcadeModeHUD()
{
	hudSprite->Release();
	delete numberFont;
	delete timerBar;
	
	for (int i = 0; i < resource_bars; i++)
		delete resourceBars[i];
}

void ArcadeModeHUD::Update()
{
	timerBar->Update();
	
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->Update();
	}
	
	timerBar->DecreaseTimer(Globals::Instance().GetTimer()->GetTimePassed());
}

void ArcadeModeHUD::Render()
{
	hudSprite->Render();
	numberFont->RenderNumber(m_currLevel);
	scoreFont->RenderNumber(m_score);
	timerBar->Render();
	
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->Render();
	}
}

void ArcadeModeHUD::PauseAnimation(bool pause)
{
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->PauseAnimation(pause);
	}
}

void ArcadeModeHUD::ResetResourceBars()
{
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->ResetValue();
	}
}

void ArcadeModeHUD::SetResourceRequirement(ResourceType rType, int amount)
{
	if ((int)rType > 5)
		return;
	
	resourceBars[rType]->SetMaxValue(amount);
}

void ArcadeModeHUD::AddResources(ResourceType rType, int amount)
{
	if ((int)rType > 5)
		return;
	
	timerBar->IncreaseTimer(amount * .3);
	
	resourceBars[rType]->AddToCurrValue(amount);
}

bool ArcadeModeHUD::ResourcesGathered()
{
	for (int i = 0; i < resource_bars; i++)
		if (resourceBars[i]->IsFull() == false) return false;
	
	return true;
}

void ArcadeModeHUD::PerformLevelUp()
{
	SetLevel(m_currLevel + 1);
	ResetResourceBars();
	timerBar->ResetTimer();
}

void ArcadeModeHUD::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
}

void ArcadeModeHUD::SetScore(int score)
{
	m_score = score;
}

void ArcadeModeHUD::SetLevel(int level)
{
	m_currLevel = level;
	
	int baseResourceRequirement = 3;
	for (int i = 0; i < 6; i++)
		SetResourceRequirement((ResourceType)i, baseResourceRequirement + level - 1);
	
	// Speed up the timer based on the level
	int baseTime = 30;
	for (int i = 0; i < level; i++)
	{
		baseTime = baseTime * .98;
				//baseTime = baseTime * .38;
	}
	
	// 10 seconds minimum
	if (baseTime < 10)
		baseTime = 10;
	
	timerBar->SetMaxTime(baseTime);
}

void ArcadeModeHUD::OnTimerExpired()
{
	TimerExpired();
	//timerBar->ResetTimer();
}

void ArcadeModeHUD::Reset()
{
	timerBar->ResetTimer();
	m_currLevel = 1;
	SetLevel(m_currLevel);
	m_score = 0;
	
	
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->ResetValue();
	}
}