/*
 *  TrophyButton.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "TrophyButton.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

TrophyButton::TrophyButton(TrophyName trophyName, int zPos) : m_touchID(-1)
{
	trophySprite = graphics_engine->CreateSprite1(true, zPos);
	trophySprite->SetImage(CR::AssetList::Scrapbook_Trophy_Icons);
	trophySprite->SetFrame((int)trophyName);
	
	SetPosition(0, 0);
	hasTrophy = false;
	this->trophyName = trophyName;
//	touch = NULL;
}

TrophyButton::~TrophyButton()
{
	trophySprite->Release();
}

void TrophyButton::Render()
{
	if (hasTrophy)
		trophySprite->Render();
}

void TrophyButton::SetPosition(int xLoc, int yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	trophySprite->SetPositionAbsolute(xLoc, yLoc);
	
	bounds.top = yLoc - trophySprite->GetFrameHeight() / 2;
	bounds.bottom = trophySprite->GetFrameHeight();
	bounds.left = xLoc - trophySprite->GetFrameWidth() / 2;
	bounds.right = trophySprite->GetFrameWidth();
}

void TrophyButton::SetHasTrophy(bool hasTrophy)
{
	this->hasTrophy = hasTrophy;
}

void TrophyButton::TouchesBeganImpl(Touch &_touches)
{
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
		OnClicked(trophyName);
	}
}

void TrophyButton::TouchesMovedImpl(Touch &_touches)
{
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
		OnClicked(trophyName);
	}
}

void TrophyButton::TouchesEndedImpl(Touch &_touches)
{
	if (_touches.ID == m_touchID)
	{
		m_touchID = -1;
	}
}

/*
void TrophyButton::TouchesBeganImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		CGPoint location = [touch locationInView: view];
		
		if (location.x > bounds.left && 
			location.x < bounds.right + bounds.left &&
			location.y > bounds.top &&
			location.y < bounds.bottom + bounds.top)
		{
			this->touch = touch;
			
			OnClicked(trophyName);
		}
	}
}

void TrophyButton::TouchesMovedImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		CGPoint location = [touch locationInView: view];
		
		if (location.x > bounds.left && 
			location.x < bounds.right + bounds.left &&
			location.y > bounds.top &&
			location.y < bounds.bottom + bounds.top)
		{
			this->touch = touch;
			
			OnClicked(trophyName);
		}
	}
}

void TrophyButton::TouchesEndedImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->touch = NULL;
			break;
		}
	}
}

void TrophyButton::TouchesCancelledImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->touch = NULL;
			break;
		}
	}
}*/