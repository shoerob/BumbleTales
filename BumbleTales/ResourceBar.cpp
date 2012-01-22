/*
 *  ResourceBar.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/16/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ResourceBar.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

ResourceBar::ResourceBar(int xLoc, int yLoc, ResourceBarSize rSize)
{	
	offset.X(xLoc);
	offset.Y(yLoc);
	
	resourceBarSprite = NULL;

	isFullAnimation = false;
	maxValue = 1;
	currValue = 0;
	
	if (rSize == NormalResourceBar)
	{
		assetResourceBar = CR::AssetList::Resource_Bar_1;
		assetResourceBarFull = CR::AssetList::Resource_Bar_2;
		barFrames = 51;
	}
	else if (rSize == TinyResourceBar)
	{
		assetResourceBar = CR::AssetList::Arcade_Mode_Resource_Bar_3;
		assetResourceBarFull = CR::AssetList::Arcade_Mode_Resource_Bar_4;
		barFrames = 21;
	}
	
	resourceBarSprite = graphics_engine->CreateSprite1(false,800);
	resourceBarSprite->SetImage(assetResourceBar);
	resourceBarSprite->SetPositionAbsolute(offset.X(), offset.Y());
}

ResourceBar::~ResourceBar()
{
	resourceBarSprite->Release();
}

void ResourceBar::Update()
{
	if (!isFullAnimation)
	{
		int frameSet = (int) (((float)currValue / (float)maxValue) * (float)barFrames);
		resourceBarSprite->SetFrameSet(frameSet);
	}
}

void ResourceBar::Render()
{
	resourceBarSprite->Render();
}

void ResourceBar::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
}

void ResourceBar::PauseAnimation(bool pause)
{
	resourceBarSprite->PauseAnimation(pause);
}

void ResourceBar::SetMaxValue(int _value)
{
	maxValue = _value;
	if (currValue > maxValue)
		currValue = maxValue;
	
	SetResourceBarSprite();
}

void ResourceBar::AddToCurrValue(int _value)
{
	currValue += _value;
	if (currValue > maxValue)
		currValue = maxValue;
	
	SetResourceBarSprite();
}

void ResourceBar::ResetValue()
{
	currValue = 0;
	isFullAnimation = false;
	
	if (resourceBarSprite != NULL)
		resourceBarSprite->Release();
	
	resourceBarSprite = graphics_engine->CreateSprite1(false,800);
	resourceBarSprite->SetImage(assetResourceBar);
	resourceBarSprite->SetPositionAbsolute(offset.X(), offset.Y());
}

void ResourceBar::SetResourceBarSprite()
{	
	if (currValue >= maxValue)
	{
		if (!isFullAnimation)
		{
			if (resourceBarSprite != NULL)
				resourceBarSprite->Release();
			
			resourceBarSprite = graphics_engine->CreateSprite1(true,800);
			resourceBarSprite->SetImage(assetResourceBarFull);
			resourceBarSprite->SetPositionAbsolute(offset.X(), offset.Y());
		}
		
		isFullAnimation = true;
	}
	else
	{
		if (isFullAnimation)
		{
			if (resourceBarSprite != NULL)
				resourceBarSprite->Release();
			
			resourceBarSprite = graphics_engine->CreateSprite1(false,800);
			resourceBarSprite->SetImage(assetResourceBar);
			resourceBarSprite->SetPositionAbsolute(offset.X(), offset.Y());
		}
		
		isFullAnimation = false;
	}
}

bool ResourceBar::IsFull()
{
	return isFullAnimation;
}