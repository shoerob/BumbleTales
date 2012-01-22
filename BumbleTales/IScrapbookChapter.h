/*
 *  IScrapbookChapter.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/4/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#pragma once
#include "Point.h"
#include "Input_Object.h"

enum ScrapbookChapter { CharactersChapter, RecordsChapter, TrophiesChapter };

class IScrapbookChapter : public Input_Object
{
public:
	virtual ~IScrapbookChapter() {};
	
	virtual void Update() = 0;
	virtual void Render() = 0;
	
	virtual void NextPage() = 0;
	virtual void PrevPage() = 0;
	
	virtual ScrapbookChapter GetChapterType() = 0;
	
	virtual void TouchesBeganImpl(Touch &_touches) {}
	virtual void TouchesMovedImpl(Touch &_touches) {}
	virtual void TouchesEndedImpl(Touch &_touches) {}
	
	// Input_Object
/*	virtual void TouchesBeganImpl(UIView *view, NSSet *touches) {};
	virtual void TouchesMovedImpl(UIView *view, NSSet *touches) {};
	virtual void TouchesEndedImpl(UIView *view, NSSet *touches) {};
	virtual void TouchesCancelledImpl(UIView *view, NSSet *touches) {};*/
	virtual void Reset(){};
	virtual void FreeResources(){};
	
protected:
	IScrapbookChapter() {};
};