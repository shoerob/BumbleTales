/*
 *  YouGotSlider.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "Globals.h"

class YouGotSlider
{
public:
	YouGotSlider();
	virtual ~YouGotSlider();
	
	void Update();
	void Render();
	
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetTagDisplay(bool gotTrophy, bool gotStar);
	void SetSlideToPoint(int xLoc, int yLoc);
	
private:
	CR::Math::PointF offset;
	CR::Math::PointF slideToPoint;
	
	CR::Graphics::Sprite *youGotTagsSprite;
	
	bool m_gotTrophy;
	bool m_gotStar;
	
	float maxDisplayDelay;
	float currDisplayDelay;
	int currTagDisplay;
	
	int xStep;
	bool sliding;
};