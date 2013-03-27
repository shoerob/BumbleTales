/*
 *  ArcadeModeView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#include "ArcadeModeView.h"
#include "ResourceTile.h"
#include "Sound.h"
#include "AssetList.h"
using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;

ArcadeModeView::ArcadeModeView()
{
	backgroundSprite = graphics_engine->CreateSprite1(false,1000);
	backgroundSprite->SetImage(CR::AssetList::Story_Mode_Background);
	backgroundSprite->SetDesignSize(320, 480);
	backgroundSprite->SetPositionAbsolute(160, 240);
	
	resourcePuzzle = new ResourcePuzzle(3, 70, 1);
	input_objects.push_back(resourcePuzzle);
	resourcePuzzle->OnIncrementChain += Delegate(this, &ArcadeModeView::OnIncrementChain);
	resourcePuzzle->ResourcesRetrieved += Delegate2<ArcadeModeView, ResourceType, int>(this,&ArcadeModeView::OnResourcesRetrieved);
	resourcePuzzle->MoveMade += Delegate(this, &ArcadeModeView::OnMoveMade);
	
	pauseButton = new Input_Button();
	pauseButton->SetSpriteAndBounds(260, 10, CR::AssetList::Pause_Button, 900);
	pauseButton->DesignSize(53, 51);
	input_objects.push_back(pauseButton);
	pauseButton->OnClicked += Delegate(this, &ArcadeModeView::OnPauseButtonPressed);
	
	arcadeModeHUD = new ArcadeModeHUD(130, 32);
	arcadeModeHUD->TimerExpired += Delegate(this, &ArcadeModeView::OnTimerExpired);
	
	characterHUD = new CharacterHUD();
	characterHUD->SetPosition(245, 397);
	input_objects.push_back(characterHUD);
	characterHUD->OnClicked += Delegate(this, &ArcadeModeView::OnCharacterHUDButtonPressed);
	
	buildingHUD = new BuildingHUD(resourcePuzzle);
	buildingHUD->SetPosition(4, 395);
	input_objects.push_back(buildingHUD);
	buildingHUD->OnPowerUsed += Delegate(this, &ArcadeModeView::OnPowerUsed);
	
	m_isPaused = false;
	m_performLevelUp = false;
	
	m_chainCount = 0;
	m_scoreData = new ArcadeModeScoreData();
	
	m_levelTime = 0;
	m_currentMoveScore = 0;
	m_sessionMoves = 0;
	m_sessionPowers = 0;
	m_sessionTime = 0;
	//gotMegaMatchTrophy = false;
	qTilesCleared = 0;
	gotArtOfScoreTrophy = false;
	gotMasterStrategistTrophy = false;
	gotOutOfTheGatesTrophy = false;
	gotDareDevil = false;
	oldFashionedLevels = 0;
	completedLevelWithNoPowers = true;
	megaBlocksCleared = 0;
	
	hudClipSprite = graphics_engine->CreateSprite1(false, 925);
	hudClipSprite->SetImage(CR::AssetList::Story_Mode_HUD_Top);
	hudClipSprite->SetDesignSize(320, 70);
	hudClipSprite->SetPositionAbsolute(160, 35);
	
	playedArcadeReady = false;
	m_resetGame = false;
}

ArcadeModeView::~ArcadeModeView()
{
	hudClipSprite->Release();
	backgroundSprite->Release();
	delete resourcePuzzle;
	delete arcadeModeHUD;
	delete pauseButton;
	delete m_scoreData;
	delete characterHUD;
	delete buildingHUD;
}

void ArcadeModeView::Update()
{	
	if (m_resetGame)
	{
		ResetGame();
	}
	
	if (!resourcePuzzle->IsPuzzleAnimating())
	{
		if (m_isChaining) // the chain ended since the puzzle finished animating
		{
			arcadeModeHUD->AddToScore(m_chainCount * m_currentMoveScore);
			m_currentMoveScore += m_chainCount * m_currentMoveScore;
			
			// store the largest chain information in scoring
			//if (m_chainCount > m_scoreInfo->GetLargestChain())
			//	m_scoreInfo->SetLargestChain(m_chainCount);
			if (m_chainCount > m_scoreData->largestChain)
			{
				m_scoreData->largestChain = m_chainCount;
				
				// store the largest chain as a record if possible
				if (m_scoreData->largestChain > largestChain)
					largestChain = m_scoreData->largestChain;
			}
			
			m_chainCount = 0;
			m_isChaining = false;
		}
		
		// Detect max points on one move
		if (m_currentMoveScore > maxPointsOnOneMove)
		{
			maxPointsOnOneMove = m_currentMoveScore;
		}
		
		if (m_currentMoveScore >= 250)
			gotArtOfScoreTrophy = true;
		if (m_currentMoveScore >= 1000)
			gotMasterStrategistTrophy = true;
		
		m_currentMoveScore = 0;
	}
	
	if (m_performLevelUp)
	{
		// wait for the puzzle to finish chaining/animating to show the level up screen
		if (!resourcePuzzle->IsPuzzleAnimating())
		{
			m_performLevelUp = false;
			PerformLevelUp();
			//OnTriggerScoreScreen();
		}
	}
	
	if (!m_isPaused)
	{
		m_levelTime += Globals::Instance().GetTimer()->GetTimePassed();
		m_sessionTime += Globals::Instance().GetTimer()->GetTimePassed();
	}
	
	resourcePuzzle->Update();
	arcadeModeHUD->Update();
	//starHUDButton->Update();
	characterHUD->Update();
	buildingHUD->Update();
	
	if (!playedArcadeReady)
	{
		std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
		sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::ArcadeReady::ID);
		sound->Play();
		playedArcadeReady = true;
	}
}

void ArcadeModeView::Render()
{
	backgroundSprite->Render();
	resourcePuzzle->Render();
	pauseButton->Render();
	arcadeModeHUD->Render();
	//starHUDButton->Render();
	characterHUD->Render();
	buildingHUD->Render();
	hudClipSprite->Render();
}

void ArcadeModeView::OnIncrementChain()
{
	m_isChaining = true;
	m_chainCount++;
}

void ArcadeModeView::OnResourcesRetrieved(ResourceType rType, int cnt)
{	
	// CHAIN Calculations
	//if (rType != QTile)
	//{
	//	m_isChaining = true;
	//	m_chainCount += cnt / 3;
	// TODO: Add/Start Chain Notify Animation Here for each chain!
	//}
	
	// Detect if this was the largest match
	if (cnt > largestMatch)
		largestMatch = cnt;
	
	if (rType == QTile)
	{
		blocksCleared[rType] += cnt;
		qTilesCleared += cnt;
	}
	
	// Resource Count Calculations
	if ((int) rType < 6)
	{
		cnt += characterHUD->GetCharacterBonus().GetResourceBonus(rType);
		arcadeModeHUD->AddResources(rType, cnt);
		arcadeModeHUD->AddToScore(cnt * 25);
		m_currentMoveScore += (cnt * 25);
		blocksCleared[(int)rType] += cnt;
	}
	
	m_scoreData->SetResourceCount(rType, m_scoreData->GetResourceCount(rType) + cnt);
	
	// A multi-tile was retrieved, player gets 3 of every basic resource
	if (rType == MTile)
	{
		blocksCleared[(int)rType] += cnt;
		megaBlocksCleared += cnt;
		//if (cnt >=5)
		//	gotMegaMatchTrophy = true;
		
		for (int i = 0; i < 6; i++)
		{
			int rBonus = characterHUD->GetCharacterBonus().GetResourceBonus((ResourceType)i);
			arcadeModeHUD->AddResources((ResourceType)i, 3 * cnt + rBonus);
			m_scoreData->SetResourceCount((ResourceType)i, m_scoreData->GetResourceCount((ResourceType)i) + 3 * cnt + rBonus);
			arcadeModeHUD->AddToScore(((3 * cnt) + rBonus) * 25);
			m_currentMoveScore += (((3 * cnt) + rBonus) * 25);
			blocksCleared[i] += (3 * cnt) + rBonus;
		}
	}
	
	//DEBUG: Level up (needs to play level up animation first)
	if (arcadeModeHUD->ResourcesGathered())
	{
		m_performLevelUp = true;
	}
}

void ArcadeModeView::OnMoveMade()
{
	m_sessionMoves++;
}

void ArcadeModeView::OnPauseButtonPressed()
{
	OnShowPauseMenu();
}

void ArcadeModeView::OnTriggerScoreScreen()
{	
	
	resourcePuzzle->DropTouchValue();
	OnShowScoreScreen(m_scoreData);
}

void ArcadeModeView::PauseAnimation(bool pause)
{
	m_isPaused = pause;
	resourcePuzzle->PauseAnimation(pause);
	arcadeModeHUD->PauseAnimation(pause);
	//starHUDButton->PauseAnimation(pause);
	buildingHUD->PauseAnimation(pause);
}

void ArcadeModeView::OnCharacterHUDButtonPressed()
{
	OnShowCharacterBonusMenu();
}

void ArcadeModeView::OnPowerUsed()
{
	m_scoreData->powersUsed++;
	m_sessionPowers++;
	completedLevelWithNoPowers = false;
}

void ArcadeModeView::PerformLevelUp()
{
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::levelupfanfare::ID);
	sound->Play();
	
	if (m_levelTime <= 10)
		gotOutOfTheGatesTrophy = true;
	
	if (arcadeModeHUD->GetCurrTime() <= 5)
		gotDareDevil = true;
	
	if (completedLevelWithNoPowers)
		oldFashionedLevels++;
	else
		oldFashionedLevels = 0;
	
	arcadeModeHUD->AddToScore(arcadeModeHUD->GetLevel() * 200);
	arcadeModeHUD->PerformLevelUp();
	completedLevelWithNoPowers = true;
}

void ArcadeModeView::OnTimerExpired()
{	
	m_scoreData->levelTime = m_levelTime;
	m_scoreData->level = arcadeModeHUD->GetLevel();
	m_scoreData->score = arcadeModeHUD->GetScore();
	
	totalPlayTime += m_levelTime;
	m_levelTime = 0;
	DetectAndUpdateHighScores();
	DetectAndUpdateTrophies();
	megaBlocksCleared = 0;
	qTilesCleared = 0;
	m_resetGame = true;
	
	OnTriggerScoreScreen();
}

void ArcadeModeView::ResetGame()
{
	m_scoreData->Reset();
	m_resetGame = false;
	arcadeModeHUD->Reset();
	resourcePuzzle->ResetPuzzle();
	buildingHUD->ResetBuildingDelays();
	qTilesCleared = 0;
	megaBlocksCleared = 0;
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::ArcadeReady::ID);
	sound->Play();
}

void ArcadeModeView::DetectAndUpdateHighScores()
{
	int currScore = arcadeModeHUD->GetScore();
	int insertIndex = 0;
	
	// high score list is in order, this loops from highest to lowest score
	for (int i = 0; i < highScores.size(); i++)
	{
		if (currScore > highScores[i])
		{
			m_scoreData->newHighScore = true;
			insertIndex = i;
			
			//shift the rest of the scores down, and insert this one
			for (int j = highScores.size() - 1; j > i; j--)
			{
				highScores[j] = highScores[j-1];
				highScoresLevels[j] = highScoresLevels[j-1];
			}
			
			highScores[insertIndex] = m_scoreData->score;
			highScoresLevels[insertIndex] = m_scoreData->level;
			break;
		}
	}
}

void ArcadeModeView::DetectAndUpdateTrophies()
{
	vector<TrophyName> gotTrophies;
	
	// CityMaster - STORY MODE ONLY
	// WellRounded - STORY MODE ONLY
	
	// IHeartBumbles
	if (buildingHUD->GetIHeartBumblesTrophy())
		gotTrophies.push_back(IHeartBumblesTrophy);
	
	// BrickBreaker
	if (blocksCleared[Brick] + storyBlocksCleared[Brick] >= 5000)
		gotTrophies.push_back(BrickBreakerTrophy);
	
	// WoodChipper
	if (blocksCleared[Wood] + storyBlocksCleared[Wood] >= 6000)
		gotTrophies.push_back(WoodChipperTrophy);
	
	// LeafRaker
	if (blocksCleared[Leaf] + storyBlocksCleared[Leaf] >= 7000)
		gotTrophies.push_back(LeafRakerTrophy);
	
	// GoldMiner
	if (blocksCleared[Gold] + storyBlocksCleared[Gold] >= 8000)
		gotTrophies.push_back(GoldMinerTrophy);
	
	// CrystalClearer
	if (blocksCleared[Crystal] + storyBlocksCleared[Crystal] >= 9000)
		gotTrophies.push_back(CrystalClearerTrophy);
	
	// GemCollector
	if (blocksCleared[Diamond] + storyBlocksCleared[Diamond] >= 10000)
		gotTrophies.push_back(GemCollectorTrophy);
	
	// MasterPiece
	if (blocksCleared[MTile] + storyBlocksCleared[MTile] >= 500)
		gotTrophies.push_back(MasterPieceTrophy);
	
	// Resourceful
	if (blocksCleared[Brick] + blocksCleared[Wood] + blocksCleared[Leaf] + blocksCleared[Gold] + blocksCleared[Crystal] + blocksCleared[Diamond] + blocksCleared[MTile] + blocksCleared[QTile] +
		storyBlocksCleared[Brick] + storyBlocksCleared[Wood] + storyBlocksCleared[Leaf] + storyBlocksCleared[Gold] + storyBlocksCleared[Crystal] + storyBlocksCleared[Diamond] +
		storyBlocksCleared[MTile] + storyBlocksCleared[QTile] >= 100000)
	{
		gotTrophies.push_back(ResourcefulTrophy);
	}
	
	// OnTheLevel
	if (m_scoreData->level >= 50)
		gotTrophies.push_back(OnTheLevelTrophy);
	
	// Centurion
	if (m_scoreData->level >= 100)
		gotTrophies.push_back(CenturionTrophy);
	
	// MedalManiac
	//if ((bronzeMedals + silverMedals + goldMedals) >= 500)
	//{
	//	gotTrophies.push_back(MedalManiacTrophy);
	//}
	
	// HeavyMedal
	//if (goldMedals >= 200)
	//{
	//	gotTrophies.push_back(HeavyMedalTrophy)
	//}
	
	// Power Hungry
	if (m_scoreData->powersUsed >= 10)
		gotTrophies.push_back(PowerHungryTrophy);
	
	// Simple Chain
	if (m_scoreData->largestChain >= 3)
		gotTrophies.push_back(SimpleChainTrophy);
	
	// Chain Reaction
	if (m_scoreData->largestChain >= 5)
		gotTrophies.push_back(ChainReactionTrophy);
	
	// Monster Chain
	if (m_scoreData->largestChain >= 10)
		gotTrophies.push_back(MonsterChainTrophy);
	
	// High Five
	if (largestMatch >= 5)
		gotTrophies.push_back(HighFiveTrophy);
	
	// Mega Match
	if (megaBlocksCleared >= 5)
		gotTrophies.push_back(MegaMatchTrophy);
	
	// The Wild Bunch
	if (qTilesCleared >= 5)
		gotTrophies.push_back(TheWildBunchTrophy);
	
	// Time on Your Hands
	if (totalPlayTime + storyTotalPlayTime >= 7200)
		gotTrophies.push_back(TimeOnYourHandsTrophy);
	
	// Arcade Newbie
	if (m_scoreData->score >= 10000)
		gotTrophies.push_back(ArcadeNewbieTrophy);
	
	// Arcade Pro
	if (m_scoreData->score >= 100000)
		gotTrophies.push_back(ArcadeProTrophy);
	
	// Arcade Master
	if (m_scoreData->score >= 500000)
		gotTrophies.push_back(ArcadeMasterTrophy);
	
	// The Art of Score
	if (gotArtOfScoreTrophy)
		gotTrophies.push_back(TheArtOfScoreTrophy);
	
	// Master Strategist
	if (gotMasterStrategistTrophy)
		gotTrophies.push_back(MasterStrategistTrophy);
	
	// Great Streak
	if (m_scoreData->levelTime >= 180)
		gotTrophies.push_back(GreatStreakTrophy);
	
	// Wicked Streak
	if (m_scoreData->levelTime >= 300)
		gotTrophies.push_back(WickedStreakTrophy);
	
	// Insane Streak
	if (m_scoreData->levelTime >= 600)
		gotTrophies.push_back(InsaneStreakTrophy);
	
	// Energized
	if (m_scoreData->level >= 25)
		gotTrophies.push_back(EnergizedTrophy);
	
	// Out of the Gates
	if (gotOutOfTheGatesTrophy)
		gotTrophies.push_back(OutOfTheGatesTrophy);
	
	// Dare Devil
	if (gotDareDevil)
		gotTrophies.push_back(DareDevilTrophy);
	
	// Old Fashioned
	if (oldFashionedLevels >= 10)
		gotTrophies.push_back(OldFashionedTrophy);
	
	// Determine if any new trophies were gotten
	for (int i = 0; i < gotTrophies.size(); i++)
	{
		if (trophies->GetTrophy(gotTrophies[i]) == false)
		{
			trophies->SetTrophy(gotTrophies[i], true);
			m_scoreData->gotTrophy = true;
		}
	}
}

void ArcadeModeView::SetCharacterBonus(CharacterName charName, int level)
{
	characterHUD->SetCharacter(charName, level);
	resourcePuzzle->SetDropRateBonusType(characterHUD->GetCharacterBonus().dropRateBonusType);
}

void ArcadeModeView::LoadFromSaveInfo(ArcadeModeSaveInfo *saveInfo)
{	
	/*
	 vector<int> highScoresLevels;
	 int largestChain;
	 int largestMatch;
	 int maxPointsOnOneMove;
	 int maxMovesInSession;
	 int maxPowersUsedInSession;
	 int longestSessionTime;
	 */
	//arcadeModeHUD->SetLevel(saveInfo->GetLevel());
	
	highScores = saveInfo->GetHighScores();
	highScoresLevels = saveInfo->GetHighScoresLevels();
	largestChain = saveInfo->GetLargestChain();
	largestMatch = saveInfo->GetLargestMatch();
	maxPointsOnOneMove = saveInfo->GetMaxPointsOnOneMove();
	maxMovesInSession = saveInfo->GetMaxMovesInSession();
	maxPowersUsedInSession = saveInfo->GetMaxPowersUsedInSession();
	longestSessionTime = saveInfo->GetLongestSessionTime();
	blocksCleared = saveInfo->GetBlocksCleared();
	totalPlayTime = saveInfo->GetTotalPlayTime();
	
	//LoadStarBonusSaveInfo(saveInfo);
	//buildingHUD->ResetBuildingDelays();
}

