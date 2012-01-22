/*
 *  CounterFont.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 6/18/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "IRenderable.h"
#include "Point.h"

class CounterFont : public IRenderable
	{
	public:
		CounterFont(int fontAsset, int xLoc, int yLoc);
		virtual ~CounterFont();
		
		void Update();
		void Render();
		void SetPosition(float xLoc, float yLoc);
		void PauseAnimation(bool pause) {};
		
		void SetCount(int cnt);
		int GetCount() { return m_count; }
		void Increment() { m_count++; UpdateDigits();}
		
		//void operator++();
		void SetMaxDigits(int _value);
		
	private:
		CR::Math::PointF offset;
		int m_count;
		CR::Graphics::Sprite *numberFont;
		
		int digits[3];
		
		void UpdateDigits();
		int m_maxDigits;
	};