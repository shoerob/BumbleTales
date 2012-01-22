/*
 *  ResourcePuzzle.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "ResourceTile.h"
#include "TileSelector.h"
#include "Point.h"
#include "Input_Engine.h"
#include "Graphics.h"
#include <queue>
#include <vector>
#include "ParticleSystemManager.h"
#include "CrystalParticleSystem.h"
#include "Event.h"
#include "IRenderable.h"
#include "BuildingLevels.h"
#include "Point.h"
#include "SpecialSelector.h"
#include "Globals.h"
#include "ChainEffectManager.h"
#include "Sound.h"
using namespace std;

enum MatchOrientation
{
	VerticalMatch,
	HorizontalMatch
};

struct MatchBounds {
	bool foundMatch;
	int x;
	int y;
	int lower;
	int upper;
	MatchOrientation orientation;
	
	ResourceType qType;
	int qTiles;
	
	MatchBounds()
	{
		foundMatch = false;
		lower = 0;
		upper = 0;
		x = 0;
		y = 0;
		
		qType = Gold;
		qTiles = 0;
	};
	
	MatchBounds(bool fMatch, MatchOrientation orient, int xLoc, int yLoc, int l, int u, ResourceType qType, int qTiles)
	{
		foundMatch = fMatch;
		orientation = orient;
		lower = l;
		upper = u;
		x = xLoc;
		y = yLoc;
		this->qType = qType;
		this->qTiles = qTiles;
	}
};

class ResourcePuzzle : public Input_Object, public IRenderable
{
public:
	ResourcePuzzle(int xLoc, int yLoc, int spacing);
	virtual ~ResourcePuzzle();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc) {};
	void PauseAnimation(bool pause);
	
	// Puzzle Tile Settings
	virtual float Offset_X() const { return offset.X(); }
	virtual float Offset_Y() const { return offset.Y(); }
	virtual float Spacing() const { return tile_spacing; }
	//virtual void SetState(int _value) { }
	
	//Input_Object
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
	//virtual void TouchesBeganImpl(UIView *view, NSSet *touches);
	//virtual void TouchesMovedImpl(UIView *view, NSSet *touches);
	//virtual void TouchesEndedImpl(UIView *view, NSSet *touches);
	//virtual void TouchesCancelledImpl(UIView *view, NSSet *touches);
	virtual void Reset() {}; // useless?
	virtual void FreeResources() {}; // useless?
	
	// Tiles Manipulation
	ResourceTile *GetResourceTile(int xLoc, int yLoc) const;
	bool CheckAndRemoveTileMatches();
	MatchBounds FindHorizontalMatch(int xLoc, int yLoc);
	MatchBounds FindVerticalMatch(int xLoc, int yLoc);
	void SwapTiles(CR::Math::PointI tile1, CR::Math::PointI tile2);
	bool CanSwapTiles(CR::Math::PointI tile1, CR::Math::PointI tile2);
	void RandomizeTiles();
	void ResetPuzzle();
	void AnimatePuzzleSlideIn();
	bool AnimateShakeTiles(CR::Math::PointI tile1, CR::Math::PointI tile2);
	
	bool IsPuzzleValid();
	bool CheckForLeftMatch(int x, int y, ResourceTile *rTile);
	bool CheckForRightMatch(int x, int y, ResourceTile *rTile);
	bool CheckForUpMatch(int x, int y, ResourceTile *rTile);
	bool CheckForDownMatch(int x, int y, ResourceTile *rTile);
	bool CheckForMiddleVerticalMatch(int x, int y, ResourceTile *rTile);
	bool CheckForMiddleHorizontalMatch(int x, int y, ResourceTile *rTile);
	bool CheckForUpSwapMatch(int x, int y);
	bool CheckForDownSwapMatch(int x, int y);
	bool CheckForLeftSwapMatch(int x, int y);
	bool CheckForRightSwapMatch(int x, int y);
	
	bool IsPuzzleAnimating() const;
	
	void SetDropRateBonusType(ResourceType rType);
	void SetBuildingSpecialDown(BuildingName bName, int level);
	void SetBuildingSpecialUp(BuildingName bName, int level);
	void CancelBuildingSpecial();
	void OnClearBuildingSpecialTiles();
	void OnExplodeTilesSpecial();
	void DropTouchValue() { /*this->touch = NULL; */}
	
	void SetHintsEnabled(bool _value) { hintsEnabled = _value; }
	void FindHintBlock();
	void AnimateHint();
	void StopAnimateHint();
	void PlayResourceSound(ResourceType rType);
	
	// Events
	Event2<ResourceType, int> ResourcesRetrieved;
	Event OnIncrementChain;
	Event MoveMade;
	
	// public constants
	static const int x_tiles = 7;
	static const int y_tiles = 7;
	static const int tiles_required_for_match = 3;

private:
	static const float anim_fps;
	bool m_isAnimating;
	float tile_spacing;
	CR::Math::PointF offset;
	ResourceTile *resourceTiles[x_tiles][y_tiles];
	bool specialClearTiles[x_tiles][y_tiles];
	TileSelector *tileSelector;
	ParticleSystemManager *particleSystemManager;
	int m_touchID;
	//UITouch *touch;
	bool hideTileSelectorAfterAnimation;
	ResourceType m_dropRateBonusType;
	bool m_buildingSpecialDown;
	SpecialSelector *specialSelector;
	
	bool resettingPuzzle;
	CR::Graphics::Sprite *resetBoardSprite;
	
	float maxHintTime;
	float currHintTime;
	CR::Math::PointI hintOffset;
	bool hintsEnabled;
	
	ChainEffectManager *chainManager;
	int chainCount;
	
	bool touchAllowed;
	vector<std::tr1::shared_ptr<CR::Sound::ISoundFX> > sounds;
};