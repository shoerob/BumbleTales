/*
 *  TrophyButton.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "TrophySaveInfo.h"
#include "Input_Object.h"
#include "Event.h"
#include "Point.h"

class TrophyButton : public Input_Object
{
public:
	TrophyButton(TrophyName trophyName, int zPos);
	virtual ~TrophyButton();
	
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
	// Input_Object
	//void TouchesBeganImpl(UIView *view, NSSet *touches);
	//void TouchesMovedImpl(UIView *view, NSSet *touches);
	//void TouchesEndedImpl(UIView *view, NSSet *touches);
	//void TouchesCancelledImpl(UIView *view, NSSet *touches);
	void Reset() {};
	void Update(){}
	void Render();
	void FreeResources() {};
	
	
	void SetPosition(int xLoc, int yLoc);
	void SetHasTrophy(bool hasTrophy);
	
	Event1<TrophyName> OnClicked;
	
private:
	CR::Graphics::Sprite *trophySprite;
	CR::Math::PointF offset;
	bool hasTrophy;
	TrophyName trophyName;
	int m_touchID;
	//UITouch *touch;
	Rect bounds;
};