void ArcadeModeView::LoadStarBonusSaveInfo(StoryModeSaveInfo *saveInfo)
{
	CharacterLevels *cLevels = saveInfo->GetCharacterLevels();
	CharacterName cChar = saveInfo->GetCurrentCharacter();
	characterHUD->SetCharacter(cChar, cLevels->GetCharacterLevel(cChar));
	//delete cLevels;
	
	BuildingLevels *bLevels = saveInfo->GetBuildingLevels();
	buildingHUD->SetBuildingLevel(TownHall, bLevels->GetBuildingLevel(TownHall));
	buildingHUD->SetBuildingLevel(PoliceStation, bLevels->GetBuildingLevel(PoliceStation));
	buildingHUD->SetBuildingLevel(Firehouse, bLevels->GetBuildingLevel(Firehouse));
	buildingHUD->SetBuildingLevel(Lodge, bLevels->GetBuildingLevel(Lodge));
	buildingHUD->SetBuildingLevel(Theatre, bLevels->GetBuildingLevel(Theatre));
	buildingHUD->SetBuildingLevel(Greenhouse, bLevels->GetBuildingLevel(Greenhouse));

	//delete bLevels;
	
	buildingHUD->ResetBuildingDelays();
	
	storyBlocksCleared = saveInfo->GetBlocksCleared();
	storyTotalPlayTime = saveInfo->GetTotalPlayTime();
}

