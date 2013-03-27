/*
 *  NumberFont.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/15/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Graphics.h"
#include "Point.h"
#include <stack>
#include "RepeatedSpriteHelper.h"

using namespace std;

enum FontAlignment { AlignFontRight, AlignFontCenter, AlignFontLeft };

class NumberFont
{
public:
	NumberFont(int fontAsset, int zPos);
	virtual ~NumberFont();

	void SetPosition(float xLoc, float yLoc);
	void RenderNumber(int _value);
	//void RenderBigNumber(int64_t _value);
	void RenderSpecial(int _frame);
	void SetMinDigits(int _value);
	int GetMinDigits() const;
	void SetAlignment(FontAlignment _value);
	int GetDigitWidth() { return numberSprite->GetFrameWidth(); }
	void Begin();
	void End();
	void SetFontAsset(int _asset);
	void SetDesignSize(int _width, int _height);

private:
	CR::Math::PointF offset;
	CR::Graphics::Sprite *numberSprite;
	int m_minDigits;
	FontAlignment m_align;
	CR::Game::RepeatedSpriteHelper m_spriteHelper;
	bool m_helperLock;
};