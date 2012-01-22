/*
 *  ShopMenuView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ShopMenuView.h"
#include "AssetList.h"
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;

ShopMenuView::ShopMenuView()
{
	baseSprite = graphics_engine->CreateSprite1(false,500);
	baseSprite->SetImage(CR::AssetList::Shop_Menu_Base);
	baseSprite->SetPositionAbsolute(160, 240);
	
	closeButton = new Input_Button();
	closeButton->SetSpriteAndBounds(110, 428, CR::AssetList::Char_Bonus_Close_Button, 400);
	closeButton->OnClicked += Delegate(this, &ShopMenuView::OnCloseButtonPressed);
	//closeButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(closeButton);
	
	shopListing = new ShopListing(153, 70);
	shopListing->ShopItemPlusClicked += Delegate(this, &ShopMenuView::OnShopItemPlusClicked);
	//shopListing->SetPosition(153, 90);
	input_objects.push_back(shopListing);
	
	numberFont = new NumberFont(CR::AssetList::Shop_Star_Font, 400);
	numberFont->SetPosition(293, 27);
	
	hasWonGame = false;
	
	maxTag = graphics_engine->CreateSprite1(false, 400);
	maxTag->SetImage(CR::AssetList::Max_Tag);
	maxTag->SetPositionAbsolute(287, 29);
	
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::shopopen::ID);
	sound->Play();
}
 
ShopMenuView::~ShopMenuView()
{
	baseSprite->Release();
	maxTag->Release();
	delete closeButton;
	delete shopListing;
	delete numberFont;
}

void ShopMenuView::Update()
{
	shopListing->Update();
}

void ShopMenuView::Render()
{
	baseSprite->Render();
	closeButton->Render();
	shopListing->Render();
	
	if (hasWonGame)
	{
		maxTag->Render();
	}
	else
	{
		numberFont->RenderNumber(m_numStars);
	}
}

void ShopMenuView::OnShopItemPlusClicked()
{
	int newStarCount = m_numStars - 1;
	
	if (newStarCount >= 0)
	{
		//starsCounter->SetCount(newStarCount);
		m_numStars = newStarCount;
		shopListing->SetStarCount(newStarCount);
	}
}

void ShopMenuView::LoadFromSaveInfo(StoryModeSaveInfo *saveInfo)
{	
	CharacterLevels *cLevels = saveInfo->GetCharacterLevels();
	BuildingLevels *bLevels = saveInfo->GetBuildingLevels();
	shopListing->LoadFromLevelInfo(cLevels, bLevels);
	//delete cLevels;
	//delete bLevels;
	//shopListing->LoadFromSaveInfo(saveInfo);
	
	//starsCounter->SetCount(saveInfo->GetStars());
	m_numStars = saveInfo->GetStars();
	shopListing->SetStarCount(saveInfo->GetStars());
	hasWonGame = saveInfo->GetHasWonGame();
}

void ShopMenuView::WriteToSaveInfo(StoryModeSaveInfo *saveInfo)
{
	CharacterLevels *cLevels = saveInfo->GetCharacterLevels();
	BuildingLevels *bLevels = saveInfo->GetBuildingLevels();
	shopListing->WriteToLevelInfo(cLevels, bLevels);
	saveInfo->SetCharacterLevels(cLevels);
	saveInfo->SetBuildingLevels(bLevels);
	//delete cLevels;
	//delete bLevels;
	
	saveInfo->SetStars(m_numStars);
	//starsCounter->SetCount(saveInfo->GetStars());
}

void ShopMenuView::OnCloseButtonPressed()
{
	if (!hasWonGame && GetHasEverything())
	{
		// Display splash screen stating user has won game before closing this view and jumping to the scrapbook
		shopListing->SplashFinished += Delegate(this, &ShopMenuView::OnWinGameSplashDone);
		shopListing->DisplayWinGameSplash();
	}
	else
		OnClose();
	
	
}

bool ShopMenuView::GetHasEverything() const
{
	return shopListing->GetHasEverything();
}

void ShopMenuView::OnWinGameSplashDone()
{
	OnClose();
}
