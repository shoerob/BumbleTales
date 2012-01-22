/*
 *  CharacterLevels.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
//#import <UIKit/UIKit.h>
#include <stdio.h>
#include <assert.h>

enum CharacterName { Mayor = 0, Elder = 1, Fireman = 2, Dog = 3, Baker = 4, Teacher = 5, Librarian = 6, Romeo = 7, Felicia = 8, Bruiser = 9, Marla = 10, ChopChop = 11, NoCharacter = 12, WonGameChapter = 13, NumCharacterLevels = 14 };
//static const NSString *CharacterNameStrings[] = {@"Mayor", @"Elder", @"Fireman", @"Dog", @"Baker", @"Teacher", @"Librarian", @"Romeo", @"Felicia", @"Bruiser", @"Marla", @"ChopChop", @"NoCharacter", @"WonGameChapter" };

class CharacterLevels
{
public:
	CharacterLevels(/*NSMutableDictionary *characterLevels*/);
	virtual ~CharacterLevels();
	
	int GetCharacterLevel(CharacterName charName) const { assert(charName < NumCharacterLevels); return m_levels[charName]; }
	void SetCharacterLevel(CharacterName charName, int _value) { assert(charName < NumCharacterLevels); m_levels[charName] = _value; }
		
	//NSMutableDictionary *GetDictionary();
	
	void Save(FILE *_file);
	void Load(FILE *_file);
	void Reset();
private:
	int m_levels[NumCharacterLevels];

	//NSMutableDictionary *m_characterLevels;
	
	//int GetIntForKey(NSString *key) const;
	//void SetIntForKey(int _value, NSString *key);
};