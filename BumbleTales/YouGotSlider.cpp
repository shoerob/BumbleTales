/*
 *  YouGotSlider.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "YouGotSlider.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

YouGotSlider::YouGotSlider()
{
	youGotTagsSprite = graphics_engine->CreateSprite1(false,400);
	youGotTagsSprite->SetImage(CR::AssetList::You_Got_Tags);
	
	m_gotTrophy = false;
	m_gotStar = false;
	
	SetPosition(0, 0);
	
	maxDisplayDelay = 1.5;
	currDisplayDelay = maxDisplayDelay;
	
	currTagDisplay = 0;
	xStep = 0;
	sliding = false;
}

YouGotSlider::~YouGotSlider()
{
}

void YouGotSlider::Update()
{
	if (m_gotTrophy && m_gotStar)
	{
		currDisplayDelay -= Globals::Instance().GetTimer()->GetTimePassed();
		
		if (currDisplayDelay <= 0)
		{
			currDisplayDelay = maxDisplayDelay;
			if (currTagDisplay == 1)
				currTagDisplay = 0;
			else
				currTagDisplay = 1;
		}
	}
	
	youGotTagsSprite->SetFrameSet(currTagDisplay);
	
	if (sliding)
	{
		SetPosition(offset.X() + xStep, offset.Y());
		if (offset.X() >= slideToPoint.X())
		{
			SetPosition(slideToPoint.X(), offset.Y());
			sliding = false;
		}
	}
}

void YouGotSlider::Render()
{
	if (m_gotTrophy || m_gotStar)
		youGotTagsSprite->Render();
}

void YouGotSlider::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	youGotTagsSprite->SetPositionAbsolute(offset.X(), offset.Y());
}

void YouGotSlider::PauseAnimation(bool pause)
{
}

void YouGotSlider::SetTagDisplay(bool gotTrophy, bool gotStar)
{
	m_gotTrophy = gotTrophy;
	m_gotStar = gotStar;
	
	if (m_gotTrophy && !m_gotStar)
	{
		currTagDisplay = 1;
	}
	else if (!m_gotTrophy && m_gotStar)
	{
		currTagDisplay = 0;
	}
}

void YouGotSlider::SetSlideToPoint(int xLoc, int yLoc)
{
	slideToPoint.X(xLoc);
	slideToPoint.Y(yLoc);
	
	sliding = true;
	xStep = (slideToPoint.X() - offset.X()) / 20;
}