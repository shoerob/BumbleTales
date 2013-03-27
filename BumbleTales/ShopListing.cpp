/*
 *  ShopListing.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/8/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ShopListing.h"
#include "AssetList.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;

ShopListing::ShopListing(int xLoc, int yLoc) : m_touchID(-1)
{
	minPos.X(xLoc);
	//minPos.Y(-(m_storeItems.size() * 75));
	minPos.Y(-(949 + 97));
	maxPos.X(xLoc);
	maxPos.Y(yLoc);
	
	m_scrollNub = new ScrollNub(287, 72, 276);
//	touch = NULL;
	
	infoSprite = graphics_engine->CreateSprite1(true,400);
	m_showInfoSprite = false;
	
	characterBonus = new CharacterBonus();
	newEntrySplash = new SplashScreen(CR::AssetList::Shop_New_Entry_Message, 1.5, 250);
	newEntrySplash->DesignSize(265, 90);
	newEntrySplash->SetPosition(160, 240);
	newEntrySplash->SplashFinished += Delegate(this, &ShopListing::OnNewEntrySplashFinished);
	
	yDownPos = 0;
	nubTouchMode = true;
	autoScroll = false;
	autoScrollStep = 0;
}

ShopListing::~ShopListing()
{
	for (int i = 0; i < m_storeItems.size(); i++)
		if (m_storeItems[i] != NULL)
			delete m_storeItems[i];
	
	delete m_scrollNub;
	delete characterBonus;
	delete newEntrySplash;
	//delete itemLockedSplash;
}

void ShopListing::Update()
{	
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
	{
		(*it)->Update();
	}
	
	m_scrollNub->Update();
	
	if (nubTouchMode)
	{
		float nubPercent = m_scrollNub->GetVerticalPercent();
		float yRange = maxPos.Y() - minPos.Y();
		float yPos = maxPos.Y() - (yRange * nubPercent);
		SetPosition(minPos.X(), yPos);
	}
	else
	{
		float y1 = maxPos.Y() - offset.Y();
		float y2 = maxPos.Y() - minPos.Y();
		m_scrollNub->SetVerticalPercent(y1 / y2);
		
		if (autoScroll)
		{
			SetPosition(offset.X(), offset.Y() + autoScrollStep);
		}
	}
	
	newEntrySplash->Update();
	//itemLockedSplash->Update();
}

void ShopListing::Render()
{
	graphics_engine->SetClipper(0, 116, 340, 304);
	
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
	{
		(*it)->Render();
	}
	
	graphics_engine->ClearClipper();
	
	m_scrollNub->Render();
	
	if (m_showInfoSprite)
		infoSprite->Render();
	
	newEntrySplash->Render();
	//itemLockedSplash->Render();
}

void ShopListing::DisplayWinGameSplash()
{
	// TODO: Change NewEntrySplash to display WIN GAME splash
	newEntrySplash->SetSplashAsset(CR::AssetList::Epilogue_Popup, 2);
	newEntrySplash->DesignSize(265, 173);
	newEntrySplash->StartSplash();
}

void ShopListing::SetPosition(float xLoc, float yLoc)
{
	offset.X(xLoc);
	offset.Y(yLoc);
	
	if (offset.Y() > maxPos.Y())
	{
		offset.Y(maxPos.Y());
		autoScroll = false;
		autoScrollStep = 0;
	}
	else if (offset.Y() < minPos.Y())
	{
		offset.Y(minPos.Y());
		autoScroll = false;
		autoScrollStep = 0;
	}
	
	int ySpacing = 0;
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
	{
		(*it)->SetPosition(offset.X(), offset.Y() + ySpacing);
		//ySpacing += 75;
		ySpacing += (*it)->GetHeight();
	}
	
	bounds.left = 20;
	bounds.top = 60;
	bounds.right = 260;
	bounds.bottom = 306;
}

void ShopListing::PauseAnimation(bool pause)
{
}

void ShopListing::OnShopItemClicked(ShopItem *item)
{
	if (dynamic_cast<BuildingItem*> (item) != NULL)
	{
		infoSprite->SetPositionAbsolute(160, 390);
		infoSprite->SetImage(item->GetInformationAsset());
		infoSprite->SetDesignSize(item->GetInformationDesignSize().X, item->GetInformationDesignSize().Y);
		infoSprite->SetFrame(item->GetLevel());
		m_showInfoSprite = true;
	}
	else if (dynamic_cast<CharacterItem*> (item) != NULL)
	{
		infoSprite->SetPositionAbsolute(160, 390);
		infoSprite->SetImage(item->GetInformationAsset());
		infoSprite->SetDesignSize(item->GetInformationDesignSize().X, item->GetInformationDesignSize().Y);
	
		CharacterName cName = ((CharacterItem*)item)->GetCharacterName();
		//infoSprite->SetFrame(item->GetLevel());
		//CharBonus cBonus = characterBonus->GetBonus(cName, item->GetLevel());
		infoSprite->SetFrame(characterBonus->GetBonusAsset(cName, item->GetLevel()));
		m_showInfoSprite = true;
	}
}

void ShopListing::OnShopItemPlusClicked(ShopItem *item)
{
	/*if (dynamic_cast<BuildingItem*> (item) != NULL)
	{
		
		BuildingItem *bItem = dynamic_cast<BuildingItem*> (item);
		
		if (IsBuildingLocked(bItem->GetBuildingName()))
		{
			Disabled(true);
			//itemLockedSplash->StartSplash();
			bItem->CancelLevelUp();
			return;
		}
	}*/
	
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	
	if ((rand() & 1) == 0)
		sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::purchase1::ID);
	else
		sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::purchase2::ID);
	
	sound->Play();
	
	
	if (dynamic_cast<CharacterItem*> (item) != NULL)
	{
		if (item->GetLevel() % 2 == 1)
		{
			Disabled(true);
			newEntrySplash->StartSplash();
		}
	}
	
	ShopItemPlusClicked();
}

