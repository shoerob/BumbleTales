/*
 *  TimeDisplay.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/18/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "NumberFont.h"
#include "Point.h"

class TimeDisplay : public IRenderable
{
public:
	TimeDisplay();
	virtual ~TimeDisplay();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);

	void SetSeconds(int _value) { m_seconds = _value; }
	void SetFontAsset(int _asset);
private:
	CR::Math::PointF offset;
	NumberFont *numberFont;
	NumberFont *colonFont;
	int m_seconds;
};