/*
 *  CharacterStats.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "CharacterBonus.h"
#include "Point.h"
#include "RepeatedSpriteHelper.h"

class CharacterStats : public IRenderable
{
public:
	CharacterStats();
	virtual ~CharacterStats();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetBonus(CharBonus cBonus);
	
private:
	CR::Graphics::Sprite *statsSprite;
	CR::Graphics::Sprite *resourceSprite;
	CR::Math::PointF offset;
	CharBonus m_cBonus;
	bool m_hasBonus;
	
	CR::Game::RepeatedSpriteHelper m_spriteHelperStats;
	CR::Game::RepeatedSpriteHelper m_spriteHelperResource;
};