void ShopListing::OnNewEntrySplashFinished()
{
	Disabled(false);
	SplashFinished();
}

bool ShopListing::GetHasEverything() const
{
	for(int i = 0; i < m_storeItems.size(); i++)
	{
		if (m_storeItems[i]->GetLevel() < 5 && m_storeItems[i]->GetLevel() != -1)
			return false;
	}
	
	return true;
}

void ShopListing::LoadFromLevelInfo(CharacterLevels *cLevels, BuildingLevels *bLevels)
{	
	// Add items to the store here
	m_storeItems.push_back(new SeparatorItem(BuildingHeader));
	
	int tLevel = bLevels->GetBuildingLevel(TownHall);
	m_storeItems.push_back(new BuildingItem(TownHall, tLevel, this));
	
	m_storeItems.push_back(new BuildingItem(PoliceStation, bLevels->GetBuildingLevel(PoliceStation), this));
	m_storeItems.push_back(new BuildingItem(Firehouse, bLevels->GetBuildingLevel(Firehouse), this));
	m_storeItems.push_back(new BuildingItem(Lodge, bLevels->GetBuildingLevel(Lodge), this));
	m_storeItems.push_back(new BuildingItem(Theatre, bLevels->GetBuildingLevel(Theatre), this));
	m_storeItems.push_back(new BuildingItem(Greenhouse, bLevels->GetBuildingLevel(Greenhouse), this));
	m_storeItems.push_back(new SeparatorItem(CharacterHeader));
	m_storeItems.push_back(new CharacterItem(Mayor, cLevels->GetCharacterLevel(Mayor)));//8
	m_storeItems.push_back(new CharacterItem(Elder, cLevels->GetCharacterLevel(Elder)));
	m_storeItems.push_back(new CharacterItem(Fireman, cLevels->GetCharacterLevel(Fireman)));
	m_storeItems.push_back(new CharacterItem(Dog, cLevels->GetCharacterLevel(Dog)));
	m_storeItems.push_back(new CharacterItem(Baker, cLevels->GetCharacterLevel(Baker)));
	m_storeItems.push_back(new CharacterItem(Teacher, cLevels->GetCharacterLevel(Teacher)));
	m_storeItems.push_back(new CharacterItem(Librarian, cLevels->GetCharacterLevel(Librarian)));
	m_storeItems.push_back(new CharacterItem(Romeo, cLevels->GetCharacterLevel(Romeo)));
	m_storeItems.push_back(new CharacterItem(Felicia, cLevels->GetCharacterLevel(Felicia)));
	m_storeItems.push_back(new CharacterItem(Bruiser, cLevels->GetCharacterLevel(Bruiser)));
	m_storeItems.push_back(new CharacterItem(Marla, cLevels->GetCharacterLevel(Marla)));
	m_storeItems.push_back(new CharacterItem(ChopChop, cLevels->GetCharacterLevel(ChopChop)));
	
	for (int i = 0; i < m_storeItems.size(); i++)
	{
		m_storeItems[i]->OnClicked += Delegate1<ShopListing, ShopItem*>(this,&ShopListing::OnShopItemClicked);
		m_storeItems[i]->OnPlusClicked += Delegate1<ShopListing, ShopItem*>(this,&ShopListing::OnShopItemPlusClicked);
	}
}

