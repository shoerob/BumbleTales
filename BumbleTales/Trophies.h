/*
 *  Trophies.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/9/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
//#import <UIKit/UIKit.h>

enum TrophyName 
{
	CityMasterTrophy,
	WellRoundedTrophy,
	IHeartBumblesTrophy,
	MasterStoryTellerTrophy,
	BrickBreakerTrophy,
	WoodChipperTrophy,
	LeafRakerTrophy,
	GoldMinerTrophy,
	CrystalClearerTrophy,
	GemCollectorTrophy,
	MasterPieceTrophy,
	ResourcefulTrophy,
	OnTheLevelTrophy,
	CenturionTrophy,
	MedalManiacTrophy,
	HeavyMedalTrophy,
	PowerHungryTrophy,
	SimpleChainTrophy,
	ChainReactionTrophy,
	MonsterChainTrophy,
	HighFiveTrophy,
	MegaMatchTrophy,
	TheWildBunchTrophy,
	TimeOnYourHandsTrophy,
	ArcadeNewbieTrophy,
	ArcadeProTrophy,
	ArcadeMasterTrophy,
	TheArtOfScoreTrophy,
	MasterStrategistTrophy,
	GreatStreakTrophy,
	WickedStreakTrophy,
	InsaneStreakTrophy,
	EnergizedTrophy,
	OutOfTheGatesTrophy,
	DareDevilTrophy,
	OldFashionedTrophy,
	NumTrophies
};
/*static const NSString *TrophyNameStrings[] = 
{
	@"CityMaster",
	@"WellRounded",
	@"IHeartBumbles",
	@"MasterStoryTeller",
	@"BrickBreaker",
	@"WoodChipper",
	@"LeafRaker",
	@"GoldMiner",
	@"CrystalClearer",
	@"GemCollector",
	@"MasterPiece",
	@"Resourceful",
	@"OnTheLevel",
	@"Centurion",
	@"MedalManiac",
	@"HeavyMedal",
	@"PowerHungry",
	@"SimpleChain",
	@"ChainReaction",
	@"MonsterChain",
	@"HighFive",
	@"MegaMatch",
	@"TheWildBunch",
	@"TimeOnYourHands",
	@"ArcadeNewbie",
	@"ArcadePro",
	@"ArcadeMaster",
	@"TheArtOfScore",
	@"MasterStrategist",
	@"GreatStreak",
	@"WickedStreak",
	@"InsaneStreak",
	@"Energized",
	@"OutOfTheGates",
	@"DareDevil",
	@"OldFashioned"
};*/

class Trophies
{
public:
	Trophies(/*NSMutableDictionary *trophies*/);
	virtual ~Trophies();
	
	bool GetTrophy(TrophyName trophyName) const;
	void SetTrophy(TrophyName trophyName, bool _value);
			
	//NSMutableDictionary *GetDictionary();
	
	void Save();
	void Load();
	void Reset();

private:
	bool m_trophies[NumTrophies];

	//NSMutableDictionary *m_trophies;
	
	//bool GetBoolForKey(NSString *key) const;
	//void SetBoolForKey(bool _value, NSString *key);
};