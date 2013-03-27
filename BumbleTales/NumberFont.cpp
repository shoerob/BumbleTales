/*
 *  NumberFont.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/15/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "NumberFont.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

NumberFont::NumberFont(int fontAsset, int zPos) : m_spriteHelper(fontAsset,true,zPos), m_helperLock(false)
{
	numberSprite = graphics_engine->CreateSprite1(true,zPos);
	numberSprite->SetImage(fontAsset);
	m_minDigits = 0;
	SetPosition(0, 0);
	m_align = AlignFontCenter;
}

NumberFont::~NumberFont()
{
	numberSprite->Release();
}

void NumberFont::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
}

void NumberFont::Begin()
{
	m_spriteHelper.Start();	
	m_helperLock = true;
}

void NumberFont::End()
{	
	m_spriteHelper.End();	
	m_helperLock = false;
}

void NumberFont::RenderNumber(int _value)
{	
	if(!m_helperLock)
		m_spriteHelper.Start();	
	
	stack<int> digits;
	
	int cValue = _value;
	
	while (cValue != 0)
	{
		int digit = cValue % 10;
		cValue = cValue / 10;
		digits.push(digit);
	}
	
	while (digits.size() < m_minDigits)
	{
		digits.push(0);
	}
	
	int xPos = 0;
	if (m_align == AlignFontCenter)
	{
		if (digits.size() > 0)
			xPos = offset.X() - ((digits.size() * numberSprite->DesignWidth())/2);
		else
			xPos = offset.X() - (numberSprite->DesignWidth())/2;
	}
	else if (m_align == AlignFontRight)
	{
		xPos = offset.X();// - ((digits.size() * numberSprite->GetFrameWidth())/2);
	}
	else if (m_align = AlignFontLeft)
	{
		if (digits.size() > 0)
			xPos = offset.X() - ((digits.size() * numberSprite->DesignWidth()));
		else
			xPos = offset.X() - (numberSprite->DesignWidth());
	}
	
	if (digits.size() == 0)
	{
		m_spriteHelper.NewSprite();
		m_spriteHelper.SetPosition(xPos, offset.Y());
		m_spriteHelper.SetFrame(0);
		//numberSprite->SetPositionAbsolute(xPos, offset.Y());
		//numberSprite->SetFrame(0);
		//numberSprite->Render();
	}
	
	while (digits.size() > 0)
	{
		int digit = digits.top();
		digits.pop();
		
		m_spriteHelper.NewSprite();
		m_spriteHelper.SetPosition(xPos, offset.Y());
		m_spriteHelper.SetFrame(digit);
		//numberSprite->SetPositionAbsolute(xPos, offset.Y());
		//numberSprite->SetFrame(digit);
		//numberSprite->Render();
		
		xPos += numberSprite->DesignWidth();
	}
	if(!m_helperLock)
		m_spriteHelper.End();	
}

/*void NumberFont::RenderBigNumber(int64_t _value)
{
	stack<int> digits;
	
	int64_t cValue = _value;
	
	while (cValue != 0)
	{
		int digit = cValue % 10;
		cValue = cValue / 10;
		digits.push(digit);
	}
	
	while (digits.size() < m_minDigits)
	{
		digits.push(0);
	}
	
	int xPos = 0;
	if (m_align == AlignFontCenter)
	{
		if (digits.size() > 0)
			xPos = offset.X() - ((digits.size() * numberSprite->GetFrameWidth())/2);
		else
			xPos = offset.X() - (numberSprite->GetFrameWidth())/2;
	}
	else if (m_align == AlignFontRight)
	{
		xPos = offset.X();// - ((digits.size() * numberSprite->GetFrameWidth())/2);
	}
	
	if (digits.size() == 0)
	{
		numberSprite->SetPositionAbsolute(xPos, offset.Y());
		numberSprite->SetFrame(0);
		numberSprite->Render();
	}
	
	while (digits.size() > 0)
	{
		int digit = digits.top();
		digits.pop();
		
		numberSprite->SetPositionAbsolute(xPos, offset.Y());
		numberSprite->SetFrame(digit);
		numberSprite->Render();
		
		xPos += numberSprite->GetFrameWidth();
	}	
}
*/

void NumberFont::RenderSpecial(int _frame)
{
	numberSprite->SetPositionAbsolute(offset.X(), offset.Y());
	numberSprite->SetFrame(_frame);
	numberSprite->Render();
}

void NumberFont::SetMinDigits(int _value)
{
	m_minDigits = _value;
}

int NumberFont::GetMinDigits() const
{
	return m_minDigits;
}

void NumberFont::SetAlignment(FontAlignment _value)
{
	m_align = _value;
}

void NumberFont::SetFontAsset(int _asset)
{
	numberSprite->SetImage(_asset);
	m_spriteHelper.SetImage(_asset);
}

void NumberFont::SetDesignSize(int _width, int _height)
{
	numberSprite->SetDesignSize(_width, _height);
	m_spriteHelper.SetDesignSize(_width, _height);
}