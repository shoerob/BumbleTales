/*
 *  ResourceBar.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/16/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Point.h"
#include "Graphics.h"
#include "IRenderable.h"

enum ResourceBarSize { NormalResourceBar, TinyResourceBar };

class ResourceBar : public IRenderable
{
public:
	ResourceBar(int xLoc, int yLoc, ResourceBarSize rSize = NormalResourceBar);
	virtual ~ResourceBar();
	
	//IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetMaxValue(int _value);
	void AddToCurrValue(int _value);
	void ResetValue();
	
	bool IsFull();
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *resourceBarSprite;
	
	int maxValue;
	int currValue;
	bool isFullAnimation;
	
	void SetResourceBarSprite();
	
	int assetResourceBar;
	int assetResourceBarFull;
	int barFrames;
};