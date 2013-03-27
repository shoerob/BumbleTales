/*
 *  CounterFont.cpp
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/18/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CounterFont.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

CounterFont::CounterFont(int fontAsset, int xLoc, int yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	m_count = 1;
	numberFont = graphics_engine->CreateSprite1(true,800);
	numberFont->SetImage(fontAsset);
	
	for (int i = 0; i < 3; i++)
		digits[i] = 0;
	
	UpdateDigits();
	
	m_maxDigits = 3;
}

CounterFont::~CounterFont()
{
	numberFont->Release();
}

void CounterFont::Update()
{	

}

void CounterFont::Render()
{
	int dSign = -1;
	
	for (int i = 0; i < 3; i++)
		//for (int i = 0; i < m_maxDigits; i++)
	{
		numberFont->SetFrame(digits[i]);
		numberFont->SetPositionAbsolute(offset.X() + (dSign * numberFont->GetFrameWidth()) + (3 * dSign), offset.Y());
		numberFont->Render();
		
		dSign++;
	}
}

void CounterFont::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
}

void CounterFont::SetCount(int cnt)
{
	m_count = cnt;
	UpdateDigits();
}

/*void CounterFont::operator++()
{
	m_count++;
	UpdateDigits();
}
*/
void CounterFont::SetMaxDigits(int _value)
{
	m_maxDigits = _value;
}

void CounterFont::UpdateDigits()
{
	// change to divide and shift
	int mNum = m_count;
	int currDigit = 2;
	for (int i = 0; i < 3; i++)
		digits[i] = 0;
	
	// 999 is the maximum displayable number
	if (m_count <= 999)
	{
		while (mNum != 0)
		{
			digits[currDigit] = mNum % 10;
			mNum = mNum / 10;
			
			currDigit--;
		}
	}
	else // set the digits to 0, a * will be used in their place
	{
		for (int i = 0; i < 3; i++)
			digits[i] = 0;
	}
}

void CounterFont::SetDesignSize(int _width, int _height)
{
	numberFont->SetDesignSize(_width, _height);
}