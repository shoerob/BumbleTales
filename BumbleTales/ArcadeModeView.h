/*
 *  ArcadeModeView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "ResourcePuzzle.h"
#include "Input_Engine.h"
#include "ArcadeModeHUD.h"
#include "StarHUD.h"
#include "IView.h"
#include "StoryModeSaveInfo.h"
#include "ArcadeModeSaveInfo.h"
#include "SettingsSaveInfo.h"
#include "TrophySaveInfo.h"
#include "Trophies.h"
#include "ArcadeModeStructures.h"
#include "CharacterHUD.h"
#include "BuildingHUD.h"
#include <queue>
#include "Globals.h"
#include <vector>
#include "Sound.h"
using namespace std;

class ArcadeModeView : public IView
{
public:
	ArcadeModeView();
	virtual ~ArcadeModeView();
	
	// IView
	void Update();
	void Render();
	void PauseAnimation(bool pause);
	bool IsPaused() const { return m_isPaused; };
	
	void OnPauseButtonPressed();
	void OnTriggerScoreScreen();
	
	// ArcadeModeHud
	void OnTimerExpired();
	
	void PerformLevelUp();
	
	// Character HUD
	void OnCharacterHUDButtonPressed();
	
	// Building HUD
	void OnPowerUsed();
	
	// ResourcePuzzle
	void OnIncrementChain();
	void OnResourcesRetrieved(ResourceType rType, int cnt);
	void OnMoveMade();
	
	void LoadFromSaveInfo(ArcadeModeSaveInfo *saveInfo);
	void LoadStarBonusSaveInfo(StoryModeSaveInfo *saveInfo);
	void WriteToSaveInfo(ArcadeModeSaveInfo *saveInfo);
	void LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo);
	void WriteToTrophySaveInfo(TrophySaveInfo *saveInfo);
	void LoadFromSettingsSaveInfo(SettingsSaveInfo *saveInfo);
	
	Event OnShowPauseMenu;
	Event1<ArcadeModeScoreData*> OnShowScoreScreen;
	Event OnShowCharacterBonusMenu;
	
	void SetCharacterBonus(CharacterName charName, int level);
	
private:
	bool m_isPaused;
	ResourcePuzzle *resourcePuzzle;
	Sprite *backgroundSprite;
	Input_Button *pauseButton;
	ArcadeModeHUD *arcadeModeHUD;
	CharacterHUD *characterHUD;
	BuildingHUD *buildingHUD;
	bool m_performLevelUp;	
	bool m_isChaining;
	int m_chainCount;
	int m_currentMoveScore;
	int m_sessionMoves;
	int m_sessionPowers;
	float m_sessionTime;
	
	ArcadeModeScoreData *m_scoreData;
	
	float m_levelTime;
	
	int totalPlayTime;
	int storyTotalPlayTime;
	
	bool m_resetGame;
	bool playedArcadeReady;
	
	// ArcadeModeSaveInfo
	vector<int> highScores;
	vector<int> highScoresLevels;
	vector<int> blocksCleared;
	vector<int> storyBlocksCleared;
	
	int largestChain;
	int largestMatch;
	int maxPointsOnOneMove;
	int maxMovesInSession;
	int maxPowersUsedInSession;
	int longestSessionTime;
	
	Trophies *trophies;
	//bool gotMegaMatchTrophy;
	int megaBlocksCleared;
	int qTilesCleared;
	bool gotArtOfScoreTrophy;
	bool gotMasterStrategistTrophy;
	bool gotOutOfTheGatesTrophy;
	bool gotDareDevil;
	int oldFashionedLevels;
	bool completedLevelWithNoPowers;
	
	void DetectAndUpdateHighScores();
	void DetectAndUpdateTrophies();
	void ResetGame();
	
	CR::Graphics::Sprite *hudClipSprite;
};