void ShopListing::WriteToLevelInfo(CharacterLevels *cLevels, BuildingLevels *bLevels)
{
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
	{
		if (dynamic_cast<BuildingItem*> (*it) != NULL)
		{
			BuildingItem* bItem = (BuildingItem*) (*it);
			bLevels->SetBuildingLevel(bItem->GetBuildingName(), bItem->GetLevel());
		}
		else if (dynamic_cast<CharacterItem*> (*it) != NULL)
		{
			CharacterItem* cItem = (CharacterItem*) (*it);
			cLevels->SetCharacterLevel(cItem->GetCharacterName(), cItem->GetLevel());
		}
	}
}

void ShopListing::SetStarCount(int _value)
{
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
		(*it)->SetStarCount(_value);
}

bool ShopListing::IsBuildingLocked(BuildingName bName)
{
	//BuildingName bName = bItem->GetBuildingName();
	//itemLockedSplash->SetFrameSet((int)bName);
	
	CharacterItem *cItem1;
	CharacterItem *cItem2;

	switch (bName)
	{
		case TownHall:
			cItem1 = (CharacterItem*)m_storeItems[8];
			cItem2 = (CharacterItem*)m_storeItems[9];			
			break;
		case PoliceStation:
			cItem1 = (CharacterItem*)m_storeItems[13];
			cItem2 = (CharacterItem*)m_storeItems[14];
			break;
		case Firehouse:
			cItem1 = (CharacterItem*)m_storeItems[10];
			cItem2 = (CharacterItem*)m_storeItems[11];
			break;
		case Lodge:
			cItem1 = (CharacterItem*)m_storeItems[12];
			cItem2 = (CharacterItem*)m_storeItems[19];
			break;
		case Theatre:
			cItem1 = (CharacterItem*)m_storeItems[17];
			cItem2 = (CharacterItem*)m_storeItems[15];
			break;
		case Greenhouse:
			cItem1 = (CharacterItem*)m_storeItems[16];
			cItem2 = (CharacterItem*)m_storeItems[18];
			break;
		default:
			return false;
			break;
	}
	
	if (cItem1->GetLevel() <= 0 || cItem2->GetLevel() <= 0)
		return true;
	else
		return false;
}

