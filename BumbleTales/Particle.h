/*
 *  Particle.h
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 5/27/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */
#pragma once
#include "Vector.h"
#include "Graphics.h"
#include "Point.h"
#include "IRenderable.h"

class Particle : public IRenderable
{
public:
	Particle();
	virtual ~Particle();
		
	virtual void Render() = 0;
	virtual void Update() = 0;
	
float IsDead() const { return m_isDead; }
protected:
	bool m_isDead;
	
	float FloatRand( float MaxVal )
	{
		return ( (float)rand( ) / (float)RAND_MAX ) * MaxVal;	
	}
};