void ArcadeModeView::WriteToSaveInfo(ArcadeModeSaveInfo *saveInfo)
{
	// Detect and store max session moves
	if (m_sessionMoves > maxMovesInSession)
		maxMovesInSession = m_sessionMoves;
	
	if (m_sessionTime > longestSessionTime)
		longestSessionTime = m_sessionTime;
	
	if (m_sessionPowers > maxPowersUsedInSession)
		maxPowersUsedInSession = m_sessionPowers;
	
	//saveInfo->SetLevel(arcadeModeHUD->GetLevel());
	//saveInfo->SetStars(starHUDButton->GetStars());
	//saveInfo->SetCurrentCharacter(characterHUD->GetCharacter());
	saveInfo->SetHighScores(highScores);
	saveInfo->SetHighScoresLevels(highScoresLevels);
	saveInfo->SetLargestChain(largestChain);
	saveInfo->SetLargestMatch(largestMatch);
	saveInfo->SetMaxPointsOnOneMove(maxPointsOnOneMove);
	saveInfo->SetMaxMovesInSession(maxMovesInSession);
	saveInfo->SetMaxPowersUsedInSession(maxPowersUsedInSession);
	saveInfo->SetLongestSessionTime(longestSessionTime);
	saveInfo->SetBlocksCleared(blocksCleared);
	saveInfo->SetTotalPlayTime(totalPlayTime);
}

void ArcadeModeView::LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo)
{
	trophies = saveInfo->GetTrophies();
}

void ArcadeModeView::WriteToTrophySaveInfo(TrophySaveInfo *saveInfo)
{
	saveInfo->SetTrophies(trophies);
}

void ArcadeModeView::LoadFromSettingsSaveInfo(SettingsSaveInfo *saveInfo)
{
	resourcePuzzle->SetHintsEnabled(saveInfo->GetOptionsHintsOn());
}
