/*
 *  SBCharacterChapter.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "SBCharacterChapter.h"
#include "AssetList.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

SBCharacterChapter::SBCharacterChapter(bool wonGame)
{	
	m_currPage = 0;
	pageSprite = graphics_engine->CreateSprite1(false, 300);
	
	scrapbookTags = graphics_engine->CreateSprite1(false, 300);
	scrapbookTags->SetImage(CR::AssetList::Scrapbook_Tags_1);
	scrapbookTags->SetPositionAbsolute(104, 60);
	
	scrapbookTags2 = graphics_engine->CreateSprite1(false, 300);
	scrapbookTags2->SetImage(CR::AssetList::Scrapbook_Tags_2);
	scrapbookTags2->SetPositionAbsolute(275, 60);
	
	hasWonGame = false;
	justWonGame = wonGame;

}

SBCharacterChapter::~SBCharacterChapter()
{
	for (int i = 0; i < characterTales.size(); i++)
		delete characterTales[i];
	
	pageSprite->Release();
	scrapbookTags->Release();
	scrapbookTags2->Release();
}

void SBCharacterChapter::Update()
{
}

void SBCharacterChapter::Render()
{
	//int currCharacter = m_currPage / 3;
	
	//if (characterTales.size() > currCharacter)
	//	characterTales[currCharacter]->Render();
	pageSprite->Render();
	scrapbookTags->Render();
	scrapbookTags2->Render();
}

void SBCharacterChapter::NextPage()
{
	m_currPage++;
	
	if (hasWonGame)
	{
		if (m_currPage > 38)
			m_currPage = 0;
	}
	else
	{
		if (m_currPage > 35)
			m_currPage = 0;
	}
	
	UpdatePage();
}

void SBCharacterChapter::PrevPage()
{
	m_currPage--;
	
	if (hasWonGame)
	{
		if (m_currPage < 0)
			m_currPage = 38;
	}
	else
	{
		if (m_currPage < 0)
			m_currPage = 35;
	}
	
	UpdatePage();
}

void SBCharacterChapter::UpdatePage()
{
	int currCharacter = m_currPage / 3;
	int characterPage = m_currPage % 3;
	
	if (currCharacter < characterTales.size())
		characterTales[currCharacter]->SetPage(characterPage, pageSprite);
	
	scrapbookTags->SetFrameSet(currCharacter);
	scrapbookTags2->SetFrameSet(characterPage);
}

ScrapbookChapter SBCharacterChapter::GetChapterType()
{
	return CharactersChapter;
}

void SBCharacterChapter::SetCharacterLevels(CharacterLevels *characterLevels)
{
	m_characterLevels = characterLevels;
	
	for (int i = 0; i < characterTales.size(); i++)
		delete characterTales[i];
	
	characterTales.clear();
	
	for (int i = 0; i < 12; i++)
	{
		characterTales.push_back(new CharacterTale((CharacterName)i, m_characterLevels->GetCharacterLevel((CharacterName)i)));
	}
	
	characterTales.push_back(new CharacterTale(WonGameChapter, 5));
	
	if (justWonGame)
		m_currPage = 36;
	else
		m_currPage = 0;
	UpdatePage();
}

void SBCharacterChapter::SetHasWonGame(bool _value)
{
	hasWonGame = _value; 
}