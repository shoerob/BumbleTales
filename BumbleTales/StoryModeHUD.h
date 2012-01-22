/*
 *  StoryModeHUD.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Point.h"
#include "ResourceBar.h"
#include "ResourceTile.h"
#include "IRenderable.h"
//#include "CounterFont.h"
#include "NumberFont.h"

class StoryModeHUD : public IRenderable
{
public:
	StoryModeHUD(int xLoc, int yLoc);
	virtual ~StoryModeHUD();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetLevel(int level);
	int GetLevel() { return m_currLevel; }
	
	void AddResources(ResourceType rType, int amount);
	bool ResourcesGathered();
	void PerformLevelUp();
	
	int GetResourceRequirement();
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *hudSprite;
	static const int resource_bars = 6;
	ResourceBar *resourceBars[resource_bars];
	//CounterFont *levelCounter;
	NumberFont *numberFont;
	int m_currLevel;
	
	void SetResourceRequirement(ResourceType rType, int amount);
	void ResetResourceBars();
};