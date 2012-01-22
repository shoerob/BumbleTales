/*
 *  StarHUD.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/21/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "IRenderable.h"
#include "Graphics.h"
#include "Input_Engine.h"
//#include "CounterFont.h"
#include "NumberFont.h"

class StarHUD : public Input_Button, public IRenderable
{
public:
	StarHUD();
	virtual ~StarHUD();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void AddStar();
	void SetStars(int _value);
	int GetStars() const;
	
	void SetMaxedOut(bool _value) { maxedOut = _value; }
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *starSprite;
	//CounterFont *starCounter;
	NumberFont *numberFont;
	int m_numStars;
	CR::Graphics::Sprite *maxTag;
	bool maxedOut;
};