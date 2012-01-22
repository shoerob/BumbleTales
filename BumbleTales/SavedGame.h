/*
 *  SavedGame.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
//#import <UIKit/UIKit.h>
#include <string>
#include "Event.h"
#include "StoryModeScoreInfo.h"

//#define kSaveFileName @"btales.plist"

class SavedGame
{
public:
	SavedGame();
	~SavedGame();
	
	//NSString* GetDefaultsFilePath();
	//NSString* GetSaveFilePath();
	
	void Save();
	void Load();
	void Reset();
	
	void SaveOnTerminate();
	Event OnSaveOnTerminate;
	
	int GetLevel() const;
	void SetLevel(int _value);
	
	int GetStars() const;
	void SetStars(int _value);
	
	bool GetOptionsHintsOn() const;
	void SetOptionsHintsOn(bool _value);
	
	bool GetOptionsMusicOn() const;
	void SetOptionsMusicOn(bool _value);
	
	bool GetOptionsSoundOn() const;
	void SetOptionsSoundOn(bool _value);
	
	//NSMutableDictionary* GetStoryModeScoreInfo();
	//void SetStoryModeScoreInfo(NSMutableDictionary *storyModeScoreInfo);
	
private:
	/*NSMutableDictionary *saveData;

	int GetIntForKey(NSString *key) const;
	void SetIntForKey(int _value, NSString *key);
	
	bool GetBoolForKey(NSString *key) const;
	void SetBoolForKey(bool _value, NSString *key);*/
	
};