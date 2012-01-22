/*
 *  ResourceTile.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Point.h"
#include <vector>
#include <queue>
#include "IRenderable.h"
#include "SpecialSelector.h"
#include "Globals.h"
#include "Sound.h"

using namespace std;

class ResourcePuzzle;

enum ResourceType {Leaf = 0, Brick = 1, Wood = 2, Crystal = 3, Diamond = 4, Gold = 5, MTile = 6, QTile = 7, NoTile, NUMResourceTypes};
enum AnimationStatus { AnimationOff, AnimationOn};
enum AnimationDirection { AnimateUp, AnimateDown, AnimateLeft, AnimateRight};

class ResourceTile: public IRenderable
{
public:
	ResourceTile(ResourcePuzzle *parentPuzzle, int xLoc, int yLoc); // initialize with matrix locations
	virtual ~ResourceTile();
	
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc) {};
	void PauseAnimation(bool pause);
	
	void AnimateSlideIn(CR::Math::PointI from_point, CR::Math::PointI to_point, float timeSpan);
	void AnimateSlideTo(CR::Math::PointI to_point, float timeSpan);
	void AnimateShakeTo(AnimationDirection direction, float timeSpan);
	void AnimateSlideToPoint(CR::Math::PointF to_point, float timeSpan);
	void AnimateHint();
	void StopAnimateHint();
	//void AnimateSpecialClearThenSlideIn(CR::Math::PointI from_point, CR::Math::PointI to_point, int animFrames);
	
	virtual int TilePositionUpToDate() const { return animationStatus == AnimationOff; }
	ResourceType GetResourceType() const { return resourceType; }
	void RandomizeType(ResourceType dropRateBonusType);
	//virtual void SetState(int _value) { }
	virtual CR::Math::PointF GetAbsolutePosition() const;
	
	void RenderSelectorSpecial(int _frame);
	void RenderSelectorExplode(int _frame);
	
	static const int tile_width = 44;
	static const int tile_height = 44;
	static const int tile_types = 8;
	
private:
	ResourcePuzzle *m_parentPuzzle;
	ResourceType resourceType;
	CR::Math::PointF position;
	
	// Tile Movement Animation
	AnimationStatus animationStatus;
	//vector<CR::Math::PointF> points;
	//queue<CR::Math::PointF> animationQueue;
	
	CR::Graphics::Sprite *m_tileSprite;
	CR::Graphics::Sprite *selectorSprite;
	
	//CR::Graphics::Sprite *m_specialClearSprite;
	//bool showSpecialClear;
	CR::Math::PointF finalAnimPoint;
	CR::Math::PointF animDelta;
	float animTotalTime;
	float animTimeLeft;
	
	bool shakeToAnim;
	CR::Math::PointF shakeToStartPoint;
	
	
};