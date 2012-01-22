/*
 *  TimeDisplay.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/18/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "TimeDisplay.h"
#include "AssetList.h"

TimeDisplay::TimeDisplay()
{
	numberFont = new NumberFont(CR::AssetList::Font_Score_2, 400);
	numberFont->SetAlignment(AlignFontRight);
	colonFont = new NumberFont(CR::AssetList::Font_Score_2, 400);
	colonFont->SetAlignment(AlignFontRight);
	m_seconds = 0;
	SetPosition(0, 0);
}



TimeDisplay::~TimeDisplay()
{
	delete numberFont;
	delete colonFont;
}

void TimeDisplay::Update()
{

}

void TimeDisplay::Render()
{	
	numberFont->Begin();
	int minutes = m_seconds / 60;
	int seconds = m_seconds % 60;
	
	int xPos = offset.X();
	numberFont->SetMinDigits(0);
	numberFont->SetPosition(xPos, offset.Y());
	numberFont->RenderNumber(minutes);

	minutes = minutes / 10;
	xPos += numberFont->GetDigitWidth();
	while (minutes != 0)
	{
		minutes = minutes / 10;
		xPos += numberFont->GetDigitWidth();
	}

	colonFont->SetPosition(xPos, offset.Y());
	colonFont->RenderSpecial(11);
	xPos += numberFont->GetDigitWidth();
	numberFont->SetMinDigits(2);
	numberFont->SetPosition(xPos, offset.Y());
	numberFont->RenderNumber(seconds);
	numberFont->End();
}

void TimeDisplay::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
}

void TimeDisplay::PauseAnimation(bool pause)
{
}

void TimeDisplay::SetFontAsset(int _asset)
{
	numberFont->SetFontAsset(_asset);
	colonFont->SetFontAsset(_asset);
}