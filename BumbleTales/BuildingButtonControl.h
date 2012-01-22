/*
 *  BuildingButtonControl.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/1/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Input_Object.h"
#include "Globals.h"
#include "Input_Button.h"

class BuildingButtonControl : public Input_Object
{
public:
	BuildingButtonControl();
	virtual ~BuildingButtonControl();
	
	// Input_Object
	void Update();
	void Render();
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
	/*void TouchesBeganImpl(UIView *view, NSSet *touches);
	void TouchesMovedImpl(UIView *view, NSSet *touches);
	void TouchesEndedImpl(UIView *view, NSSet *touches);
	void TouchesCancelledImpl(UIView *view, NSSet *touches);*/
	void Reset() {}
	void FreeResources() {}
	void PauseAnimation(bool pause);
	
	void SetDelayTime(float _value);
	void StartCountDown();
	
	void SetSprite(int nSprite);
	void SetPosition(int xLoc, int yLoc);

	void SetTag(int _value) { m_tag = _value; }
	int GetTag() const { return m_tag; }
	
	void ShowBuildAnimation();
	void CancelIfDown();
	
	void Activate();
	Event1<int> OnDown;
	Event1<int> OnUp;
	
private:
	Rect bounds;
	CR::Graphics::Sprite *buttonSprite;
	float m_delayTime;
	float m_currTime;
	bool m_active;
	int m_touchID;
	//UITouch *touch;
	int m_tag;
	
	bool m_wasPaused;
	
	// Build animation
	bool m_showBuildAnimation;
	CR::Graphics::Sprite *buildSprite;
	CR::Math::Color32 fadeColor;
	int alphaStep;
};