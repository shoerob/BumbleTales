/*
 *  StarMeter.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/10/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StarMeter.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

StarMeter::StarMeter() : m_spriteHelper(CR::AssetList::Shop_Star_Meter_Indicator, false, 300)
{
	m_spriteHelper.SetDesignSize(22, 21);

	meterSprite = graphics_engine->CreateSprite1(false,300);
	meterSprite->SetImage(CR::AssetList::Shop_Star_Meter);
	meterSprite->SetDesignSize(145, 38);

	m_starCount = 0;
	
	starSprite = graphics_engine->CreateSprite1(false,300);
	starSprite->SetImage(CR::AssetList::Shop_Star_Meter_Indicator);
	starSprite->SetDesignSize(22, 21);
	starSprite->SetFrameRate(10);
	starSprite->SetAutoAnimate(true);
	m_starIndicator = 0;
	//starSprite->SetFrameRate(30);
	//m_spriteHelper.SetFrameRate(5);
}

StarMeter::~StarMeter()
{
	meterSprite->Release();
	starSprite->Release();
}

// IRenderable
void StarMeter::Update()
{
}

void StarMeter::Render()
{
	meterSprite->Render();
	
	int availableStars = m_starIndicator;


	m_spriteHelper.Start();	
	for (int i = 0; i < 5; i++)
	{
		if (i >= m_starCount && availableStars > 0)
		{
			//starSprite->SetPositionAbsolute(offset.X() + 53 - (27 * i), offset.Y() - 3);
			//starSprite->Render();
			m_spriteHelper.NewSprite();
			m_spriteHelper.SetPosition(offset.X() + 53 - (26 * i), offset.Y() - 3);
			m_spriteHelper.SetFrame(starSprite->GetFrame());	
			
			availableStars--;
		}
	}
	m_spriteHelper.End();	
	
}


void StarMeter::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	meterSprite->SetPositionAbsolute(offset.X(), offset.Y());
}

void StarMeter::PauseAnimation(bool pause)
{
}

void StarMeter::SetFilledStars(int _value)
{
	if (_value == -1 || m_starCount == _value) return;
	
	m_starCount = _value;
	meterSprite->SetFrameSet(m_starCount);
}

void StarMeter::SetStarIndicator(int _value)
{
	m_starIndicator = _value;
}