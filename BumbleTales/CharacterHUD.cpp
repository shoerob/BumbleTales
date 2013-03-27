/*
 *  CharacterHUD.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CharacterHUD.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

CharacterHUD::CharacterHUD()
{
	characterBonus = new CharacterBonus();
	charStats = new CharacterStats();
	
	Input_Button::Input_Button();
	SetSpriteAndBounds(0, 0, CR::AssetList::Char_HUD_Base, 800);
	DesignSize(71, 81);

	characterSprite = graphics_engine->CreateSprite1(true,700);
	characterSprite->SetImage(CR::AssetList::Char_HUD_Character);
	characterSprite->SetDesignSize(62, 39);

	SetCharacter(Mayor, 1);
	
}

CharacterHUD::~CharacterHUD()
{
	characterSprite->Release();
	delete characterBonus;
	delete charStats;
}

void CharacterHUD::Update()
{
}

void CharacterHUD::Render()
{
	Input_Button::Render();
	
	if (m_character != NoCharacter)
	{
		characterSprite->Render();
		charStats->Render();
	}
}

void CharacterHUD::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	Input_Button::SetPosition(xLoc, yLoc);
	characterSprite->SetPositionAbsolute(xLoc + 35, yLoc + 21);
	charStats->SetPosition(xLoc + 14, yLoc + 53);
}

void CharacterHUD::PauseAnimation(bool pause)
{
}

void CharacterHUD::SetCharacter(CharacterName charName, int level)
{
	characterSprite->SetFrame((int)charName);
	m_character = charName;
	m_level = level;
	charStats->SetBonus(characterBonus->GetBonus(m_character, m_level));
}

CharBonus CharacterHUD::GetCharacterBonus()
{
	return characterBonus->GetBonus(m_character, m_level);
}