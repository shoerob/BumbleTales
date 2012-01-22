/*
 *  ChainEffect.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/29/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ChainEffect.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ChainEffect::ChainEffect(int amount, float xLoc, float yLoc)
{
	isDead = false;
	
	chainSprite = graphics_engine->CreateSprite1(true, 790);
	chainSprite->SetImage(CR::AssetList::Chain_Match_Tags);
	
	if (amount > 20)
		chainSprite->SetFrame(20);
	else
		chainSprite->SetFrame(amount - 2);
	
	SetPosition(xLoc, yLoc);
	timeLeft = 2;
}

ChainEffect::~ChainEffect()
{
	chainSprite->Release();
}

void ChainEffect::Update()
{
	float timePassed = Globals::Instance().GetTimer()->GetTimePassed();
	
	timeLeft -= timePassed;
	
	if (timeLeft <= 0)
		isDead = true;
	
	SetPosition(offset.X(), offset.Y() - (10 * timePassed));
	
	if (timeLeft <= 1.0f)
	{
		CR::Math::Color32 color = CR::Math::Color32(255, 255, 255, 255 * (timeLeft / 1.0f) );
		chainSprite->Color(color);
	}
}

void ChainEffect::Render()
{
	chainSprite->Render();
}

void ChainEffect::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	chainSprite->SetPositionAbsolute(xLoc, yLoc);
}

void ChainEffect::PauseAnimation(bool pause)
{
}

bool ChainEffect::IsDead()
{
	return isDead;
}