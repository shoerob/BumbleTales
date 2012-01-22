/*
 *  ChainEffect.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/29/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#include "Graphics.h"
#include "IRenderable.h"
#include "Globals.h"

class ChainEffect : public IRenderable
{
public:
	ChainEffect(int amount, float xLoc, float yLoc);
	virtual ~ChainEffect();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	bool IsDead();
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *chainSprite;
	float timeLeft;
	bool isDead;
};