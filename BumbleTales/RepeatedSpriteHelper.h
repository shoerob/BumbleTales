/*
 *  RepeatedSpriteHelper.h
 *  Bumble Tales
 *
 *  Created by Eric Duhon on 8/22/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include <memory>

namespace CR
{
	namespace Game
	{
		class RepeatedSpriteHelperImpl;
		
		class RepeatedSpriteHelper
		{
		public:
			RepeatedSpriteHelper(int _image,bool _singleSetMode, int _zInitial);
			void Start();
			void End();
			void NewSprite();
			void SetPosition(int _x,int _y);
			void SetFrame(int _frame);
			void SetFrameRate(int _frameRate);
			void SetImage(int _image);
			void SetDesignSize(int _width, int _height);

		private:
			std::auto_ptr<RepeatedSpriteHelperImpl> m_impl;
		};
	}
}