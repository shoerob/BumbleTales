/*
 *  StoryModeView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/24/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "StoryModeView.h"
#include "ResourceTile.h"
#include "Sound.h"
#include "NewAssetList.h"
#include "AssetList.h"

using namespace CR::Sound;

extern CR::Graphics::GraphicsEngine *graphics_engine;
extern Input_Engine *input_engine;

StoryModeView::StoryModeView()
{
	backgroundSprite = graphics_engine->CreateSprite1(false,1000);
	backgroundSprite->SetImage(CR::AssetList::Story_Mode_Background);
	backgroundSprite->SetDesignSize(320, 480);
	backgroundSprite->SetPositionAbsolute(160, 240);
	
	touchToEnterShop = new SplashScreen(CR::AssetList::Touch_to_Enter, 3, 775);
	touchToEnterShop->DesignSize(117, 83);
	touchToEnterShop->SetPosition(233, 105);
	touchToEnterShop->SetFadeEffect(true);
	
	resourcePuzzle = new ResourcePuzzle(3, 70, 1);
	input_objects.push_back(resourcePuzzle);
	resourcePuzzle->OnIncrementChain += Delegate(this, &StoryModeView::OnIncrementChain);
	resourcePuzzle->ResourcesRetrieved += Delegate2<StoryModeView, ResourceType, int>(this,&StoryModeView::OnResourcesRetrieved);
	
	pauseButton = new Input_Button();
	pauseButton->SetSpriteAndBounds(260, 10, CR::AssetList::Pause_Button, 800);
	pauseButton->DesignSize(53, 51);
	pauseButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(pauseButton);
	pauseButton->OnClicked += Delegate(this, &StoryModeView::OnPauseButtonPressed);
	
	starHUDButton = new StarHUD();
	starHUDButton->SetPosition(210, 4);
	input_objects.push_back(starHUDButton);
	starHUDButton->OnClicked += Delegate(this, &StoryModeView::OnStarHUDButtonPressed);
	
	storyModeHUD = new StoryModeHUD(106, 32);
	
	characterHUD = new CharacterHUD();
	characterHUD->SetPosition(245, 397);
	//characterHUD->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(characterHUD);
	characterHUD->OnClicked += Delegate(this, &StoryModeView::OnCharacterHUDButtonPressed);
	
	buildingHUD = new BuildingHUD(resourcePuzzle);
	buildingHUD->SetPosition(4, 395);
	input_objects.push_back(buildingHUD);
	buildingHUD->OnPowerUsed += Delegate(this, &StoryModeView::OnPowerUsed);

	m_isPaused = false;
	m_performLevelUp = false;
	//m_isChaining = false;
	
	m_chainCount = 0;
	m_scoreData = new StoryModeScoreData();
	
	m_levelTime = 0;
	largestMatch = 0;
	//gotMegaMatchTrophy = false;
	qTilesCleared = 0;
	bronzeMedals = 0;
	silverMedals = 0;
	goldMedals = 0;
	receivedStars = 0;
	gotWellRounded = false;
	gotMasterStoryTeller = false;
	megaBlocksCleared = 0;
	hudClipSprite = graphics_engine->CreateSprite1(false, 925);
	hudClipSprite->SetImage(CR::AssetList::Story_Mode_HUD_Top);
	hudClipSprite->SetDesignSize(320, 70);
	hudClipSprite->SetPositionAbsolute(160, 35);

}

StoryModeView::~StoryModeView()
{
	backgroundSprite->Release();
	hudClipSprite->Release();
	delete resourcePuzzle;
	delete storyModeHUD;
	delete pauseButton;
	delete starHUDButton;
	delete m_scoreData;
	delete characterHUD;
	delete buildingHUD;
	delete touchToEnterShop;
}

void StoryModeView::Update()
{	
	//touchToEnterShop->StartSplash();
	
	if (!resourcePuzzle->IsPuzzleAnimating())
	{
		if (m_isChaining) // the chain ended since the puzzle finished animating
		{
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
	}
	
	if (m_performLevelUp)
	{
		// wait for the puzzle to finish chaining/animating to show the level up screen
		if (!resourcePuzzle->IsPuzzleAnimating())
		{
			m_performLevelUp = false;
			PerformLevelUp();
			OnTriggerScoreScreen();
		}
	}
	
	if (!m_isPaused)
	{
		m_levelTime += Globals::Instance().GetTimer()->GetTimePassed();
	}
	
	resourcePuzzle->Update();
	storyModeHUD->Update();
	starHUDButton->Update();
	characterHUD->Update();
	buildingHUD->Update();
	touchToEnterShop->Update();
}

void StoryModeView::Render()
{
	backgroundSprite->Render();
	resourcePuzzle->Render();
	pauseButton->Render();
	storyModeHUD->Render();
	starHUDButton->Render();
	characterHUD->Render();
	buildingHUD->Render();
	hudClipSprite->Render();
	touchToEnterShop->Render();
}

void StoryModeView::OnIncrementChain()
{
	m_isChaining = true;
	m_chainCount++;
}

void StoryModeView::OnResourcesRetrieved(ResourceType rType, int cnt)
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
		storyModeHUD->AddResources(rType, cnt);
		blocksCleared[(int)rType] += cnt;
	}
	
	m_scoreData->SetResourceCount(rType, m_scoreData->GetResourceCount(rType) + cnt);
	
	// A multi-tile was retrieved, player gets 3 of every basic resource
	if (rType == MTile)
	{
		blocksCleared[(int)rType] += cnt;
		//if (cnt >=5)
		//	gotMegaMatchTrophy = true;
		megaBlocksCleared += cnt;
		
		for (int i = 0; i < 6; i++)
		{
			int rBonus = characterHUD->GetCharacterBonus().GetResourceBonus((ResourceType)i);
			storyModeHUD->AddResources((ResourceType)i, 3 * cnt + rBonus);
			m_scoreData->SetResourceCount((ResourceType)i, m_scoreData->GetResourceCount((ResourceType)i) + 3 * cnt + rBonus);
			blocksCleared[i] += (3 * cnt) + rBonus;
		}
	}
	
	//DEBUG: Level up (needs to play level up animation first)
	if (storyModeHUD->ResourcesGathered())
	{
		m_performLevelUp = true;
	}
}

void StoryModeView::OnPauseButtonPressed()
{
	OnShowPauseMenu();
}

void StoryModeView::OnTriggerScoreScreen()
{	
	OnShowScoreScreen(m_scoreData);
}

void StoryModeView::PauseAnimation(bool pause)
{
	m_isPaused = pause;
	resourcePuzzle->PauseAnimation(pause);
	storyModeHUD->PauseAnimation(pause);
	starHUDButton->PauseAnimation(pause);
	buildingHUD->PauseAnimation(pause);
}

void StoryModeView::OnStarHUDButtonPressed()
{
	hasOpenedStore = true;
	OnShowStore();
}

void StoryModeView::OnCharacterHUDButtonPressed()
{
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::shopopen::ID);
	sound->Play();
	
	OnShowCharacterBonusMenu();
}

void StoryModeView::OnPowerUsed()
{
	m_scoreData->powersUsed++;
}

void StoryModeView::PerformLevelUp()
{
	std::tr1::shared_ptr<CR::Sound::ISoundFX> sound;
	sound = ISound::Instance().CreateSoundFX(CR::AssetList::sounds::levelupfanfare::ID);
	sound->Play();
	
	storyModeHUD->PerformLevelUp();
	
	// 90 stars are possible in the game
	if (receivedStars < 90)
	{
		starHUDButton->AddStar();
		receivedStars++;
		m_scoreData->gotStar = true;
	}
	else
	{
		m_scoreData->gotStar = false;
	}
	
	totalPlayTime += m_levelTime;
	
	m_scoreData->levelTime = m_levelTime;
	m_levelTime = 0;
	
	DetectAndUpdateMedals();
	DetectAndUpdateTrophies();
	
	//largestMatch = 0;
	//gotMegaMatchTrophy = false;
	qTilesCleared = 0;
	megaBlocksCleared = 0;
	/*int modLevel = (storyModeHUD->GetLevel()-1) % 10;
	if (modLevel < 5)
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory1::ID);
	else
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory2::ID);*/
}

