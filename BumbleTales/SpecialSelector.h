/*
 *  SpecialSelector.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/3/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Point.h"
#include "IRenderable.h"
#include "Event.h"

class ResourcePuzzle;

class SpecialSelector : public IRenderable
{
public:
	SpecialSelector(ResourcePuzzle *parentPuzzle);
	virtual ~SpecialSelector();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void SetTilePosition(int x, int y);
	
	void ShowSelector2();
	void ShowSelector3();
	
	bool HideTiles() const;
	bool IsSelector3() const { return m_isSelector3; }
	
	Event OnDoneAnimating;
	Event OnExplodeTiles;
	
	int GetCurrFrame();
	
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *selectorSprite;
	ResourcePuzzle *m_parentPuzzle;
	bool m_isSelector3;
	
	bool tilesExploded;
};