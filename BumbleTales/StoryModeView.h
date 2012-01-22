/*
 *  StoryModeView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#include "ResourcePuzzle.h"
#include "Input_Engine.h"
#include "StoryModeHUD.h"
#include "StarHUD.h"
#include "IView.h"
#include "StoryModeSaveInfo.h"
#include "ArcadeModeSaveInfo.h"
#include "SettingsSaveInfo.h"
#include "TrophySaveInfo.h"
#include "StoryModeStructures.h"
#include "CharacterHUD.h"
#include "BuildingHUD.h"
#include <queue>
#include "Globals.h"
#include "SplashScreen.h"

class StoryModeView : public IView
{
public:
	StoryModeView();
	virtual ~StoryModeView();
	
	// IView
	void Update();
	void Render();
	void PauseAnimation(bool pause);
	bool IsPaused() const { return m_isPaused; };
	

	void OnPauseButtonPressed();
	void OnTriggerScoreScreen();
	
	// Star HUD
	void OnStarHUDButtonPressed();
	void PerformLevelUp();
	
	// Character HUD
	void OnCharacterHUDButtonPressed();
	
	// Building HUD
	void OnPowerUsed();
	
	// ResourcePuzzle
	void OnIncrementChain();
	void OnResourcesRetrieved(ResourceType rType, int cnt);
	
	void LoadFromSaveInfo(StoryModeSaveInfo *saveInfo);
	void LoadStarBonusSaveInfo(StoryModeSaveInfo *saveInfo);
	void WriteToSaveInfo(StoryModeSaveInfo *saveInfo);
	void LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo);
	void WriteToTrophySaveInfo(TrophySaveInfo *saveInfo);
	void LoadArcadeBlocksCleared(ArcadeModeSaveInfo *saveInfo);
	void LoadFromSettingsSaveInfo(SettingsSaveInfo *saveInfo);
	
	Event OnShowPauseMenu;
	Event1<StoryModeScoreData*> OnShowScoreScreen;
	Event OnShowCharacterBonusMenu;
	Event OnShowStore;
	
	void SetCharacterBonus(CharacterName charName, int level);
	
	void TriggerTouchToEnterStore();
	int GetCurrentLevel() { return storyModeHUD->GetLevel(); }
	
private:
	bool m_isPaused;
	ResourcePuzzle *resourcePuzzle;
	Sprite *backgroundSprite;
	Input_Button *pauseButton;
	StarHUD *starHUDButton;
	StoryModeHUD *storyModeHUD;
	CharacterHUD *characterHUD;
	BuildingHUD *buildingHUD;
	bool m_performLevelUp;	
	bool m_isChaining;
	int m_chainCount;
	Trophies *trophies;
	StoryModeScoreData *m_scoreData;
	
	float m_levelTime;
	
	int totalPlayTime;
	int arcadeTotalPlayTime;
	
	void DetectAndUpdateMedals();
	MedalType GetMedalForTile(ResourceType rType);
	void DetectAndUpdateTrophies();
	
	//StoryModeSaveInfo
	vector<int> blocksCleared;
	vector<int> arcadeBlocksCleared;

	int largestChain;
	int largestMatch;
	
	//bool gotMegaMatchTrophy;
	int megaBlocksCleared;
	int qTilesCleared;
	
	int bronzeMedals;
	int silverMedals;
	int goldMedals;
	
	int receivedStars;
	bool gotWellRounded;
	bool gotMasterStoryTeller;
	
	bool hasOpenedStore;
	SplashScreen *touchToEnterShop;
	
	CR::Graphics::Sprite *hudClipSprite;
};