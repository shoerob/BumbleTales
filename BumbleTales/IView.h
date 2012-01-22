/*
 *  IView.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/25/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Input_Engine.h"

class IView : public Input_Controller
{
public:
	virtual ~IView() {};
	
	virtual void Update() {};
	virtual void Render() {};
	virtual void PauseAnimation(bool pause) {};
	virtual bool IsPaused() const { return false; };
	virtual void InputChanged() {};
	//virtual void SaveOnTerminate() {}
	
protected:
	IView() {};
	
};