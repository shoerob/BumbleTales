/*
 *  Input_Button.h
 *  BoB
 *
 *  Created by Robert Shoemate on 1/19/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 *  Sprite Requirements:
 *	Total Frames: 2
 *	Frame 1: Up Image
 *	Frame 2: Down Image
 */
#pragma once

#include "Input_Object.h"
#include "../utility/Event.h"
#include "../utility/Guid.h"

using namespace CR::Graphics;
class Input_Button : public Input_Object
{
public:
	Input_Button(bool _oneSet = false);
	~Input_Button();
	
	void SetButtonBounds(float left, float top, float width, float height);
	void SetSpriteAndBounds(float left, float top, int nSprite, int zPos = 0);
	void SetSound(CR::Utility::Guid _id);

	void TouchesBeganImpl(Touch &_touches);
	void TouchesMovedImpl(Touch &_touches);
	void TouchesEndedImpl(Touch &_touches);
	
	bool IsDown() const {return isDown;}
	//void Temp(int _value) {temp = _value;}
	bool WasPressed()
	{
		// reset wasPressed whenever it is checked for
		if (wasPressed)
		{
			wasPressed = false;
			return true;
		}
		
		return false;
	}
	
	bool IsActing()
	{
		// reset isActing whenever it is checked for
		if (isActing)
		{
			isActing = false;
			return true;
		}
		
		return false;
	}
	
	
	void Reset();
	virtual void Render();
	virtual void FreeResources();
	virtual void SetPosition(int x, int y);
	void SetSoundOn(bool isOn) { soundOn = isOn; }
	Event OnClicked;
	virtual void DesignSize(int _width,int _height)
	{
		objectSprite->SetDesignSize(_width,_height);
		bounds.right = _width;
		bounds.bottom = _height;
	}
private:
	Rect bounds;
	Rect position;
	bool isDown;
	bool isActing;
	bool m_oneSet;

	bool wasPressed;
	int touchID;
	CR::Graphics::Sprite* objectSprite;
	
	bool soundOn;
	
	void SetSprite(int nSprite, int zPos);
	
	//CR::Utility::Guid soundId;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> disabledSound;
};