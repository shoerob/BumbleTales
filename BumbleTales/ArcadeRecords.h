/*
 *  ArcadeRecords.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/16/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "IRenderable.h"
#include "Graphics.h"
#include "ArcadeModeSaveInfo.h"
#include "NumberFont.h"
#include "TimeDisplay.h"
class ArcadeRecords : public IRenderable
{
public:
	ArcadeRecords();
	virtual ~ArcadeRecords();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void LoadFromArcadeSaveInfo(ArcadeModeSaveInfo *saveInfo);
	
private:
	ArcadeModeSaveInfo *saveInfo;
	CR::Graphics::Sprite *bgSprite;
	NumberFont *smallNumFont;
	NumberFont *bigNumFont;
	
	vector<int> highScores;
	vector<int> highScoresLevels;
	int largestMatch;
	int largestChain;
	int maxPointsOnSingleMove;
	int highestNumMoves;
	int mostPowersUsed;
	int longestSession;
	TimeDisplay *timeDisplay;
};