/*
 *  CrystalParticleSystem.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/28/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "ParticleSystem.h"
#include "CrystalParticle.h"
#include "Point.h"
#include "ResourceTile.h"

class CrystalParticleSystem : public ParticleSystem
{
public:
	CrystalParticleSystem(CR::Math::PointF position, ResourceType rType);
	virtual ~CrystalParticleSystem();
	
	void Update();
	void Render();
	void SetPosition(float xLoc, float yLoc) {};
	void PauseAnimation(bool pause);
	
private:
	
	vector<Particle*> particles;
	CR::Math::PointF m_position;
	int m_life;
	
	//CrystalParticle *dummyTile1;
};