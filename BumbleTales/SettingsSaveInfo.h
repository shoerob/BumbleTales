/*
 *  SettingsSaveInfo.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/26/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "SaveInfo.h"
#include <stdio.h>
//#import <UIKit/UIKit.h>

class SettingsSaveInfo : public SaveInfo
{
public:
	SettingsSaveInfo();
	virtual ~SettingsSaveInfo();
	
	bool GetOptionsHintsOn() const { return m_hintsOn; }
	void SetOptionsHintsOn(bool _value) { m_hintsOn = _value; }
	
	bool GetOptionsMusicOn() const { return m_musicOn; }
	void SetOptionsMusicOn(bool _value) { m_musicOn = _value; }
	
	bool GetOptionsSoundOn() const { return m_soundOn; }
	void SetOptionsSoundOn(bool _value) { m_soundOn = _value; }
	
	virtual void Save();
	virtual void Load();
	virtual void Reset();
protected:

private:
	FILE *m_file;

	bool m_hintsOn;
	bool m_musicOn;
	bool m_soundOn;
	//NSString* GetDefaultsFilePath();
	//NSString* GetSaveFilePath();
};