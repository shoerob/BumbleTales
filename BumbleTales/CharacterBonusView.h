/*
 *  CharacterBonusView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IView.h"
#include "Input_Engine.h"
#include "StoryModeSaveInfo.h"
#include "RadioButtonControl.h"
#include "CharacterHUD.h"

class CharacterBonusView : public IView
{
public:
	CharacterBonusView();
	virtual ~CharacterBonusView();
	
	// IView
	virtual void Update();
	virtual void Render();
	
	void LoadFromSaveInfo(StoryModeSaveInfo *saveInfo);
	void WriteToSaveInfo(StoryModeSaveInfo *saveInfo);
	
	void OnRadioButtonSelected(int _value);
	
	void OnCloseButtonPressed();
	Event OnClose;
	Event OnChangeCharacter;
	
	CharacterName GetCurrentCharacter() const { return currCharacter; }
	int GetCurrentCharacterLevel();
	
private:
	CR::Graphics::Sprite *baseSprite;
	Input_Button *closeButton;
	RadioButtonControl *m_radioButtons[12];
	CharacterName currCharacter;
	CharacterLevels *cLevels;
};