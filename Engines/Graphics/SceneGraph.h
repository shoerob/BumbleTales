/*
 *  SceneGraph.h
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/13/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <tr1/memory>

namespace CR
{
	namespace Graphics
	{
		class SceneGraphImpl;
		class SpriteInternal;
		
		class SceneGraph
		{
		public:			
			SceneGraph();
			void AddSprite(SpriteInternal *_sprite);
			void RemoveSprite(SpriteInternal *_sprite);
			int Size();
			int NumGroups();
			void Render();
			void BeginFrame();
		private:
			std::tr1::shared_ptr<SceneGraphImpl> m_impl;		
		};
	}
}