void ShopListing::TouchesBeganImpl(Touch &_touches)
{
	m_scrollNub->TouchesBeganImpl(_touches);
	if (m_scrollNub->IsDown()) 
	{
		nubTouchMode = true;
		autoScroll = false;
		return;
	}
	
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
		
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
	
		yDownPos = _touches.Y;
		nubTouchMode = false;
		autoScroll = false;
		autoScrollStep = 0;
			
		for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
			(*it)->TouchesBeganImpl(_touches);
	}
}

void ShopListing::TouchesMovedImpl(Touch &_touches)
{
	m_scrollNub->TouchesMovedImpl(_touches);
	if (m_scrollNub->IsDown()) return;
	
	if (m_touchID != -1 && m_touchID != _touches.ID)
		return;
	
	if (_touches.X > bounds.left && 
		_touches.X < bounds.right + bounds.left &&
		_touches.Y > bounds.top &&
		_touches.Y < bounds.bottom + bounds.top)
	{
		m_touchID = _touches.ID;
			
		float yDiff = _touches.Y - yDownPos;
		yDownPos = _touches.Y;
		autoScrollStep = yDiff;
			
		//float y1 = maxPos.Y() - (offset.Y() + yDiff);
		//float y2 = maxPos.Y() - minPos.Y();
		//m_scrollNub->SetVerticalPercent(y1 / y2);
		SetPosition(offset.X(), offset.Y() + yDiff);
			
		for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
			(*it)->TouchesMovedImpl(_touches);
	}
}

void ShopListing::TouchesEndedImpl(Touch &_touches)
{
	m_scrollNub->TouchesEndedImpl(_touches);
	if (m_scrollNub->IsDown()) return;
	
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
		(*it)->TouchesEndedImpl(_touches);
	
	if (_touches.ID == m_touchID)
	{
		if (abs(autoScrollStep) > 3)
		{
			autoScroll = true;
				
		}
			
		m_touchID = -1;
	}
}

/*
void ShopListing::TouchesBeganImpl(UIView *view, NSSet *touches)
{
	m_scrollNub->TouchesBegan(view, touches);
	if (m_scrollNub->IsDown()) 
	{
		nubTouchMode = true;
		autoScroll = false;
		return;
	}
	
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
	
			yDownPos = location.y;
			nubTouchMode = false;
			autoScroll = false;
			autoScrollStep = 0;
			
			for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
				(*it)->TouchesBegan(view, touches);
		}
	}
}

void ShopListing::TouchesMovedImpl(UIView *view, NSSet *touches)
{	
	m_scrollNub->TouchesMoved(view, touches);
	if (m_scrollNub->IsDown()) return;

	if (this->touch == NULL)
		return;
	
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
			
			int yDiff = location.y - yDownPos;
			yDownPos = location.y;
			autoScrollStep = yDiff;
			
			//float y1 = maxPos.Y() - (offset.Y() + yDiff);
			//float y2 = maxPos.Y() - minPos.Y();
			//m_scrollNub->SetVerticalPercent(y1 / y2);
			SetPosition(offset.X(), offset.Y() + yDiff);
			
			for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
				(*it)->TouchesMoved(view, touches);
		}
	}
}

void ShopListing::TouchesEndedImpl(UIView *view, NSSet *touches)
{
	m_scrollNub->TouchesEnded(view, touches);
	if (m_scrollNub->IsDown()) return;
	
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
		(*it)->TouchesEnded(view, touches);
	
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			if (abs(autoScrollStep) > 3)
			{
				autoScroll = true;
				
			}
			
			this->touch = NULL;
			break;
		}
	}
}

void ShopListing::TouchesCancelledImpl(UIView *view, NSSet *touches)
{
	m_scrollNub->TouchesCancelled(view, touches);
	if (m_scrollNub->IsDown()) return;
	
	for (vector<ShopItem*>::iterator it = m_storeItems.begin(); it != m_storeItems.end(); it++)
		(*it)->TouchesCancelled(view, touches);
	
	for (UITouch *touch in touches)
	{
		if (touch == this->touch)
		{
			this->touch = NULL;
			break;
		}
	}
}*/