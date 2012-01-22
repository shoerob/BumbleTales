/*
 *  SBCharacterChapter.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "IScrapbookChapter.h"
#include "Graphics.h"
#include "CharacterLevels.h"
#include "CharacterTale.h"
#include <vector>
using namespace std;

class SBCharacterChapter : public IScrapbookChapter
{
public:
	SBCharacterChapter(bool wonGame = false);
	virtual ~SBCharacterChapter();
	
	// IScrapbookChapter
	void Update();
	void Render();
	void NextPage();
	void PrevPage();
	ScrapbookChapter GetChapterType();
	void SetCharacterLevels(CharacterLevels *characterLevels);
	void UpdatePage();
	void SetHasWonGame(bool _value);
	
private:
	CR::Graphics::Sprite *pageSprite;
	CharacterLevels *m_characterLevels;
	vector<CharacterTale*> characterTales;
	CR::Graphics::Sprite *scrapbookTags;
	CR::Graphics::Sprite *scrapbookTags2;
	int m_currPage;
	bool hasWonGame;
	bool justWonGame;
};