#ifndef HPT_FONT_INTERNAL_1_H
#define HPT_FONT_INTERNAL_1_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include<string>
#include "Graphics.h"
#include "TexturesInternal.h"
#include "SpriteInternal.h"

namespace CR
{
	namespace Graphics
	{		
		class FontInternal : public Font  
		{
		public:
			void Render(char *arg,int& x,int& y,int py);
			inline void SetPosition(int x,int y)
			{
				current_x = x;
				current_y = y;
				sprite.SetPositionAbsolute(x,y);
			};
			FontInternal();
			virtual ~FontInternal();
			virtual void LoadHFFFont(char *fontname);
			virtual void Release();
			
			void Reload();
			void Free();
			virtual CR::Math::Color32 Color() const {return sprite.Color();}
			virtual void Color(const CR::Math::Color32 &_color) { sprite.Color(_color);}
		private:
			void Clear();
			int current_y;
			int current_x;
			int keyred;
			int keygreen;
			int keyblue;
			int fringered;
			int fringegreen;
			int fringeblue;
			int height;
			int width;
			int charwidths[95];
			TextureStruct *texture;
			SpriteInternal sprite;
			int numChars;
			std::string m_fontName;
		};
	}
}

#endif