/*
 *  BuildingHUD.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "BuildingHUD.h"
#include "AssetList.h"

BuildingHUD::BuildingHUD(ResourcePuzzle *resourcePuzzle) : m_touchID(-1)
{
	baseDelayTime = 90.0f;
	
	for (int i = 0; i < 6; i++)
	{
		buildingButtons.push_back(new BuildingButtonControl());
		buildingButtons[i]->SetTag(i);
		buildingButtons[i]->SetDelayTime(baseDelayTime);
		buildingButtons[i]->StartCountDown();
		buildingButtons[i]->OnDown += Delegate1<BuildingHUD, int>(this,&BuildingHUD::OnButtonDown);
		buildingButtons[i]->OnUp += Delegate1<BuildingHUD, int>(this,&BuildingHUD::OnButtonUp);
		m_buildingLevels[i] = 0;
		m_buildingUsed[i] = false;
	}
	
	buildingButtons[TownHall]->SetSprite(CR::AssetList::Building_Town_Hall);
	buildingButtons[TownHall]->SetDesignSize(71, 51);
	buildingButtons[PoliceStation]->SetSprite(CR::AssetList::Building_Police_Station);
	buildingButtons[PoliceStation]->SetDesignSize(60, 50);
	buildingButtons[Firehouse]->SetSprite(CR::AssetList::Building_Firehouse);
	buildingButtons[Firehouse]->SetDesignSize(50, 56);
	buildingButtons[Lodge]->SetSprite(CR::AssetList::Building_Lodge);
	buildingButtons[Lodge]->SetDesignSize(66, 53);
	buildingButtons[Theatre]->SetSprite(CR::AssetList::Building_Theatre);
	buildingButtons[Theatre]->SetDesignSize(61, 51);
	buildingButtons[Greenhouse]->SetSprite(CR::AssetList::Building_Greenhouse);
	buildingButtons[Greenhouse]->SetDesignSize(70, 64);

	m_resourcePuzzle = resourcePuzzle;
}

BuildingHUD::~BuildingHUD()
{
	for (int i = 0; i < buildingButtons.size(); i++)
		delete buildingButtons[i];
}

void BuildingHUD::Update()
{
	int i = 0;
	for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
	{
		if (m_buildingLevels[i] > 0)
			(*it)->Update();
		i++;
	}
}

void BuildingHUD::Render()
{
	int i = 0;
	for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
	{
		if (m_buildingLevels[i] > 0)
			(*it)->Render();
		i++;
	}
}

void BuildingHUD::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);

	buildingButtons[TownHall]->SetPosition(offset.X() - 4, offset.Y() - 4);
	buildingButtons[PoliceStation]->SetPosition(offset.X() + 28, offset.Y() + 35);
	buildingButtons[Firehouse]->SetPosition(offset.X() + 70, offset.Y() - 5);
	buildingButtons[Lodge]->SetPosition(offset.X() + 100, offset.Y() + 33);
	buildingButtons[Theatre]->SetPosition(offset.X() + 130, offset.Y() - 3);
	buildingButtons[Greenhouse]->SetPosition(offset.X() + 167, offset.Y() + 20);
	
	bounds.left = xLoc;
	bounds.top = yLoc;
	bounds.right = 250;
	bounds.bottom = 100; 
}

void BuildingHUD::PauseAnimation(bool pause)
{
	for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
	{
		(*it)->CancelIfDown();
		(*it)->PauseAnimation(pause);
	}
	
	//m_buildingButtonDown = NoBuilding;
	
	m_resourcePuzzle->CancelBuildingSpecial();
	m_touchID = -1;
}

void BuildingHUD::SetBuildingLevel(BuildingName bName, int level)
{
	if (m_buildingLevels[(int)bName] == level) return;
	else if (m_buildingLevels[(int)bName] == 0)
	{
		buildingButtons[(int)bName]->ShowBuildAnimation();
	}
	
	m_buildingLevels[(int)bName] = level;
	
	if (level <= 1)
		buildingButtons[(int)bName]->SetDelayTime(baseDelayTime);
	else if (level <= 3)
		buildingButtons[(int)bName]->SetDelayTime(baseDelayTime / 1.5f);
	else if (level <= 5)
		buildingButtons[(int)bName]->SetDelayTime(baseDelayTime / 2.0f);
}

int BuildingHUD::GetBuildingLevel(BuildingName bName) const
{
	return m_buildingLevels[(int)bName];
}

void BuildingHUD::ResetBuildingDelays()
{
	int i = 0;
	for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
	{
		if (m_buildingLevels[i] > 0)
			(*it)->StartCountDown();
		i++;
	}
}

void BuildingHUD::EnableButton(BuildingName bName)
{
	buildingButtons[(int)bName]->Activate();
}

void BuildingHUD::OnButtonDown(int tag)
{
	if (m_resourcePuzzle->IsPuzzleAnimating())
	{
		buildingButtons[tag]->Activate();
		return;
	}
	
	m_resourcePuzzle->SetBuildingSpecialDown((BuildingName)tag, m_buildingLevels[tag]);
}

void BuildingHUD::OnButtonUp(int tag)
{
	m_resourcePuzzle->SetBuildingSpecialUp((BuildingName)tag, m_buildingLevels[tag]);
	m_buildingUsed[tag] = true;
	OnPowerUsed();
}

bool BuildingHUD::GetCityMasterTrophy()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_buildingLevels[i] < 5)
			return false;
	}
	
	return true;
}

bool BuildingHUD::GetIHeartBumblesTrophy()
{
	for (int i = 0; i < 6; i++)
	{
		if (m_buildingUsed[i] == false)
			return false;
	}
	
	return true;
}

void BuildingHUD::TouchesBeganImpl(Touch &_touches)
{
	if (m_touchID != -1 && _touches.ID != m_touchID)
		return;
			
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
	
		for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
		{
			(*it)->TouchesBegan(_touches);
		}
	}
}

void BuildingHUD::TouchesMovedImpl(Touch &_touches)
{
	if (m_touchID != -1 && _touches.ID != m_touchID)
		return;;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
			
		for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
		{
			(*it)->TouchesMoved(_touches);
		}
	}
}

void BuildingHUD::TouchesEndedImpl(Touch &_touches)
{
	if (_touches.ID == m_touchID)
	{
		for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
		{
			(*it)->TouchesEnded(_touches);
		}
			
		m_touchID = -1;
	}
}

/*
void BuildingHUD::TouchesBeganImpl(UIView *view, NSSet *touches)
{
	CGPoint glLocation;
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		glLocation = GetGLLocation(view, touch);
		
		if (glLocation.x > bounds.left && 
			glLocation.x < bounds.right + bounds.left &&
			glLocation.y > bounds.top &&
			glLocation.y < bounds.bottom + bounds.top)
		{
			this->touch = touch;
	
			for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
			{
				(*it)->TouchesBegan(view, touches);
			}
		}
	}
}

void BuildingHUD::TouchesMovedImpl(UIView *view, NSSet *touches)
{
	CGPoint glLocation;
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		glLocation = GetGLLocation(view, touch);
		
		if (glLocation.x > bounds.left && 
			glLocation.x < bounds.right + bounds.left &&
			glLocation.y > bounds.top &&
			glLocation.y < bounds.bottom + bounds.top)
		{
			this->touch = touch;
			
			for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
			{
				(*it)->TouchesMoved(view, touches);
			}
		}
	}
}

void BuildingHUD::TouchesEndedImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
			{
				(*it)->TouchesEnded(view, touches);
			}
			
			this->touch = NULL;
			break;
		}
	}
}

void BuildingHUD::TouchesCancelledImpl(UIView *view, NSSet *touches)
{
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			for (vector<BuildingButtonControl*>::iterator it = buildingButtons.begin(); it != buildingButtons.end(); it++)
			{
				(*it)->TouchesCancelled(view, touches);
			}
			
			this->touch = NULL;
			break;
		}
	}
}*/

void BuildingHUD::Reset()
{

}