/*
 *  RadioButtonControl.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Input_Engine.h"
#include "Graphics.h"
#include "Event.h"
#include <vector>

class RadioButtonControl : public Input_Object
{
public:
	RadioButtonControl(int Img_Selected, int Img_Disabled);
	virtual ~RadioButtonControl();
	
	// Input_Object
	void Render();
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);

	void Reset() {};
	void FreeResources() {};
	
	void SetPositionAndBounds(int x, int y, int width, int height);
	
	void SetValue(int _value) {m_value = _value;}
	int GetValue() const { return m_value; }
	
	void Select();
	void Deselect() { m_isSelected = false; }
	
	Event1<int> OnRadioButtonSelected;
	
	void SetDesignSize(int _widthActive, int _heightActive, int _widthDisabled, int _heightDisabled);

private:
	int m_touchID;
	//UITouch *touch;
	Rect bounds;
	CR::Graphics::Sprite *selectedSprite;
	CR::Graphics::Sprite *disabledSprite;
	bool m_isSelected;
	vector<RadioButtonControl*> friendRadioButtons;
	int m_value;
};