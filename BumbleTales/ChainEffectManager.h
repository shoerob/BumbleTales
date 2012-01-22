/*
 *  ChainEffectManager.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 8/29/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#include "ChainEffect.h"
#include <vector>
using namespace std;

class ChainEffectManager
{
public:
	ChainEffectManager();
	virtual ~ChainEffectManager();

	void Update();
	void Render();

	void AddChainEffect(int amount, int xLoc, int yLoc);
	
private:
	vector<ChainEffect*> chainEffects;
	CR::Graphics::Sprite *dummyChainSprite;
};