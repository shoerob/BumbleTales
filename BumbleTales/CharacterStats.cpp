/*
 *  CharacterStats.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CharacterStats.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

CharacterStats::CharacterStats() : m_spriteHelperStats(CR::AssetList::Char_HUD_Stat,true,700), m_spriteHelperResource(CR::AssetList::Char_HUD_Resource,true,700)
{
	statsSprite = graphics_engine->CreateSprite1(false,700);
	statsSprite->SetImage(CR::AssetList::Char_HUD_Stat);
	
	resourceSprite = graphics_engine->CreateSprite1(false,700);
	resourceSprite->SetImage(CR::AssetList::Char_HUD_Resource);
	m_cBonus = CharBonus();
	
	SetPosition(0, 0);
}

CharacterStats::~CharacterStats()
{
	statsSprite->Release();
	resourceSprite->Release();
}

void CharacterStats::Update()
{
}

void CharacterStats::Render()
{
	//CR::Math::PointF pos = offset;
	int xRow = 0;
	int yRow = 0;
	
	m_spriteHelperStats.Start();
	m_spriteHelperResource.Start();
	
	for (int i = 0; i < 6; i++)
	{
		if (m_cBonus.resourceBonus[i] > 0)
		{
			//resourceSprite->SetPositionAbsolute(offset.X() + xRow * 28, offset.Y() + yRow * 15);
			//resourceSprite->SetFrameSet(i);
			//resourceSprite->Render();
			m_spriteHelperResource.NewSprite();
			m_spriteHelperResource.SetPosition(offset.X() + xRow * 28, offset.Y() + yRow * 15);
			m_spriteHelperResource.SetFrame(i);
			
			//statsSprite->SetPositionAbsolute(offset.X() + 15 + (xRow * 28), offset.Y() + yRow * 15);
			//statsSprite->SetFrameSet(m_cBonus.resourceBonus[i]-1);
			//statsSprite->Render();
			m_spriteHelperStats.NewSprite();
			m_spriteHelperStats.SetPosition(offset.X() + 15 + (xRow * 28), offset.Y() + yRow * 15);
			m_spriteHelperStats.SetFrame(m_cBonus.resourceBonus[i]-1);
			
			xRow++;
			if (xRow > 1)
			{
				xRow = 0;
				yRow++;
			}
		}
	}
	
	if (m_cBonus.dropRateBonusType != NoTile)
	{
		//resourceSprite->SetFrameSet((int)m_cBonus.dropRateBonusType);
		//resourceSprite->SetPositionAbsolute(offset.X() + xRow * 28, offset.Y() + yRow * 15);
		//resourceSprite->Render();
		m_spriteHelperResource.NewSprite();
		m_spriteHelperResource.SetPosition(offset.X() + xRow * 28, offset.Y() + yRow * 15);
		m_spriteHelperResource.SetFrame((int)m_cBonus.dropRateBonusType);
		
		//statsSprite->SetPositionAbsolute(offset.X() + 15 + (xRow * 28), offset.Y() + yRow * 15);
		//statsSprite->SetFrameSet(2);
		//statsSprite->Render();
		m_spriteHelperStats.NewSprite();
		m_spriteHelperStats.SetPosition(offset.X() + 15 + (xRow * 28), offset.Y() + yRow * 15);
		m_spriteHelperStats.SetFrame(2);
	}
	
	m_spriteHelperStats.End();
	m_spriteHelperResource.End();
}

void CharacterStats::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	resourceSprite->SetPositionAbsolute(xLoc, yLoc);
}

void CharacterStats::PauseAnimation(bool pause)
{
}

void CharacterStats::SetBonus(CharBonus cBonus)
{
	m_cBonus = cBonus;
}