void StoryModeView::SetCharacterBonus(CharacterName charName, int level)
{
	characterHUD->SetCharacter(charName, level);
	resourcePuzzle->SetDropRateBonusType(characterHUD->GetCharacterBonus().dropRateBonusType);
}

void StoryModeView::TriggerTouchToEnterStore()
{
	if (!hasOpenedStore)
		touchToEnterShop->StartSplash();
}

void StoryModeView::DetectAndUpdateMedals()
{
	int eGold = 0;
	int eSilver = 0;
	int eBronze = 0;
	int eNone = 0;
	
	m_scoreData->tileMedals[Brick] = GetMedalForTile(Brick);
	m_scoreData->tileMedals[Gold] = GetMedalForTile(Gold);
	m_scoreData->tileMedals[Wood] = GetMedalForTile(Wood);
	m_scoreData->tileMedals[Crystal] = GetMedalForTile(Crystal);
	m_scoreData->tileMedals[Leaf] = GetMedalForTile(Leaf);
	m_scoreData->tileMedals[Diamond] = GetMedalForTile(Diamond);
	m_scoreData->tileMedals[QTile] = GetMedalForTile(QTile);
	m_scoreData->tileMedals[MTile] = GetMedalForTile(MTile);
	
	for (int i = 0; i < 7; i++)
	{
		if (m_scoreData->tileMedals[i] == GoldMedal)
			eGold++;
		else if (m_scoreData->tileMedals[i] == SilverMedal)
			eSilver++;
		else if (m_scoreData->tileMedals[i] == BronzeMedal)
			eBronze++;
		else
			eNone++;
	}
	
	
	// Chain Medal
	if (m_scoreData->largestChain >= 5)
	{
		m_scoreData->chainMedal = GoldMedal;
		eGold++;
	}
	else if (m_scoreData->largestChain >= 4)
	{
		m_scoreData->chainMedal = SilverMedal;
		eSilver++;
	}
	else if (m_scoreData->largestChain >= 3)
	{
		m_scoreData->chainMedal = BronzeMedal;
		eBronze++;
	}
	else
	{
		m_scoreData->chainMedal = NoMedal;
		eNone++;
	}
	
	// Powers Used Medal
	if (m_scoreData->powersUsed >= 10)
	{
		m_scoreData->powersUsedMedal = GoldMedal;
		eGold++;
	}
	else if (m_scoreData->powersUsed >= 7)
	{
		m_scoreData->powersUsedMedal = SilverMedal;
		eSilver++;
	}
	else if (m_scoreData->powersUsed >= 4)
	{
		m_scoreData->powersUsedMedal = BronzeMedal;
		eBronze++;
	}
	else
	{
		m_scoreData->powersUsedMedal = NoMedal;
		eNone++;
	}
	
	// Level Time Medal
	m_scoreData->levelTimeMedal = NoMedal;
	
	// Add medals to saved tally
	goldMedals += eGold;
	silverMedals += eSilver;
	bronzeMedals += eBronze;
}

