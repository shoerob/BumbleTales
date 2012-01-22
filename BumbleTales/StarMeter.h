/*
 *  StarMeter.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/10/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "RepeatedSpriteHelper.h"

class StarMeter : public IRenderable
{
public:
	StarMeter();
	virtual ~StarMeter();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);

	void SetFilledStars(int _value);
	int GetFilledStars() const { return m_starCount; }
	void SetStarIndicator(int _value);
	int GetStarIndicator() const { return m_starIndicator; }

private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *meterSprite;
	CR::Graphics::Sprite *starSprite;
	int m_starCount;
	int m_starIndicator;
	CR::Game::RepeatedSpriteHelper m_spriteHelper;
	

};