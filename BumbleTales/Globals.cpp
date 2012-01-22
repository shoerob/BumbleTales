/*
 *  Globals.mm
 *  Bumble Tales
 *
 *  Created by Robert Shoemate on 7/2/09.
 *  Copyright 2009 Conjured Realms LLC. All rights reserved.
 *
 */

#include "Globals.h"

Globals::Globals()
{
	m_timer = new CR::Game::Timer();
}

Globals::~Globals()
{
	delete m_timer;
}

void Globals::Update()
{
	m_timer->Update();
}