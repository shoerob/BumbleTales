/*
 *  ScrapbookMenuView.cpp
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "ScrapbookMenuView.h"
#include "AssetList.h"
#include <algorithm>
#include "Sound.h"
#include "NewAssetList.h"
using namespace CR::Sound;
using namespace std;

extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;

ScrapbookMenuView::ScrapbookMenuView(bool wonGame)
{
	baseSprite = graphics_engine->CreateSprite1(false, 500);
	baseSprite->SetImage(CR::AssetList::Scrapbook_Background);
	baseSprite->SetPositionAbsolute(160, 240);
	
	rimSprite = graphics_engine->CreateSprite1(false, 400);
	rimSprite->SetImage(CR::AssetList::Scrapbook_Category_Rim);
	rimSprite->SetPositionAbsolute(55, 25);
	
	exitButton = new Input_Button();
	exitButton->SetSpriteAndBounds(112, 432, CR::AssetList::Scrapbook_Exit_Button, 300);
	exitButton->OnClicked += Delegate(this, &ScrapbookMenuView::OnExitButtonClicked);
	exitButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(exitButton);
	
	prevButton = new Input_Button();
	prevButton->SetSpriteAndBounds(6, 432, CR::AssetList::Scrapbook_LArrow_Button, 300);
	prevButton->OnClicked += Delegate(this, &ScrapbookMenuView::OnPrevButtonClicked);
	prevButton->SetSound(CR::AssetList::sounds::scrapbookpageturn1::ID);
	input_objects.push_back(prevButton);
	
	nextButton = new Input_Button();
	nextButton->SetSpriteAndBounds(217, 432, CR::AssetList::Scrapbook_RArrow_Button, 300);
	nextButton->OnClicked += Delegate(this, &ScrapbookMenuView::OnNextButtonClicked);
	nextButton->SetSound(CR::AssetList::sounds::scrapbookpageturn1::ID);
	input_objects.push_back(nextButton);
	
	charactersButton = new Input_Button();
	charactersButton->SetSpriteAndBounds(1, 5, CR::AssetList::Scrapbook_Characters_Button, 300);
	charactersButton->OnClicked += Delegate(this, &ScrapbookMenuView::OnCharactersButtonClicked);
	charactersButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(charactersButton);
	
	recordsButton = new Input_Button();
	recordsButton->SetSpriteAndBounds(106, 5, CR::AssetList::Scrapbook_Records_Button, 300);
	recordsButton->OnClicked += Delegate(this, &ScrapbookMenuView::OnRecordsButtonClicked);
	recordsButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(recordsButton);
	
	trophiesButton = new Input_Button();
	trophiesButton->SetSpriteAndBounds(211, 5, CR::AssetList::Scrapbook_Trophies_Button, 300);
	trophiesButton->OnClicked += Delegate(this, &ScrapbookMenuView::OnTrophiesButtonClicked);
	trophiesButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(trophiesButton);
	
	m_currChapter = new SBCharacterChapter(wonGame);
	
	ISound::Instance().PlaySong(CR::AssetList::music::BGMScrapbook::ID);
}

ScrapbookMenuView::~ScrapbookMenuView()
{
	baseSprite->Release();
	rimSprite->Release();
	delete exitButton;
	delete prevButton;
	delete nextButton;
	delete charactersButton;
	delete recordsButton;
	delete trophiesButton;
	delete m_currChapter;
	//delete characterLevels;
	//delete buildingLevels;
}

void ScrapbookMenuView::Update()
{
	m_currChapter->Update();
}

void ScrapbookMenuView::Render()
{
	baseSprite->Render();
	prevButton->Render();
	exitButton->Render();
	nextButton->Render();
	charactersButton->Render();
	recordsButton->Render();
	trophiesButton->Render();
	m_currChapter->Render();
	rimSprite->Render();
}

void ScrapbookMenuView::OnExitButtonClicked()
{
	OnExitClicked();
}

void ScrapbookMenuView::OnPrevButtonClicked()
{
	m_currChapter->PrevPage();
}

void ScrapbookMenuView::OnNextButtonClicked()
{
	m_currChapter->NextPage();
}

void ScrapbookMenuView::OnCharactersButtonClicked()
{
	if (m_currChapter->GetChapterType() == CharactersChapter)
		return;
	
	//UnregisterInput();
	delete m_currChapter;
	m_currChapter = new SBCharacterChapter();
	((SBCharacterChapter *)m_currChapter)->SetHasWonGame(storyModeSaveInfo->GetHasWonGame());
	((SBCharacterChapter *)m_currChapter)->SetCharacterLevels(characterLevels);
	
	rimSprite->SetPositionAbsolute(55, 25);
}

void ScrapbookMenuView::OnRecordsButtonClicked()
{
	if (m_currChapter->GetChapterType() == RecordsChapter)
		return;
	
	//UnregisterInput();
	delete m_currChapter;
	m_currChapter = new SBRecordChapter();
	((SBRecordChapter *)m_currChapter)->LoadFromArcadeSaveInfo(arcadeModeSaveInfo);
	((SBRecordChapter *)m_currChapter)->LoadFromStorySaveInfo(storyModeSaveInfo);
	
	rimSprite->SetPositionAbsolute(160, 25);
}

void ScrapbookMenuView::OnTrophiesButtonClicked()
{
	if (m_currChapter->GetChapterType() == TrophiesChapter)
		return;
	
	//UnregisterInput();
	delete m_currChapter;
	m_currChapter = new SBTrophyChapter();
	//input_objects.push_back((Input_Object*)m_currChapter);
	((SBTrophyChapter *)m_currChapter)->LoadFromTrophySaveInfo(trophySaveInfo);
	
	rimSprite->SetPositionAbsolute(265, 25);
}

/*
void ScrapbookMenuView::UnregisterInput()
{
	return;
	if (dynamic_cast<Input_Object*> (m_currChapter) != NULL)
	{
		vector<Input_Object*>::iterator unregObject = find(input_objects.begin(), input_objects.end(), (Input_Object*)m_currChapter);
		CR::Utility::UnorderedRemove(input_objects, unregObject);
	}
}*/