MedalType StoryModeView::GetMedalForTile(ResourceType rType)
{
	int rRequired = storyModeHUD->GetResourceRequirement();
	int bBonus = rRequired * 1.5;
	int sBonus = rRequired * 2.0;
	int gBonus = rRequired * 2.5;
	
	if (m_scoreData->resourceCount[rType] >= gBonus)
		return GoldMedal;
	else if (m_scoreData->resourceCount[rType] >= sBonus)
		return SilverMedal;
	else if (m_scoreData->resourceCount[rType] >= bBonus)
		return BronzeMedal;
	else
		return NoMedal;
}

void StoryModeView::DetectAndUpdateTrophies()
{
	vector<TrophyName> gotTrophies;
	
	// CityMaster
	if (buildingHUD->GetCityMasterTrophy())
		gotTrophies.push_back(CityMasterTrophy);
	
	// WellRounded
	if (gotWellRounded)
		gotTrophies.push_back(WellRoundedTrophy);
	
	// IHeartBumbles
	if (buildingHUD->GetIHeartBumblesTrophy())
		gotTrophies.push_back(IHeartBumblesTrophy);
	
	// Master Story Teller
	if (gotMasterStoryTeller)
		gotTrophies.push_back(MasterStoryTellerTrophy);
	
	// BrickBreaker
	if (blocksCleared[Brick] + arcadeBlocksCleared[Brick] >= 5000)
		gotTrophies.push_back(BrickBreakerTrophy);
	
	// WoodChipper
	if (blocksCleared[Wood] + arcadeBlocksCleared[Wood] >= 6000)
		gotTrophies.push_back(WoodChipperTrophy);
	
	// LeafRaker
	if (blocksCleared[Leaf] + arcadeBlocksCleared[Leaf] >= 7000)
		gotTrophies.push_back(LeafRakerTrophy);
	
	// GoldMiner
	if (blocksCleared[Gold] + arcadeBlocksCleared[Gold] >= 8000)
		gotTrophies.push_back(GoldMinerTrophy);
	
	// CrystalClearer
	if (blocksCleared[Crystal] + arcadeBlocksCleared[Crystal] >= 9000)
		gotTrophies.push_back(CrystalClearerTrophy);
	
	// GemCollector
	if (blocksCleared[Diamond] + arcadeBlocksCleared[Diamond] >= 10000)
		gotTrophies.push_back(GemCollectorTrophy);
	
	// MasterPiece
	if (blocksCleared[MTile] + arcadeBlocksCleared[MTile] >= 500)
		gotTrophies.push_back(MasterPieceTrophy);
	
	// Resourceful
	if (blocksCleared[Brick] + blocksCleared[Wood] + blocksCleared[Leaf] + blocksCleared[Gold] + blocksCleared[Crystal] + blocksCleared[Diamond] + blocksCleared[MTile] + blocksCleared[QTile] +
		arcadeBlocksCleared[Brick] + arcadeBlocksCleared[Wood] + arcadeBlocksCleared[Leaf] + arcadeBlocksCleared[Gold] + arcadeBlocksCleared[Crystal] + arcadeBlocksCleared[Diamond] +
		arcadeBlocksCleared[MTile] + arcadeBlocksCleared[QTile] >= 100000)
	{
		gotTrophies.push_back(ResourcefulTrophy);
	}
	
	// OnTheLevel
	if (storyModeHUD->GetLevel() >= 50)
		gotTrophies.push_back(OnTheLevelTrophy);
	
	// Centurion
	if (storyModeHUD->GetLevel() >= 100)
		gotTrophies.push_back(CenturionTrophy);
	
	// MedalManiac
	if ((bronzeMedals + silverMedals + goldMedals) >= 500)
	{
		gotTrophies.push_back(MedalManiacTrophy);
	}
	
	// HeavyMedal
	if (goldMedals >= 200)
	{
		gotTrophies.push_back(HeavyMedalTrophy);
	}
	
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
	if (totalPlayTime + arcadeTotalPlayTime >= 7200)
		gotTrophies.push_back(TimeOnYourHandsTrophy);
	
	// Arcade Newbie
	//if (m_scoreData->score >= 10000)
	//	gotTrophies.push_back(ArcadeNewbieTrophy);
	
	// Arcade Pro
	//if (m_scoreData->score >= 100000)
	//	gotTrophies.push_back(ArcadeProTrophy);
	
	// Arcade Master
	//if (m_scoreData->score >= 500000)
	//	gotTrophies.push_back(ArcadeMasterTrophy);
	
	// The Art of Score
	//if (gotArtOfScoreTrophy)
	//	gotTrophies.push_back(TheArtOfScoreTrophy);
	
	// Master Strategist
	//if (gotMasterStrategistTrophy)
	//	gotTrophies.push_back(MasterStrategistTrophy);
	
	// Great Streak
	//if (m_scoreData->levelTime >= 180)
	//	gotTrophies.push_back(GreatStreakTrophy);
	
	// Wicked Streak
	//if (m_scoreData->levelTime >= 300)
	//	gotTrophies.push_back(WickedStreakTrophy);
	
	// Insane Streak
	//if (m_scoreData->levelTime >= 600)
	//	gotTrophies.push_back(InsaneStreakTrophy);
	
	// Energized
	//if (m_scoreData->level >= 25)
	//	gotTrophies.push_back(EnergizedTrophy);
	
	// Out of the Gates
	//if (gotOutOfTheGatesTrophy)
	//	gotTrophies.push_back(OutOfTheGatesTrophy);
	
	// Dare Devil - ARCADE MODE ONLY
	// Old Fashioned - ARCADE MODE ONLY
	
	
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

void StoryModeView::LoadFromSaveInfo(StoryModeSaveInfo *saveInfo)
{	
	storyModeHUD->SetLevel(saveInfo->GetLevel());
	
	LoadStarBonusSaveInfo(saveInfo);
	buildingHUD->ResetBuildingDelays();
	blocksCleared = saveInfo->GetBlocksCleared();
	bronzeMedals = saveInfo->GetBronzeMedals();
	silverMedals = saveInfo->GetSilverMedals();
	goldMedals = saveInfo->GetGoldMedals();
	totalPlayTime = saveInfo->GetTotalPlayTime();
	largestMatch = saveInfo->GetLargestMatch();
	largestChain = saveInfo->GetLargestChain();
	hasOpenedStore = saveInfo->GetHasOpenedStore();
	
	int modLevel = (storyModeHUD->GetLevel()-1) % 10;
	if (modLevel < 5)
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory1::ID);
	else
		ISound::Instance().PlaySong(CR::AssetList::music::BGMStory2::ID);
}

