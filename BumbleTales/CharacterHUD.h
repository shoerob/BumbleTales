/*
 *  CharacterHUD.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "Input_Button.h"
#include "CharacterLevels.h"
#include "CharacterBonus.h"
#include "CharacterStats.h"

class CharacterHUD : public Input_Button, public IRenderable
{
public:
	CharacterHUD();
	virtual ~CharacterHUD();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetCharacter(CharacterName charName, int level);
	CharacterName GetCharacter() const { return m_character; }
	CharBonus GetCharacterBonus();
private:
	CharacterBonus *characterBonus;
	CR::Math::PointF offset;
	CR::Graphics::Sprite *characterSprite;
	CharacterStats *charStats;
	CharacterName m_character;
	int m_level;
};