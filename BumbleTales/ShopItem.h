/*
 *  ShopItem.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/7/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "Point.h"
#include "ITouchable.h"
#include "Event.h"
#include "StarMeter.h"
#include "Input_Engine.h"

class ShopItem : public IRenderable, public ITouchable
{
public:
	ShopItem();
	virtual ~ShopItem();
	
	// IRenderable
	virtual void Update();
	virtual void Render();	
	virtual void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
	// ITouchable
/*	void TouchesBegan(UIView *view, NSSet *touches);
	void TouchesMoved(UIView *view, NSSet *touches);
	void TouchesEnded(UIView *view, NSSet *touches);
	void TouchesCancelled(UIView *view, NSSet *touches);*/
	
	int GetLevel() const;
	void CancelLevelUp() { m_level--; }
	int GetHeight() const;
	
	
	int GetInformationAsset();
	void SetStarCount(int _value);
	void PlusClicked();
	
	Event1<ShopItem*> OnClicked;
	Event1<ShopItem*> OnPlusClicked;
	
protected:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *itemSprite;
	int m_level;
	int m_height;
	int m_infoAsset;
	Rect bounds;
	int m_touchID;
	//UITouch *touch;
	
	bool isLevelable;
	StarMeter *starMeter;
	Input_Button *plusButton;
	CR::Graphics::Sprite *plusDimmerSprite;
	
	bool disableInput;
};