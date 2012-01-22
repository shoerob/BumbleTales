/*
 *  ArcadeModeHUD.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "Graphics.h"
#include "Point.h"
#include "ResourceBar.h"
#include "ResourceTile.h"
#include "IRenderable.h"
#include "NumberFont.h"
#include "TimerBar.h"

class ArcadeModeHUD : public IRenderable
{
public:
	ArcadeModeHUD(int xLoc, int yLoc);
	virtual ~ArcadeModeHUD();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetLevel(int level);
	int GetLevel() { return m_currLevel; }
	
	void SetScore(int score);
	int GetScore() { return m_score; }
	void AddToScore(int _value) { m_score += _value; }
	
	void AddResources(ResourceType rType, int amount);
	bool ResourcesGathered();
	void PerformLevelUp();
	
	// TimerBar
	void OnTimerExpired();
	Event TimerExpired;
	float GetCurrTime() { return timerBar->GetCurrTime(); }
	
	void Reset();
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *hudSprite;
	static const int resource_bars = 6;
	ResourceBar *resourceBars[resource_bars];
	NumberFont *numberFont;
	NumberFont *scoreFont;
	TimerBar *timerBar;
	int m_currLevel;
	int m_score;
	
	void SetResourceRequirement(ResourceType rType, int amount);
	void ResetResourceBars();
};