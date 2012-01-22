/*
 *  TileSelector.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "TileSelector.h"
#include "AssetList.h"
#include "ResourcePuzzle.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

TileSelector::TileSelector(ResourcePuzzle *parentPuzzle)
{
	m_parentPuzzle = parentPuzzle;
	m_visible = true;
	
	m_selectorSprite = graphics_engine->CreateSprite1(true,800);
	m_selectorSprite->SetImage(CR::AssetList::Selector_1);

	m_position.X(0);
	m_position.Y(0);
	SetPosition(m_position);
}

TileSelector::~TileSelector()
{
	m_selectorSprite->Release();
}

void TileSelector::SetPosition(CR::Math::PointI position)
{
	// Return w/no changes if player touched out of puzzle's bounds
	if (position.X() > (ResourcePuzzle::x_tiles - 1) || position.X() < 0 ||
		position.Y() > (ResourcePuzzle::y_tiles - 1) || position.Y() < 0)
		return;
	
	// set the position of te selection sprite
	m_position = position;
	m_selectorSprite->SetPositionAbsolute(m_position.X() * tile_width + tile_width/2 + (m_position.X() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_X(),
										  m_position.Y() * tile_height + tile_height/2 + (m_position.Y() * m_parentPuzzle->Spacing()) + m_parentPuzzle->Offset_Y());
}

void TileSelector::Update()
{

}

void TileSelector::Render()
{
	if (m_visible)
		m_selectorSprite->Render();
}

void TileSelector::PauseAnimation(bool pause)
{
	m_selectorSprite->PauseAnimation(pause);
}