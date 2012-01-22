/*
 *  StoryRecords.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/16/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "IRenderable.h"
#include "Graphics.h"
#include "StoryModeSaveInfo.h"
#include "NumberFont.h"

class StoryRecords : public IRenderable
{
public:
	StoryRecords();
	virtual ~StoryRecords();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void LoadFromStorySaveInfo(StoryModeSaveInfo *saveInfo);
	
private:
	StoryModeSaveInfo *saveInfo;
	CR::Graphics::Sprite *bgSprite;
	NumberFont *smallNumFont;
	NumberFont *specialFont;
	
	int currentLevel;
	int purchaseCompletion;
	int largestMatch;
	int largestChain;
	vector<int> blocksCleared;
	int bronzeMedals;
	int silverMedals;
	int goldMedals;
};