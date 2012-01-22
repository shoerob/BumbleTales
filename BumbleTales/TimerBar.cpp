/*
 *  TimerBar.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "TimerBar.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

TimerBar::TimerBar(int xLoc, int yLoc)
{
	timeSprite = graphics_engine->CreateSprite1(false,800);
	timeSprite->SetImage(CR::AssetList::Arcade_Mode_Time_Tag);
	
	barSprite = graphics_engine->CreateSprite1(true,800);
	barSprite->SetImage(CR::AssetList::Arcade_Mode_Time_Bar);
	
	maxTime = 30;
	currTime = maxTime;
	
	SetPosition(xLoc, yLoc);
}

TimerBar::~TimerBar()
{
	timeSprite->Release();
	barSprite->Release();
}

void TimerBar::Update()
{
	float frame = (1 - ((float)currTime / (float) maxTime)) * 52.0;
	barSprite->SetFrame(frame);
}

void TimerBar::Render()
{
	timeSprite->Render();
	barSprite->Render();
}

void TimerBar::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	timeSprite->SetPositionAbsolute(xLoc, yLoc);
	barSprite->SetPositionAbsolute(xLoc + 123, yLoc);
}

void TimerBar::PauseAnimation(bool pause)
{
	
}

void TimerBar::SetMaxTime(float _value)
{
	maxTime = _value;
	
	if (currTime > maxTime)
		currTime = maxTime;
}

void TimerBar::ResetTimer()
{
	currTime = maxTime;
}

void TimerBar::IncreaseTimer(float time)
{
	currTime += time;
	if (currTime >= maxTime)
		currTime = maxTime;
}

void TimerBar::DecreaseTimer(float time)
{
	currTime -= time;
	
	if (currTime <= 0)
	{
		currTime = 0;
		TimerExpired();
	}
}