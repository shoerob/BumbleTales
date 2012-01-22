/*
 *  BuildingHUD.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "IRenderable.h"
#include "Graphics.h"
#include "BuildingButtonControl.h"
#include "BuildingLevels.h"
#include "Input_Engine.h"
#include "ResourcePuzzle.h"
#include <vector>

class BuildingHUD : IRenderable, public Input_Object
{
public:
	BuildingHUD(ResourcePuzzle *resourcePuzzle);
	virtual ~BuildingHUD();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	// Input_Object
	virtual void TouchesBeganImpl(Touch &_touches);
	virtual void TouchesMovedImpl(Touch &_touches);
	virtual void TouchesEndedImpl(Touch &_touches);
/*	void TouchesBeganImpl(UIView *view, NSSet *touches);
	void TouchesMovedImpl(UIView *view, NSSet *touches);
	void TouchesEndedImpl(UIView *view, NSSet *touches);
	void TouchesCancelledImpl(UIView *view, NSSet *touches);*/
	void Reset();
	void FreeResources() {};
	
	void SetBuildingLevel(BuildingName bName, int level);
	int GetBuildingLevel(BuildingName bName) const;
	void ResetBuildingDelays();
	
	//void AddButtonsToInputObjects(vector<Input_Object*> &input_objects);
	
	void EnableButton(BuildingName bName);
	void OnButtonDown(int tag);
	void OnButtonUp(int tag);
	
	// event args: building name, building level
	//Event2<BuildingName, int> OnBuildingDown;
	//Event2<BuildingName, int> OnBuildingUp;
	Event OnPowerUsed;
	
	bool GetCityMasterTrophy();
	bool GetIHeartBumblesTrophy();
	
private:
	//static const float baseDelayTime = 10.0f;
	float baseDelayTime;
	CR::Math::PointF offset;
	vector<BuildingButtonControl*> buildingButtons;
	int m_buildingLevels[6];
	bool m_buildingUsed[6];
	BuildingName m_buildingButtonDown;
	ResourcePuzzle *m_resourcePuzzle;
	Rect bounds;
	int m_touchID;
	//UITouch *touch;
};