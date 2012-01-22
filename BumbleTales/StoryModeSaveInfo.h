/*
 *  StoryModeSaveInfo.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "SaveInfo.h"
//#import <UIKit/UIKit.h>
#include "BuildingLevels.h"
#include "CharacterLevels.h"
#include <vector>
using namespace std;

class StoryModeSaveInfo : public SaveInfo
{
public:
	StoryModeSaveInfo();
	virtual ~StoryModeSaveInfo();
	
	int GetLevel() const { return m_level; }
	void SetLevel(int _value) { m_level = _value;
	}	
	int GetStars() const { return m_stars; }
	void SetStars(int _value) { m_stars = _value; }

	int GetStarsReceived() const { return m_starsRecieved; }
	void SetStarsReceived(int _value) { m_starsRecieved = _value; }
	
	int GetBronzeMedals() const { return m_bronzeMedals; }
	void SetBronzeMedals(int _value) { m_bronzeMedals = _value; }

	int GetSilverMedals() const { return m_silverMedals; }
	void SetSilverMedals(int _value) { m_silverMedals = _value; }
	
	int GetGoldMedals() const { return m_goldMedals; }
	void SetGoldMedals(int _value) { m_goldMedals = _value; }
	
	int GetTotalPlayTime() { return m_totalPlayTime; }
	void SetTotalPlayTime(int _value) { m_totalPlayTime = _value; }
	
	bool GetHasWonGame() { return m_hasWonGame; }
	void SetHasWonGame(bool _value) { m_hasWonGame = _value; }
	
	int GetLargestChain() const { return m_largestChain; }
	void SetLargestChain(int chain) { m_largestChain = chain; }
	
	int GetLargestMatch() const { return m_laregestMatch; }
	void SetLargestMatch(int match) { m_laregestMatch = match; }
	
	bool GetHasOpenedStore() { return m_hasOpenedStore; }
	void SetHasOpenedStore(bool _value) { m_hasOpenedStore = _value; }
	
	CharacterName GetCurrentCharacter() const { return m_currentCharacter; }
	void SetCurrentCharacter(CharacterName _value) { m_currentCharacter = _value; }
	
	BuildingLevels *GetBuildingLevels() { return &m_bLevels; }
	void SetBuildingLevels(BuildingLevels *_value) {}
	
	CharacterLevels *GetCharacterLevels() { return &m_cLevels; }
	void SetCharacterLevels(CharacterLevels *_value) {}
	
	vector<int> GetBlocksCleared() const { return m_blocksCleared; }
	void SetBlocksCleared(vector<int> &blocks) { m_blocksCleared = blocks; }
	
	virtual void Save();
	virtual void Load();
	virtual void Reset();

private:
	int m_level;
	int m_stars;
	int m_starsRecieved;
	int m_bronzeMedals;
	int m_silverMedals;
	int m_goldMedals;
	int m_totalPlayTime;
	bool m_hasWonGame;
	int m_largestChain;
	int m_laregestMatch;
	bool m_hasOpenedStore;
	CharacterName m_currentCharacter;
	vector<int> m_blocksCleared;

	BuildingLevels m_bLevels;;
	CharacterLevels m_cLevels;
	/*NSString* GetDefaultsFilePath();
	NSString* GetSaveFilePath();*/
};