void ScrapbookMenuView::LoadFromSaveInfo(StoryModeSaveInfo *saveInfo)
{
	storyModeSaveInfo = saveInfo;
	
	characterLevels = saveInfo->GetCharacterLevels();
	buildingLevels = saveInfo->GetBuildingLevels();
	
	if (dynamic_cast<SBCharacterChapter*> (m_currChapter) != NULL)
	{
		((SBCharacterChapter *)m_currChapter)->SetCharacterLevels(characterLevels);
		((SBCharacterChapter *)m_currChapter)->SetHasWonGame(storyModeSaveInfo->GetHasWonGame());
	}
}

void ScrapbookMenuView::LoadFromArcadeSaveInfo(ArcadeModeSaveInfo *saveInfo)
{
	arcadeModeSaveInfo = saveInfo;
}

void ScrapbookMenuView::LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo)
{
	trophySaveInfo = saveInfo;
}
/*
void ScrapbookMenuView::TouchesBegan(UIView *view, NSSet *touches)
{
	if (dynamic_cast<Input_Object*> (m_currChapter) != NULL)
	{
		Input_Object* bleh = dynamic_cast<Input_Object*> (m_currChapter);//->TouchesBeganImpl(view, touches);
		bleh->TouchesBeganImpl(view, touches);
	}
}

void ScrapbookMenuView::TouchesMoved(UIView *view, NSSet *touches)
{
	if (dynamic_cast<Input_Object*> (m_currChapter) != NULL)
	{
		((Input_Object*)m_currChapter)->TouchesMovedImpl(view, touches);
	}
}

void ScrapbookMenuView::TouchesEnded(UIView *view, NSSet *touches)
{
	if (dynamic_cast<Input_Object*> (m_currChapter) != NULL)
	{
		((Input_Object*)m_currChapter)->TouchesEndedImpl(view, touches);
	}
}

void ScrapbookMenuView::TouchesCancelled(UIView *view, NSSet *touches)
{
	if (dynamic_cast<Input_Object*> (m_currChapter) != NULL)
	{
		((Input_Object*)m_currChapter)->TouchesCancelledImpl(view, touches);
	}
}
*/