/*
 *  CheckboxControl.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Input_Object.h"
#include "Event.h"

class CheckboxControl : public Input_Object
{
public:
	CheckboxControl();
	virtual ~CheckboxControl();
	
	// Input_Object
	void Render();
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
	void Reset();
	void FreeResources();
	
	void SetSpriteAndPosition(int nSprite, int xLoc, int yLoc);
	void SetButtonBounds(float left, float top, float width, float height);
	void SetSpriteAndBounds(float left, float top, int nSprite);
	
	bool IsChecked() const { return m_isChecked; }
	bool SetChecked(bool _value) { m_isChecked = _value; return m_isChecked; }
	
	Event OnCheckChanged;
	
	void DesignSize(int _width, int _height);

private:
	Rect bounds;
	bool m_isChecked;
	int m_touchID;
	//UITouch *touch;
	CR::Graphics::Sprite *checkSprite;
};