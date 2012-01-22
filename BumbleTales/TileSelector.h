/*
 *  TileSelector.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Point.h"
#include "IRenderable.h"

class ResourcePuzzle;

class TileSelector : public IRenderable
{
public:
	TileSelector(ResourcePuzzle *parentPuzzle);
	~TileSelector();
	
	// Methods
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc) {};
	void PauseAnimation(bool pause);
	
	//Properties
	virtual bool Visible() const { return m_visible; }
	virtual void SetVisible(bool _value) { m_visible = _value; }
	void SetPosition(CR::Math::PointI position);
	CR::Math::PointI GetPosition() const { return m_position; }
	
	static const int tile_width = 44;
	static const int tile_height = 44;
private:
	CR::Math::PointI m_position; // position in the tile matrix
	CR::Graphics::Sprite *m_selectorSprite;
	ResourcePuzzle *m_parentPuzzle;
	bool m_visible;
};