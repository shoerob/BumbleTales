/*
 *  ParticleSystemManager.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/28/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "ParticleSystem.h"
#include <vector>
#include "IRenderable.h"

class ParticleSystemManager : public IRenderable
{
public:
	ParticleSystemManager();
	virtual ~ParticleSystemManager();

	void AddParticleSystem(ParticleSystem *pSystem);
	
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc) {};
	void PauseAnimation(bool pause);
	
private:
	vector<ParticleSystem*> particleSystems;
	vector<CR::Graphics::Sprite*> dummyParticles;
};