/*
 *  CharacterBonusView.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/30/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "CharacterBonusView.h"
#include "AssetList.h"
#include "StoryModeSaveInfo.h"

extern CR::Graphics::GraphicsEngine *graphics_engine;

CharacterBonusView::CharacterBonusView()
{
	baseSprite = graphics_engine->CreateSprite1(false,500);
	baseSprite->SetImage(CR::AssetList::Char_Bonus_Base);
	baseSprite->SetPositionAbsolute(160, 240);
	
	closeButton = new Input_Button();
	closeButton->SetSpriteAndBounds(110, 420, CR::AssetList::Char_Bonus_Close_Button, 400);
	closeButton->OnClicked += Delegate(this, &CharacterBonusView::OnCloseButtonPressed);
	closeButton->SetSound(CR::AssetList::sounds::shopopen::ID);
	input_objects.push_back(closeButton);
	
	//for (int i = 0; i < 12; i++)
	int i = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_radioButtons[i] = new RadioButtonControl(CR::AssetList::Char_Bonus_Character_Active, CR::AssetList::Char_Dim);
			m_radioButtons[i]->SetPositionAndBounds(37 + x * 89, 75 + y * 84, 68, 68);
			m_radioButtons[i]->OnRadioButtonSelected += Delegate1<CharacterBonusView, int>(this, &CharacterBonusView::OnRadioButtonSelected);
			input_objects.push_back(m_radioButtons[i]);
			i++;
		}
	}
	
	// Set radio button values
	m_radioButtons[Mayor]->SetValue((int)Mayor);
	m_radioButtons[Elder]->SetValue((int)Elder);
	m_radioButtons[Fireman]->SetValue((int)Fireman);
	m_radioButtons[Dog]->SetValue((int)Dog);
	m_radioButtons[Baker]->SetValue((int)Baker);
	m_radioButtons[Teacher]->SetValue((int)Teacher);
	m_radioButtons[Librarian]->SetValue((int)Librarian);
	m_radioButtons[Romeo]->SetValue((int)Romeo);
	m_radioButtons[Felicia]->SetValue((int)Felicia);
	m_radioButtons[Bruiser]->SetValue((int)Bruiser);
	m_radioButtons[Marla]->SetValue((int)Marla);
	m_radioButtons[ChopChop]->SetValue((int)ChopChop);
	
	currCharacter = NoCharacter;
	cLevels = NULL;
}

CharacterBonusView::~CharacterBonusView()
{
	baseSprite->Release();
	delete closeButton;
	
	for (int i = 0; i < 12; i++)
		delete m_radioButtons[i];
	
	//cLevels.Save();
	//if (cLevels != NULL)
	//	delete cLevels;
}

void CharacterBonusView::Update()
{
}

void CharacterBonusView::Render()
{
	baseSprite->Render();
	closeButton->Render();
	
	for (int i = 0; i < 12; i++)
		m_radioButtons[i]->Render();
}

void CharacterBonusView::LoadFromSaveInfo(StoryModeSaveInfo *saveInfo)
{
	cLevels = saveInfo->GetCharacterLevels();
	m_radioButtons[Mayor]->Disabled(cLevels->GetCharacterLevel(Mayor) <= 0);
	m_radioButtons[Elder]->Disabled(cLevels->GetCharacterLevel(Elder) <= 0);
	m_radioButtons[Fireman]->Disabled(cLevels->GetCharacterLevel(Fireman) <= 0);
	m_radioButtons[Dog]->Disabled(cLevels->GetCharacterLevel(Dog) <= 0);
	m_radioButtons[Baker]->Disabled(cLevels->GetCharacterLevel(Baker) <= 0);
	m_radioButtons[Teacher]->Disabled(cLevels->GetCharacterLevel(Teacher) <= 0);
	m_radioButtons[Librarian]->Disabled(cLevels->GetCharacterLevel(Librarian) <= 0);
	m_radioButtons[Romeo]->Disabled(cLevels->GetCharacterLevel(Romeo) <= 0);
	m_radioButtons[Felicia]->Disabled(cLevels->GetCharacterLevel(Felicia) <= 0);
	m_radioButtons[Bruiser]->Disabled(cLevels->GetCharacterLevel(Bruiser) <= 0);
	m_radioButtons[Marla]->Disabled(cLevels->GetCharacterLevel(Marla) <= 0);
	m_radioButtons[ChopChop]->Disabled(cLevels->GetCharacterLevel(ChopChop) <= 0);
	currCharacter = saveInfo->GetCurrentCharacter();
	
	if (currCharacter != NoCharacter)
		m_radioButtons[currCharacter]->Select();
}

int CharacterBonusView::GetCurrentCharacterLevel()
{
	if (currCharacter != NoCharacter)
		return cLevels->GetCharacterLevel(currCharacter);
	else
		return 0;
}

void CharacterBonusView::WriteToSaveInfo(StoryModeSaveInfo *saveInfo)
{
	saveInfo->SetCurrentCharacter(currCharacter);
}

void CharacterBonusView::OnRadioButtonSelected(int _value)
{
	// deselect all other radio buttons
	for (int i = 0; i < 12; i++)
	{
		if (m_radioButtons[i]->GetValue() != _value)
			m_radioButtons[i]->Deselect();
	}
	
	currCharacter = (CharacterName) _value;
	OnChangeCharacter();
}

void CharacterBonusView::OnCloseButtonPressed()
{
	OnClose();
}