void StoryModeView::LoadStarBonusSaveInfo(StoryModeSaveInfo *saveInfo)
{
	starHUDButton->SetStars(saveInfo->GetStars());
	starHUDButton->SetMaxedOut(saveInfo->GetHasWonGame());
	receivedStars = saveInfo->GetStarsReceived();
	
	CharacterLevels *cLevels = saveInfo->GetCharacterLevels();
	CharacterName cChar = saveInfo->GetCurrentCharacter();
	characterHUD->SetCharacter(cChar, cLevels->GetCharacterLevel(cChar));
	
	// Check for well rounded trophy
	if(cLevels->GetCharacterLevel(Mayor) >= 5 || cLevels->GetCharacterLevel(Elder) >= 5 || cLevels->GetCharacterLevel(Fireman) >= 5 ||
		cLevels->GetCharacterLevel(Dog) >= 5 || cLevels->GetCharacterLevel(Baker) >= 5 || cLevels->GetCharacterLevel(Teacher) >= 5 ||
		cLevels->GetCharacterLevel(Librarian) >= 5 || cLevels->GetCharacterLevel(Romeo) >= 5 || cLevels->GetCharacterLevel(Felicia) >= 5 ||
		cLevels->GetCharacterLevel(Bruiser) >= 5 || cLevels->GetCharacterLevel(Marla) >= 5 || cLevels->GetCharacterLevel(ChopChop) >= 5)
	{
		gotWellRounded = true;
	}
	
	// Check for master story teller trophy
	if(cLevels->GetCharacterLevel(Mayor) >= 5 && cLevels->GetCharacterLevel(Elder) >= 5 && cLevels->GetCharacterLevel(Fireman) >= 5 &&
	   cLevels->GetCharacterLevel(Dog) >= 5 && cLevels->GetCharacterLevel(Baker) >= 5 && cLevels->GetCharacterLevel(Teacher) >= 5 &&
	   cLevels->GetCharacterLevel(Librarian) >= 5 && cLevels->GetCharacterLevel(Romeo) >= 5 && cLevels->GetCharacterLevel(Felicia) >= 5 &&
	   cLevels->GetCharacterLevel(Bruiser) >= 5 && cLevels->GetCharacterLevel(Marla) >= 5 && cLevels->GetCharacterLevel(ChopChop) >= 5)
	{
		gotMasterStoryTeller = true;
	}
	
	//delete cLevels;
	
	BuildingLevels *bLevels = saveInfo->GetBuildingLevels();
	buildingHUD->SetBuildingLevel(TownHall, bLevels->GetBuildingLevel(TownHall));
	buildingHUD->SetBuildingLevel(PoliceStation, bLevels->GetBuildingLevel(PoliceStation));
	buildingHUD->SetBuildingLevel(Firehouse, bLevels->GetBuildingLevel(Firehouse));
	buildingHUD->SetBuildingLevel(Lodge, bLevels->GetBuildingLevel(Lodge));
	buildingHUD->SetBuildingLevel(Theatre, bLevels->GetBuildingLevel(Theatre));
	buildingHUD->SetBuildingLevel(Greenhouse, bLevels->GetBuildingLevel(Greenhouse));
	//buildingHUD->ResetBuildingDelays();
	
	//delete bLevels;
}

