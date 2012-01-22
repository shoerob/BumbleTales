/*
 *  ShopMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "IView.h"
#include "Graphics.h"
#include "StoryModeSaveInfo.h"
#include "Input_Engine.h"
#include "ShopItem.h"
#include "CharacterItem.h"
#include "BuildingItem.h"
#include "ShopListing.h"
#include "NumberFont.h"

class ShopMenuView : public IView
{
public:
	ShopMenuView();
	virtual ~ShopMenuView();
	
	// IView
	void Update();
	void Render();
	
	void LoadFromSaveInfo(StoryModeSaveInfo *saveInfo);
	void WriteToSaveInfo(StoryModeSaveInfo *saveInfo);
	
	void OnCloseButtonPressed();
	void OnShopItemPlusClicked();
	void OnWinGameSplashDone();
	
	bool GetHasEverything() const;
	
	Event OnClose;
	
private:
	CR::Graphics::Sprite *baseSprite;
	Input_Button *closeButton;
	ShopListing *shopListing;
	//CounterFont *starsCounter;
	NumberFont *numberFont;
	int m_numStars;
	bool hasWonGame;
	
	CR::Graphics::Sprite *maxTag;
	bool maxedOut;
};