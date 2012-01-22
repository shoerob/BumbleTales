/*
 *  RadioButtonControl.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "RadioButtonControl.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

RadioButtonControl::RadioButtonControl(int Img_Selected, int Img_Disabled) : m_touchID(-1)
{
	disabledSprite = graphics_engine->CreateSprite1(false,400);
	disabledSprite->SetImage(Img_Disabled);
	
	selectedSprite = graphics_engine->CreateSprite1(false,400);
	selectedSprite->SetImage(Img_Selected);
	
	m_isSelected = false;
	
	//touch = NULL;
}

RadioButtonControl::~RadioButtonControl()
{
	disabledSprite->Release();
}

void RadioButtonControl::Render()
{
	if (m_disabled)
	{
		disabledSprite->Render();
	}
	else if (m_isSelected)
	{
		selectedSprite->Render();
	}
}

void RadioButtonControl::SetPositionAndBounds(int x, int y, int width, int height)
{
	bounds.left = x;
	bounds.top = y;
	bounds.right = width;
	bounds.bottom = height;
	
	//disabledSprite->SetPositionAbsolute(x - (width/2), y - (height/2));
	//selectedSprite->SetPositionAbsolute(x - (width/2), y - (height/2));
	disabledSprite->SetPositionAbsolute(bounds.left + (disabledSprite->GetFrameWidth()/2), bounds.top + (disabledSprite->GetFrameWidth()/2));
	selectedSprite->SetPositionAbsolute(bounds.left + (disabledSprite->GetFrameWidth()/2), bounds.top + (disabledSprite->GetFrameWidth()/2));
	
	//checkSprite->SetPositionAbsolute(bounds.left + (checkSprite->GetFrameWidth()/2), bounds.top + (checkSprite->GetFrameHeight()/2));
}

void RadioButtonControl::Select()
{
	if (!m_disabled)
	{
		m_isSelected = true;
		OnRadioButtonSelected(m_value);
	}
}

void RadioButtonControl::TouchesBeganImpl(Touch &_touches)
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
			m_isSelected = true;
			OnRadioButtonSelected(m_value);
		}
	}
}

void RadioButtonControl::TouchesMovedImpl(Touch &_touches)
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

void RadioButtonControl::TouchesEndedImpl(Touch &_touches)
{
	if (_touches.ID == m_touchID)
	{
		m_touchID = -1;
	}
}

/*
void RadioButtonControl::TouchesBeganImpl(UIView *view, NSSet *touches)
{
	CGPoint glLocation;
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		glLocation = GetGLLocation(view, touch);
		
		if (glLocation.x > bounds.left && 
			glLocation.x < bounds.right + bounds.left &&
			glLocation.y > bounds.top &&
			glLocation.y < bounds.bottom + bounds.top)
		{
			//m_isChecked = !m_isChecked;
			
			if (!m_disabled)
			{
				m_isSelected = true;
				OnRadioButtonSelected(m_value);
			}
			
			this->touch = touch;
		}
	}
}

void RadioButtonControl::TouchesMovedImpl(UIView *view, NSSet *touches)
{
	CGPoint glLocation;
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		glLocation = GetGLLocation(view, touch);
		
		if (glLocation.x > bounds.left && 
			glLocation.x < bounds.right + bounds.left &&
			glLocation.y > bounds.top &&
			glLocation.y < bounds.bottom + bounds.top)
		{
			this->touch = touch;
		}
	}
}

void RadioButtonControl::TouchesEndedImpl(UIView *view, NSSet *touches)
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

void RadioButtonControl::TouchesCancelledImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			break;
		}
	}
}*/