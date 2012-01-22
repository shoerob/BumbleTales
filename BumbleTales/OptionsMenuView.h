/*
 *  OptionsMenuView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Input_Engine.h"
#include "Event.h"
#include "Graphics.h"
#include "ConfirmEraseDialog.h"
#include "IView.h"
#include "SettingsSaveInfo.h"
#include "CheckboxControl.h"

class OptionsMenuView : public IView
	{
	public:
		OptionsMenuView(bool allowEraseData);
		~OptionsMenuView();
		
		void Update();
		void Render();
		
		void LoadFromSaveInfo(SettingsSaveInfo *saveInfo);
		void WriteToSaveInfo(SettingsSaveInfo *saveInfo);
		
		Event OnExitClicked;
		Event OnEraseData;
		
		// Delegate Methods
		void OnExitButtonClicked();
		void OnEraseDataButtonClicked();
		
		void OnConfirmEraseYes();
		void OnConfirmEraseNo();
		
	private:
		CheckboxControl *hintsCheckbox;
		CheckboxControl *musicCheckbox;
		CheckboxControl *soundCheckbox;
		
		void OnMusicToggled();
		void OnSoundToggled();
		
		bool eraseDataVisible;
		CR::Graphics::Sprite *menuBackground;
		CR::Graphics::Sprite *headerSprite;
		Input_Button *exitButton;
		Input_Button *eraseDataButton;
		ConfirmEraseDialog *confirmEraseDialog;
		
		//bool m_RequestCloseConfirmEraseDialog;
		bool m_RenderConfirmEraseDialog;
	};