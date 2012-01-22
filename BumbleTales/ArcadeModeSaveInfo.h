/*
 *  ArcadeModeSaveInfo.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include <vector>
#include "SaveInfo.h"
//#import <UIKit/UIKit.h>
using namespace std;

class ArcadeModeSaveInfo : public SaveInfo
{
public:
	ArcadeModeSaveInfo();
	virtual ~ArcadeModeSaveInfo();
	
	vector<int> GetHighScores() const { return m_highScores; }
	void SetHighScores(const vector<int> &scores) { m_highScores = scores; }
	
	vector<int> GetHighScoresLevels() const { return m_highScoreLevels; }
	void SetHighScoresLevels(const vector<int> &levels) { m_highScoreLevels = levels; }
	
	vector<int> GetBlocksCleared() const { return m_blocksCleared; }
	void SetBlocksCleared(const vector<int> &blocks) { m_blocksCleared = blocks; }
	
	int GetLargestChain() const { return m_largetsChain; }
	void SetLargestChain(int chain) { m_largetsChain = chain; }
	
	int GetLargestMatch() const { return m_largestMatch; }
	void SetLargestMatch(int match) { m_largestMatch = match; }
	
	int GetMaxPointsOnOneMove() const { return m_maxPointsOnOneMove; }
	void SetMaxPointsOnOneMove(int points) { m_maxPointsOnOneMove = points; }
	
	int GetMaxMovesInSession() const { return m_maxMovesInSession; }
	void SetMaxMovesInSession(int moves) { m_maxMovesInSession = moves; }
	
	int GetMaxPowersUsedInSession() const { return m_maxPowerUsedInSession; }
	void SetMaxPowersUsedInSession(int powers) { m_maxPowerUsedInSession = powers; }
	
	int GetLongestSessionTime() const { return m_longestSessionTime; }
	void SetLongestSessionTime(int seconds) { m_longestSessionTime = seconds; }
	
	int GetTotalPlayTime() { return m_totalPlayTime; }
	void SetTotalPlayTime(int _value) { m_totalPlayTime = _value; }
	
	virtual void Save();
	virtual void Load();
	virtual void Reset();

private:
	int m_largetsChain;
	int m_largestMatch;
	int m_maxPointsOnOneMove;
	int m_maxMovesInSession;
	int m_maxPowerUsedInSession;
	int m_longestSessionTime;
	int m_totalPlayTime;
	vector<int> m_blocksCleared;
	vector<int> m_highScores;
	vector<int> m_highScoreLevels;

	//NSString* GetDefaultsFilePath();
	//NSString* GetSaveFilePath();
};