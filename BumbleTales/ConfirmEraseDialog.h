/*
 *  ConfirmEraseDialog.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/22/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "IRenderable.h"
#include "Input_Engine.h"
#include "Graphics.h"

class ConfirmEraseDialog : public Input_Controller, public IRenderable
{
public:
	ConfirmEraseDialog();
	virtual ~ConfirmEraseDialog();
	
	//IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	//Events
	Event OnYes;
	Event OnNo;
	//Event OnCloseDialog;
	
	//Delegates
	void OnYesClicked();
	void OnNoClicked();
	virtual void InputChanged() {}
	
private:
	CR::Graphics::Sprite *confirmEraseSprite;
	Input_Button *yesButton;
	Input_Button *noButton;
};