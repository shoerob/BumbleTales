/*
 *  ShopItem.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/7/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ShopItem.h"
#include "AssetListFull.h"
extern CR::Graphics::GraphicsEngine *graphics_engine;

ShopItem::ShopItem(): m_touchID(-1)
{
	disableInput = false;
	itemSprite = graphics_engine->CreateSprite1(false,400);
	m_level = -1;
	m_height = 75;
	m_infoAsset = 0;
	starMeter = new StarMeter();
	
	plusButton = new Input_Button();
	plusButton->SetSpriteAndBounds(0, 0, CR::AssetList::Shop_Plus_Button, 400);
	plusButton->OnClicked += Delegate(this, &ShopItem::PlusClicked);
	
	plusDimmerSprite = graphics_engine->CreateSprite1(false,300);
	plusDimmerSprite->SetImage(CR::AssetList::Shop_Plus_Dimmer);
}

ShopItem::~ShopItem()
{
	itemSprite->Release();
	delete starMeter;
	delete plusButton;
	plusDimmerSprite->Release();
}

void ShopItem::Update()
{
	//SetPosition(offset.X(), offset.Y() - 1);
	starMeter->SetFilledStars(m_level);
	
	if (starMeter->GetStarIndicator() <= 0 || starMeter->GetFilledStars() >= 5)
		plusButton->Disabled(true);
	else
		plusButton->Disabled(false);
}

void ShopItem::Render()
{
	itemSprite->Render();
	
	if (m_level >= 0)
	{
		starMeter->Render();
		plusButton->Render();
		
		if (plusButton->Disabled())
			plusDimmerSprite->Render();
	}
}

void ShopItem::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	itemSprite->SetPositionAbsolute(offset.X(), offset.Y());
	starMeter->SetPosition(offset.X() + 10, offset.Y() + 15);
	plusButton->SetPosition(offset.X() + 82, offset.Y() - 5);
	plusDimmerSprite->SetPositionAbsolute(offset.X() + 100, offset.Y() + 13);
	bounds.top = yLoc - itemSprite->GetFrameHeight() / 2;
	bounds.bottom = itemSprite->GetFrameHeight();
	bounds.left = xLoc - itemSprite->GetFrameWidth() / 2;
	bounds.right = itemSprite->GetFrameWidth();
}

void ShopItem::PauseAnimation(bool pause)
{
}

int ShopItem::GetLevel() const
{
	return m_level;
}

int ShopItem::GetHeight() const
{
	return m_height;
}

int ShopItem::GetInformationAsset()
{
	return m_infoAsset;
}

void ShopItem::SetStarCount(int _value)
{
	starMeter->SetStarIndicator(_value);
}

void ShopItem::PlusClicked()
{
	if (starMeter->GetStarIndicator() > 0 && m_level < 5)
	{
		m_level++;
		OnPlusClicked(this);
	}
}

void ShopItem::TouchesBeganImpl(Touch &_touches)
{
	if (disableInput) return;
	
	plusButton->TouchesBegan(_touches);
	
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
			
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
			
		OnClicked(this);
	}
}

void ShopItem::TouchesMovedImpl(Touch &_touches)
{
	if (disableInput) return;
	
	plusButton->TouchesMoved(_touches);
	
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
			
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
			
		OnClicked(this);
	}
}

void ShopItem::TouchesEndedImpl(Touch &_touches)
{
	if (disableInput) return;
	
	plusButton->TouchesEnded(_touches);
	
	if (_touches.ID == m_touchID)
	{
		m_touchID = -1;
	}
}

/*
void ShopItem::TouchesBegan(UIView *view, NSSet *touches)
{
	if (disableInput) return;
	
	plusButton->TouchesBegan(view, touches);
	
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		CGPoint location = [touch locationInView: view];
		
		if (location.x > bounds.left && 
			location.x < bounds.right + bounds.left &&
			location.y > bounds.top &&
			location.y < bounds.bottom + bounds.top)
		{
			this->touch = touch;
			
			OnClicked(this);
		}
	}
}

void ShopItem::TouchesMoved(UIView *view, NSSet *touches)
{
	if (disableInput) return;
	
	plusButton->TouchesMoved(view, touches);
	
	for (UITouch *touch in touches)
	{
		if (this->touch != NULL && touch != this->touch)
			continue;
		
		CGPoint location = [touch locationInView: view];
		
		if (location.x > bounds.left && 
			location.x < bounds.right + bounds.left &&
			location.y > bounds.top &&
			location.y < bounds.bottom + bounds.top)
		{
			this->touch = touch;
			
			OnClicked(this);
		}
	}
}

void ShopItem::TouchesEnded(UIView *view, NSSet *touches)
{
	if (disableInput) return;
	
	plusButton->TouchesEnded(view, touches);
	
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->touch = NULL;
			break;
		}
	}
}

void ShopItem::TouchesCancelled(UIView *view, NSSet *touches)
{
	if (disableInput) return;
	
	plusButton->TouchesCancelled(view, touches);
	
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->touch = NULL;
			break;
		}
	}
}*/