void StoryModeView::WriteToSaveInfo(StoryModeSaveInfo *saveInfo)
{
	saveInfo->SetLevel(storyModeHUD->GetLevel());
	saveInfo->SetStars(starHUDButton->GetStars());
	saveInfo->SetCurrentCharacter(characterHUD->GetCharacter());
	saveInfo->SetBlocksCleared(blocksCleared);
	saveInfo->SetBronzeMedals(bronzeMedals);
	saveInfo->SetSilverMedals(silverMedals);
	saveInfo->SetGoldMedals(goldMedals);
	saveInfo->SetTotalPlayTime(totalPlayTime);
	saveInfo->SetStarsReceived(receivedStars);
	saveInfo->SetLargestMatch(largestMatch);
	saveInfo->SetLargestChain(largestChain);
	saveInfo->SetHasOpenedStore(hasOpenedStore);
}

void StoryModeView::LoadFromTrophySaveInfo(TrophySaveInfo *saveInfo)
{
	trophies = saveInfo->GetTrophies();
}

void StoryModeView::WriteToTrophySaveInfo(TrophySaveInfo *saveInfo)
{
	saveInfo->SetTrophies(trophies);
}

void StoryModeView::LoadArcadeBlocksCleared(ArcadeModeSaveInfo *saveInfo)
{
	arcadeBlocksCleared = saveInfo->GetBlocksCleared();
	arcadeTotalPlayTime = saveInfo->GetTotalPlayTime();
}

void StoryModeView::LoadFromSettingsSaveInfo(SettingsSaveInfo *saveInfo)
{
	resourcePuzzle->SetHintsEnabled(saveInfo->GetOptionsHintsOn());
}