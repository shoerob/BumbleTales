/*
 *  StoryModeScore.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/19/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#include "Graphics.h"
#include "IRenderable.h"
#include "Input_Engine.h"
#include "Event.h"
#include "CounterFont.h"

class StoryModeScore : public Input_Controller, public IRenderable
{
public:
	StoryModeScore();
	virtual ~StoryModeScore();
	
	// IRenderable
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc);
	void PauseAnimation(bool pause);
	
	void OnOkButtonPressed();
	
	Event OnResumeGame;
private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *scoreBaseSprite;
	Input_Button *okButton;
	CounterFont *counterFont;
};