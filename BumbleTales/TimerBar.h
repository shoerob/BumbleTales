/*
 *  TimerBar.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "Point.h"
#include "Event.h"

class TimerBar
{
public:
	TimerBar(int xLoc, int yLoc);
	virtual ~TimerBar();
	
	//IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetMaxTime(float _value);
	void ResetTimer();
	void IncreaseTimer(float time);
	void DecreaseTimer(float time);
	
	float GetCurrTime() { return currTime; }
	
	Event TimerExpired;
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *timeSprite;
	CR::Graphics::Sprite *barSprite;
	
	float maxTime;
	float currTime;
};