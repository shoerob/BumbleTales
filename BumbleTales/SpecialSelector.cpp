/*
 *  SpecialSelector.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/3/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SpecialSelector.h"
#include "AssetList.h"
#include "ResourcePuzzle.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

SpecialSelector::SpecialSelector(ResourcePuzzle *parentPuzzle)
{
	selectorSprite = graphics_engine->CreateSprite1(true,800);
	selectorSprite->SetImage(CR::AssetList::Selector_2);
	m_parentPuzzle = parentPuzzle;
	m_isSelector3 = false;
	tilesExploded = false;
}

SpecialSelector::~SpecialSelector()
{
	selectorSprite->Release();
}

void SpecialSelector::Update()
{
	if (m_isSelector3)
	{
		if (!selectorSprite->IsAnimating())
		{
			OnDoneAnimating();
			ShowSelector2();
			tilesExploded = false;
		}
		else
		{
			if (selectorSprite->GetFrame() > 12)
			{
				if (!tilesExploded)
				{
					OnExplodeTiles();
					tilesExploded = true;
				}
			}
		}
	}
}

void SpecialSelector::Render()
{
	selectorSprite->Render();
}

void SpecialSelector::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	selectorSprite->SetPositionAbsolute(xLoc, yLoc);
}

void SpecialSelector::PauseAnimation(bool pause)
{
	selectorSprite->PauseAnimation(pause);
}

void SpecialSelector::SetTilePosition(int x, int y)
{
	// Return w/no changes if player touched out of puzzle's bounds
	if (x > (ResourcePuzzle::x_tiles - 1) || x < 0 ||
		y > (ResourcePuzzle::y_tiles - 1) || y < 0)
		return;
	
	SetPosition(x * ResourceTile::tile_width + ResourceTile::tile_width/2 + (x * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_X(),
				 y * ResourceTile::tile_height + ResourceTile::tile_height/2 + (y * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_Y());
}

void SpecialSelector::ShowSelector2()
{
	selectorSprite->SetImage(CR::AssetList::Selector_2);
	selectorSprite->SetFrame(0);
	selectorSprite->SetAutoAnimate(true);
	m_isSelector3 = false;
}

void SpecialSelector::ShowSelector3()
{
	selectorSprite->SetImage(CR::AssetList::Selector_3);
	selectorSprite->SetFrame(0);
	selectorSprite->AutoStopAnimate();
	m_isSelector3 = true;
}

bool SpecialSelector::HideTiles() const
{
	if (selectorSprite->GetFrame() > 12)
		return true;
	else return false;
}

int SpecialSelector::GetCurrFrame()
{
	return (selectorSprite->GetFrame());
}
