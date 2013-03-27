/*
 *  StarHUD.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/21/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StarHUD.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

StarHUD::StarHUD()
{
	Input_Button::Input_Button();
	SetSpriteAndBounds(0, 0, CR::AssetList::Star_HUD, 900);
	DesignSize(48, 57);

	starSprite = graphics_engine->CreateSprite1(true,800);
	starSprite->SetImage(CR::AssetList::Star_HUD_Animation);
	starSprite->SetDesignSize(29, 28);

	numberFont = new NumberFont(CR::AssetList::Font_StarHUD, 700);
	numberFont->SetDesignSize(10, 14);
	m_numStars = 0;
	
	maxTag = graphics_engine->CreateSprite1(false, 800);
	maxTag->SetImage(CR::AssetList::Max_Tag);
	maxTag->SetDesignSize(34, 21);

	maxedOut = false;
}

StarHUD::~StarHUD()
{
	starSprite->Release();
	maxTag->Release();
	delete numberFont;
}

void StarHUD::Update()
{	
	if (m_numStars > 0)
	{
		if (!starSprite->IsAnimating())
		{
			starSprite->SetAutoAnimate(true);
		}
	}
	else if (m_numStars == 0)
	{
		if (starSprite->IsAnimating())
		{
			starSprite->SetAutoAnimate(false);
			starSprite->SetFrame(0);
		}
	}
}

void StarHUD::Render()
{
	Input_Button::Render();
	starSprite->Render();
	
	if (maxedOut)
		maxTag->Render();
	else
		numberFont->RenderNumber(m_numStars);
}
void StarHUD::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	Input_Button::SetPosition(xLoc, yLoc);
	starSprite->SetPositionAbsolute(xLoc + 25, yLoc + 20);
	
	numberFont->SetPosition(xLoc + 30, yLoc + 43);
	maxTag->SetPositionAbsolute(xLoc + 25, yLoc + 46);
}

void StarHUD::PauseAnimation(bool pause)
{
	starSprite->PauseAnimation(pause);
}

void StarHUD::AddStar()
{
	//if (m_numStars < 90)
		m_numStars++;
}

void StarHUD::SetStars(int _value)
{
	m_numStars = _value;
}

int StarHUD::GetStars() const
{
	return m_numStars;
}