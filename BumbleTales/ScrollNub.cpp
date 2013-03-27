/*
 *  ScrollNub.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/8/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ScrollNub.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ScrollNub::ScrollNub(int xLoc, int yLoc, int yRange) : m_touchID(-1)
{
	nubSprite = graphics_engine->CreateSprite1(false,400);
	nubSprite->SetImage(CR::AssetList::Shop_Scroll_Cursor);
	nubSprite->SetDesignSize(17, 17);

	minPos.X(xLoc);
	minPos.Y(yLoc);
	maxPos.X(xLoc);
	maxPos.Y(yLoc + yRange);
	
	SetPosition(xLoc, yLoc);
	
}

ScrollNub::~ScrollNub()
{
	nubSprite->Release();
}

void ScrollNub::Update()
{
}

void ScrollNub::Render()
{
	nubSprite->Render();
}

void ScrollNub::SetPosition(float xLoc, float yLoc)
{
	if (yLoc < minPos.Y())
		yLoc = minPos.Y();
	else if (yLoc > maxPos.Y())
		yLoc = maxPos.Y();
	
	offset.X(xLoc);
	offset.Y(yLoc);
	nubSprite->SetPositionAbsolute(offset.X(), offset.Y());
	
	bounds.top = yLoc - nubSprite->DesignHeight() / 2 - 10;
	bounds.bottom = nubSprite->DesignHeight() + 20;
	bounds.left = xLoc - nubSprite->DesignWidth() / 2 - 10;
	bounds.right = nubSprite->DesignWidth() + 20; 
}

void ScrollNub::PauseAnimation(bool pause)
{
}

float ScrollNub::GetVerticalPercent() const
{
	float y1 = offset.Y() - minPos.Y();
	float y2 = maxPos.Y() - minPos.Y();
	return y1 / y2;
}

void ScrollNub::SetVerticalPercent(float _value)
{
	float y1 = maxPos.Y() - minPos.Y();
	float yOffset = (y1 * _value) + minPos.Y();
	SetPosition(offset.X(), yOffset);
}

void ScrollNub::TouchesBeganImpl(Touch &_touches)
{
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
	}
}

void ScrollNub::TouchesMovedImpl(Touch &_touches)
{
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;

	SetPosition(offset.X(), _touches.Y);
}

void ScrollNub::TouchesEndedImpl(Touch &_touches)
{
	if (_touches.ID == m_touchID)
	{
		m_touchID = -1;
	}
}
	

/*
void ScrollNub::TouchesBegan(UIView *view, NSSet *touches)
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
		}
	}
}

void ScrollNub::TouchesMoved(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch == this->touch)
		{
			CGPoint location = [touch locationInView: view];
			SetPosition(offset.X(), location.y);
		}
	}
}

void ScrollNub::TouchesEnded(UIView *view, NSSet *touches)
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

void ScrollNub::TouchesCancelled(UIView *view, NSSet *touches)
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
*/