/*
 *  ScrollNub.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/8/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "ITouchable.h"

class ScrollNub : public ITouchable, public IRenderable
{
public:
	ScrollNub(int xLoc, int yLoc, int yRange);
	virtual ~ScrollNub();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	float GetVerticalPercent() const; // returns 0 - 100 based on the nub position, min through max
	void SetVerticalPercent(float _value);
	
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
	// ITouchable
	/*void TouchesBegan(UIView *view, NSSet *touches);
	void TouchesMoved(UIView *view, NSSet *touches);
	void TouchesEnded(UIView *view, NSSet *touches);
	void TouchesCancelled(UIView *view, NSSet *touches);*/
	
	bool IsDown() { return false;}//touch != NULL; }
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *nubSprite;
	
	int m_touchID;
	//UITouch *touch;
	Rect bounds;
	CR::Math::PointF minPos;
	CR::Math::PointF maxPos;
};