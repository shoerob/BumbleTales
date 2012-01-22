#ifndef HPT_TILE_BACKGROUND_INTERNAL_H
#define HPT_TILE_BACKGROUND_INTERNAL_H

#include "Graphics.h"
#include "SpriteInternal.h"
#include "Vertex.h"
#include "Color.h"
#include <string>

struct Tile
{
	unsigned short layer;
};
namespace CR
{
	namespace Graphics
	{
		class TileBackgroundInternal : public TileBackground  
		{
		public:
			void ReLoad();
			//void RenderHighQuality(TileBackgroundInternal *arg);
			void Render();
			TileBackgroundInternal();
			virtual ~TileBackgroundInternal();
			virtual void LoadTileSet(char *name);
			virtual void Release();
			inline virtual void SetPositionAbsolute(float x,float y)
			{
				x_position = x;
				y_position = y;

			};
			inline virtual void SetPositionRelative(int x,int y)
			{
				x_position = x;
				y_position = y;

			};
			float y_position;
			float x_position;
			unsigned int tile_matrix_height;
			unsigned int tile_matrix_width;
			unsigned char *tile_flags;
			
			void Free();
	
			virtual CR::Math::Color32 Color() const {return m_color;}
			virtual void Color(const CR::Math::Color32 &_color) { m_color = _color;}
			virtual bool Lighting() const {return m_lighting;}
			virtual void Lighting(bool _enable) {m_lighting = _enable;}			
			
		private:
			const static int gridWidth = 31;
			const static int gridHeight = 21;
			const static int vertsPerTile = 4;
			const static int c_indicesPerTile = 6;
			
			SpriteInternal *tile_sprite;
			TextureStruct *tiles;
			Tile *tile_matrix;
			bool set_loaded;
			std::string m_fileName;
			
			CR::Graphics::Vertex m_vertices[vertsPerTile*gridWidth*gridHeight];
			GLushort m_indices[c_indicesPerTile*gridWidth*gridHeight];
			
			CR::Math::Color32 m_color;
			bool m_lighting;
			void ProcessColor();

		};
	}
}

#endif