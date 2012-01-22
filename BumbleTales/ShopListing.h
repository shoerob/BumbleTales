/*
 *  ShopListing.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/8/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "BuildingItem.h"
#include "CharacterItem.h"
#include "SeparatorItem.h"
#include "Point.h"
#include "Input_Engine.h"
#include <vector>
#include "ScrollNub.h"
#include "StoryModeSaveInfo.h"
#include "CounterFont.h"
#include "CharacterBonus.h"
#include "BuildingLevels.h"
#include "CharacterLevels.h"
#include "Event.h"
#include "SplashScreen.h"

using namespace std;

class ShopListing : public Input_Object, public IRenderable
{
public:
	ShopListing(int xLoc, int yLoc);
	virtual ~ShopListing();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
	
	// Input_Object
	/*void TouchesBeganImpl(UIView *view, NSSet *touches);
	void TouchesMovedImpl(UIView *view, NSSet *touches);
	void TouchesEndedImpl(UIView *view, NSSet *touches);
	void TouchesCancelledImpl(UIView *view, NSSet *touches);*/
	//void Update(){}
	//void Render();
	void FreeResources() {};
	void Reset(){};
	
	//void LoadFromSaveInfo(StoryModeSaveInfo *saveInfo);
	//void WriteToSaveInfo(StoryModeSaveInfo *saveInfo);
	
	void LoadFromLevelInfo(CharacterLevels *cLevels, BuildingLevels *bLevels);
	void WriteToLevelInfo(CharacterLevels *cLevels, BuildingLevels *bLevels);
	void DisplayWinGameSplash();
	// get blevels
	// get clevels
	
	void SetStarCount(int _value);
	
	void OnShopItemClicked(ShopItem *item);
	void OnShopItemPlusClicked(ShopItem *item);
	void OnNewEntrySplashFinished();
	
	bool GetHasEverything() const;
	bool IsBuildingLocked(BuildingName bName);
	
	Event ShopItemPlusClicked;
	Event SplashFinished;
private:
	CR::Math::PointF offset;
	CR::Math::PointF minPos;
	CR::Math::PointF maxPos;
	vector<ShopItem *> m_storeItems;
	int m_touchID;
	//UITouch *touch;
	Rect bounds;
	CR::Math::PointF touchPos;
	ScrollNub *m_scrollNub;
	CR::Graphics::Sprite *infoSprite;
	bool m_showInfoSprite;
	CharacterBonus *characterBonus;
	SplashScreen *newEntrySplash;
	SplashScreen *itemLockedSplash;
	bool showingNewEntrySplash;
	
	int yDownPos;
	bool nubTouchMode;
	
	bool autoScroll;
	int autoScrollStep;
	
	
};