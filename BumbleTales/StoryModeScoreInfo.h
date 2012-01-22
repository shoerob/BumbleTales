/*
 *  StoryModeScoreInfo.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
//#import <UIKit/UIKit.h>
#include "ResourceTile.h"

class StoryModeScoreInfo
{
public:
	StoryModeScoreInfo();
	virtual ~StoryModeScoreInfo();
	
	void SetResourceCount(ResourceType resourceType, int _value);
	int GetResourceCount(ResourceType resourceType);
	
	void SetLargestChain(int _value);
	int GetLargestChain() const;
	
	void SetLevelTime(float _value);
	float GetLevelTime() const;
	
	void ResetScore();
	
private:
/*	NSMutableDictionary *scoreInfo;
	
	int GetIntForKey(NSString *key) const;
	void SetIntForKey(int _value, NSString *key);
	
	float GetFloatForKey(NSString *key) const;
	void SetFloatForKey(float _value, NSString *key);
	
	bool GetBoolForKey(NSString *key) const;
	void SetBoolForKey(bool _value, NSString *key);*/
};