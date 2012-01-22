/*
 *  Vertex.h
 *  Steph
 *
 *  Created by Eric Duhon on 4/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "Color.h"

#include "GLES/gl.h"
namespace CR
{
	namespace Graphics
	{
		struct Vertex
		{
			GLfloat X,Y,Z;
			GLfloat U,V;
			CR::Math::Color32 Color;
		};
	}
}