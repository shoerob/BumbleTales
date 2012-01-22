#ifndef HPT_BACKGROUND_INTERNAL_H
#define HPT_BACKGROUND_INTERNAL_H

#include "Graphics.h"
#include "TexturesInternal.h"
#include "TileBackgroundInternal.h"
#include "Color.h"

namespace CR
{
	namespace Graphics
	{		
		class BackgroundInternal : public Background  
		{
		public:
			void ReLoad();
			BackgroundInternal();
			virtual ~BackgroundInternal();
			inline virtual void SetImage(int pallette_entry);
			virtual void Release();
			virtual void Render();
			
			virtual CR::Math::Color32 Color() const {return m_color;}
			virtual void Color(const CR::Math::Color32 &_color) { m_color = _color;}
			virtual bool Lighting() const {return m_lighting;}
			virtual void Lighting(bool _enable) {m_lighting = _enable;}	
			void Free()		;

		private:
			int image_number;
			TextureStruct *texture;
			CR::Graphics::Vertex m_vertices[4];
			CR::Math::Color32 m_color;
			bool m_lighting;
			void ProcessColor();
		};
	}
}

#endif 