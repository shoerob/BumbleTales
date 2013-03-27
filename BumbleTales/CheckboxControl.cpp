/*
 *  CheckboxControl.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CheckboxControl.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

CheckboxControl::CheckboxControl() : m_touchID(-1)
{
	m_isChecked = true;
	checkSprite = graphics_engine->CreateSprite1(false,400);
	//touch = NULL;
}

CheckboxControl::~CheckboxControl()
{
	checkSprite->Release();
}

void CheckboxControl::SetSpriteAndPosition(int nSprite, int xLoc, int yLoc)
{
	checkSprite->SetImage(nSprite);
	checkSprite->SetPositionAbsolute(xLoc + (checkSprite->GetFrameWidth()/2), yLoc + (checkSprite->GetFrameHeight()/2));
}

void CheckboxControl::SetButtonBounds(float left, float top, float width, float height)
{
	Rect r;
	r.top = top;
	r.left = left;
	r.bottom = height;
	r.right = width;
	bounds = r;
}

void CheckboxControl::SetSpriteAndBounds(float left, float top, int nSprite)
{	
	checkSprite->SetImage(nSprite);
	
	Rect r;
	r.top = top;
	r.left = left;
	r.bottom = checkSprite->GetFrameHeight();
	r.right = checkSprite->GetFrameWidth();
	bounds = r;

	checkSprite->SetPositionAbsolute(bounds.left + (checkSprite->GetFrameWidth()/2), bounds.top + (checkSprite->GetFrameHeight()/2));
}

void CheckboxControl::Render()
{
	if (m_isChecked)
		checkSprite->Render();
}

void CheckboxControl::TouchesBeganImpl(Touch &_touches)
{
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
		
		if (!m_disabled)
		{
			m_isChecked = !m_isChecked;
			OnCheckChanged();
		}
	}
}

void CheckboxControl::TouchesMovedImpl(Touch &_touches)
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

void CheckboxControl::TouchesEndedImpl(Touch &_touches)
{
	if (_touches.ID == m_touchID)
	{
		m_touchID = -1;
	}
}

void CheckboxControl::Reset()
{
}

void CheckboxControl::FreeResources()
{
}

void CheckboxControl::DesignSize(int _width, int _height)
{
	checkSprite->SetDesignSize(_width, _height);
}