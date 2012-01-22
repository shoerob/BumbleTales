/*
 *  StoryModeHUD.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/13/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryModeHUD.h"
#include "AssetList.h"
//#include "SavedGame.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

StoryModeHUD::StoryModeHUD(int xLoc, int yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	hudSprite = graphics_engine->CreateSprite1(false,900);
	hudSprite->SetImage(CR::AssetList::Story_Mode_HUD);
	hudSprite->SetPositionAbsolute(offset.X(), offset.Y());
	
	// Create resource bars
	resourceBars[Brick] = new ResourceBar(offset.X() + 3, offset.Y() - 19);
	resourceBars[Wood] = new ResourceBar(offset.X() + 3, offset.Y() - 1);
	resourceBars[Leaf] = new ResourceBar(offset.X() + 3, offset.Y() + 17);
	resourceBars[Crystal] = new ResourceBar(offset.X() + 71, offset.Y() - 19);
	resourceBars[Gold] = new ResourceBar(offset.X() + 71, offset.Y() - 1);
	resourceBars[Diamond] = new ResourceBar(offset.X() + 71, offset.Y() + 17);
	
	// Create level counter
	//levelCounter = new CounterFont(CR::AssetList::Font_Level, offset.X() - 70, offset.Y() + 10);
	numberFont = new NumberFont(CR::AssetList::Font_Level,800);
	numberFont->SetPosition(offset.X() - 61, offset.Y() + 10);
	m_currLevel = 0;
}

StoryModeHUD::~StoryModeHUD()
{
	hudSprite->Release();
	//delete levelCounter;
	delete numberFont;
	
	for (int i = 0; i < resource_bars; i++)
		delete resourceBars[i];
}

void StoryModeHUD::Update()
{
	//levelCounter->Update();
	
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->Update();
	}
}

void StoryModeHUD::Render()
{
	hudSprite->Render();
	
	//levelCounter->Render();
	numberFont->RenderNumber(m_currLevel);
	
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->Render();
	}
}

void StoryModeHUD::PauseAnimation(bool pause)
{
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->PauseAnimation(pause);
	}
}

void StoryModeHUD::ResetResourceBars()
{
	for (int i = 0; i < resource_bars; i++)
	{
		resourceBars[i]->ResetValue();
	}
}

void StoryModeHUD::SetResourceRequirement(ResourceType rType, int amount)
{
	if ((int)rType > 5)
		return;
	
	resourceBars[rType]->SetMaxValue(amount);
}

void StoryModeHUD::AddResources(ResourceType rType, int amount)
{
	if ((int)rType > 5)
		return;
	
	resourceBars[rType]->AddToCurrValue(amount);
}

bool StoryModeHUD::ResourcesGathered()
{
	for (int i = 0; i < resource_bars; i++)
		if (resourceBars[i]->IsFull() == false) return false;
	
	return true;
}

void StoryModeHUD::PerformLevelUp()
{
	//levelCounter->Increment();
	//levelCounter++;
	//SetLevel(levelCounter->GetCount() + 1);
	SetLevel(m_currLevel + 1);
	ResetResourceBars();
}

void StoryModeHUD::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
}

void StoryModeHUD::SetLevel(int level)
{
	//levelCounter->SetCount(level);
	m_currLevel = level;
	
	int baseResourceRequirement = 3;
	for (int i = 0; i < 6; i++)
		SetResourceRequirement((ResourceType)i, baseResourceRequirement + level - 1);
}

int StoryModeHUD::GetResourceRequirement()
{
	int baseResourceRequirement = 3;
	return baseResourceRequirement + m_currLevel - 1;
}