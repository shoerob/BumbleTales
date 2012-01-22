#include "TileBackgroundInternal.h"
#include "GraphicsEngineInternal.h"
#include <vector>
#include "GLES/gl.h"

using namespace std;
using namespace CR::Graphics;

extern GraphicsEngineInternal *gengine;
//extern void GENEW(void *arg);

TileBackgroundInternal::TileBackgroundInternal() : m_color(255,255,255,255), m_lighting(false)
{
	tile_sprite = NULL;
	tile_matrix = NULL;
	tile_flags = NULL;
	x_position = 0;
	y_position = 0;
	set_loaded = false;
	tiles = NULL;
	
	int y_step = gridWidth*vertsPerTile;
	int y_istep = gridWidth*c_indicesPerTile;
	
	for(int y = 0;y < gridHeight; y++)
	{
		for(int x = 0;x < gridWidth; x++)
		{
			m_vertices[y*y_step+x*vertsPerTile].X = x*16;
			m_vertices[y*y_step+x*vertsPerTile].Y = -y*16;
			m_vertices[y*y_step+x*vertsPerTile+1].X = x*16+16;
			m_vertices[y*y_step+x*vertsPerTile+1].Y = -y*16;
			m_vertices[y*y_step+x*vertsPerTile+2].X = x*16;
			m_vertices[y*y_step+x*vertsPerTile+2].Y = -y*16-16;
			m_vertices[y*y_step+x*vertsPerTile+3].X = x*16+16;
			m_vertices[y*y_step+x*vertsPerTile+3].Y = -y*16-16;
			
			m_indices[y*y_istep+x*c_indicesPerTile] = y*y_step+x*vertsPerTile;
			m_indices[y*y_istep+x*c_indicesPerTile+1] = y*y_step+x*vertsPerTile+1;
			m_indices[y*y_istep+x*c_indicesPerTile+2] = y*y_step+x*vertsPerTile+2;
			m_indices[y*y_istep+x*c_indicesPerTile+3] = y*y_step+x*vertsPerTile+1;
			m_indices[y*y_istep+x*c_indicesPerTile+4] = y*y_step+x*vertsPerTile+3;
			m_indices[y*y_istep+x*c_indicesPerTile+5] = y*y_step+x*vertsPerTile+2;
		}
	}
}

TileBackgroundInternal::~TileBackgroundInternal()
{
	Free();
}

void TileBackgroundInternal::Free()
{
	if(tile_sprite != NULL)
	{
		tile_sprite->Release();
		tile_sprite = NULL;
	}
	if(tile_matrix != NULL) delete[] tile_matrix;
	tile_matrix = NULL;
	if(tile_flags != NULL) delete[] tile_flags;
	tile_flags = NULL;
	if(tiles != NULL)
	{
		tiles->ReleaseTexture();
		delete tiles;
		tiles = NULL;
	}
}

void TileBackgroundInternal::LoadTileSet(char *name)
{
	if(m_fileName.empty())
		m_fileName = name;

	tile_sprite = new SpriteInternal();

	int count;
	int color_key_red;
	int color_key_blue;
	int color_key_green;
	if(tile_matrix != NULL) delete[] tile_matrix;
	if(tile_flags != NULL) delete[] tile_flags;
	if(tiles != NULL) delete tiles;
	
	FILE* filep;
	filep = fopen(name,"rb");
	char temp[3];
	fread(temp,sizeof(char),3,filep);
	if((temp[0] != 'H') || (temp[1] != 'T') || (temp[2] != 'F'))
	{
		fclose(filep);
		return;
	}
	int tempi;
	fread(&tempi,sizeof(int),1,filep);
	if(tempi != 1)
	{
		fclose(filep);
		return;
	}
	tiles = new TextureStruct();
	//GENEW(tiles);
//	fread(&(tiles->width),sizeof(int),1,filep);
//	fread(&(tiles->height),sizeof(int),1,filep);
	tiles->width = 16;
	tiles->height = 16;
	fread(&(tiles->total_width),sizeof(int),1,filep);
	fread(&(tiles->total_height),sizeof(int),1,filep);
	//tiles->m_halfu = 1.0f/(1.0f*(tiles->total_width))*0.375f;
	//tiles->m_halfv = 1.0f/(1.0f*tiles->total_height)*0.375f;
	tiles->m_halfu = 0.5f/tiles->GetNextPowerOf2(tiles->total_width);
	tiles->m_halfv = 0.5f/tiles->GetNextPowerOf2(tiles->total_height);
	color_key_red = 255;
	color_key_green = 0;
	color_key_blue = 255;


	tiles->color_key = 0;
	tiles->color_key += (color_key_red)>>3;
	tiles->color_key = (tiles->color_key)<<5;
	tiles->color_key += (color_key_green)>>3;
	tiles->color_key = (tiles->color_key)<<5;
	tiles->color_key += (color_key_blue)>>3;
	tiles->color_key = (tiles->color_key)<<1;
	
	tiles->default_frame_rate = 1;
	tiles->default_auto_animate = false;
	fread(&(tiles->num_frame_sets),sizeof(int),1,filep);

	tiles->frames_per_set = new int[tiles->num_frame_sets];
	fread(&(tiles->frames_per_set[0]),sizeof(int)*tiles->num_frame_sets,1,filep);
	tiles->ReadPNG(name,filep);
	vector<unsigned char> opacityCollecter;
	tiles->LoadTextureTiles(filep,opacityCollecter);
	tiles->ref_count++;
	fread(&tile_matrix_width,sizeof(int),1,filep);
	fread(&tile_matrix_height,sizeof(int),1,filep);
	
	tile_matrix = new Tile[tile_matrix_width*tile_matrix_height];
	tile_flags = new unsigned char[tile_matrix_width*tile_matrix_height];
	fread(tile_matrix,sizeof(Tile),tile_matrix_width*tile_matrix_height,filep);

	for(count = 0;count < (signed)tile_matrix_width*(signed)tile_matrix_height;count++)
	{
		char tempi = 0/*tile_matrix[count].flip*/;
		if(tile_matrix[count].layer & 0x08000) tempi = tempi | HFLIP;
		if(tile_matrix[count].layer & 0x04000) tempi = tempi | VFLIP;
		//if(isopaq[tile_matrix[count].layer & 0x03fff]) tempi = tempi | HPTOPAQUE;
		tile_matrix[count].layer = tile_matrix[count].layer & 0x03fff;
		if(!opacityCollecter[tile_matrix[count].layer]) tempi = tempi | HPTOPAQUE;
		tile_flags[count] = tempi;

	}


	tile_sprite->SetTexture(tiles);

	tile_sprite->SetFrameSet(0);

	tile_sprite->SetAutoAnimate(false);

	fclose(filep);
	set_loaded = true;
}

void TileBackgroundInternal::Release()
{
	delete this;
}

void TileBackgroundInternal::ProcessColor()
{	
	int y_step = gridWidth*vertsPerTile;	
	for(int y = 0;y < gridHeight; y++)
	{
		for(int x = 0;x < gridWidth; x++)
		{
			m_vertices[y*y_step+x*vertsPerTile].Color = m_color;
			m_vertices[y*y_step+x*vertsPerTile+1].Color = m_color;
			m_vertices[y*y_step+x*vertsPerTile+2].Color = m_color;
			m_vertices[y*y_step+x*vertsPerTile+3].Color = m_color;
		}
	}	
}

void TileBackgroundInternal::Render()
{
	if(!set_loaded) return;
	
	int y_step = gridWidth*vertsPerTile;
	
	int startX = 0;
	if((x_position+15) < 0)
	{
		startX = ((-(x_position))/16);
	}
	int endX = startX + 31;
	if(endX > (signed)tile_matrix_width) endX = tile_matrix_width;
	
	int startY = 0;
	if((y_position+15) < 0)
	{
		startY = ((-(y_position))/16);
	}
	int endY = startY + 21;
	if(endY > (signed)tile_matrix_height) endY = tile_matrix_height;
	
	float rowStep = 16.0f/tiles->GetNextPowerOf2(tiles->total_height);
	float rowHeight = 15.0f/tiles->GetNextPowerOf2(tiles->total_height);
	int total_width = tiles->GetNextPowerOf2(tiles->total_width);

	vector<GLfloat> opaqueGridVerts;
	vector<GLfloat> opaqueGridTexCoords;
	vector<GLfloat> transGridVerts;
	vector<GLfloat> transGridTexCoords;

	int lastRow = (tiles->GetNextPowerOf2(tiles->total_height)/16)-1;
	Tile *temp2;
	Tile *temp2i = tile_matrix + startX;
	for(int y = startY;y < endY; y++)
	{
		temp2 = temp2i + tile_matrix_width*y;
		int flags_offset = tile_matrix_width*(y) + startX;
		for(int x = startX;x < endX; x++)
		{
			int row = lastRow - ((temp2->layer>>6) & 0x00fff);
			
			int tile = temp2->layer & 0x0003f;
			
			int flags = tile_flags[flags_offset];
			int texCoordsOffset = (y-startY)*y_step+(x-startX)*vertsPerTile;
						
			float left = tile*(16.0f/total_width)+tiles->m_halfu;
			float right = tile*(16.0f/total_width)+(15.0f/total_width)+tiles->m_halfu;
			float top = row*rowStep+tiles->m_halfv;
			float bot = row*rowStep+rowHeight+tiles->m_halfv;
			
			if(flags&HFLIP)
			{
				m_vertices[texCoordsOffset].U = right;
				m_vertices[texCoordsOffset+1].U = left;
				m_vertices[texCoordsOffset+2].U = right;
				m_vertices[texCoordsOffset+3].U = left;
			}
			else
			{
				m_vertices[texCoordsOffset].U = left;
				m_vertices[texCoordsOffset+1].U = right;
				m_vertices[texCoordsOffset+2].U = left;
				m_vertices[texCoordsOffset+3].U = right;
			}
			
			if(flags&VFLIP)
			{
				m_vertices[texCoordsOffset].V = top;
				m_vertices[texCoordsOffset+1].V = top;
				m_vertices[texCoordsOffset+2].V = bot;
				m_vertices[texCoordsOffset+3].V = bot;
			}
			else
			{
				m_vertices[texCoordsOffset].V = bot;
				m_vertices[texCoordsOffset+1].V = bot;
				m_vertices[texCoordsOffset+2].V = top;
				m_vertices[texCoordsOffset+3].V = top;
			}

			/*if(temp2->layer != 0)
			{
				if(flags & HPTOPAQUE)
				{
					for(int i = 0;i < 12;++i)
					{
						opaqueGridTexCoords.push_back(gridTexCoords[texCoordsOffset+i]);
						opaqueGridVerts.push_back(gridVerts[texCoordsOffset+i]);
					}
				}
				else
				{
					for(int i = 0;i < 12;++i)
					{
						transGridTexCoords.push_back(gridTexCoords[texCoordsOffset+i]);
						transGridVerts.push_back(gridVerts[texCoordsOffset+i]);
					}
				}
			}*/
			
			temp2++;
			flags_offset++;
		}
	}	
	
	ProcessColor();
	
	glPushMatrix();
	glTranslatef(x_position-240+(startX<<4), 160-y_position-(startY<<4), -60.0f);
	
	glBindTexture(GL_TEXTURE_2D,tiles->glTextureIds[0]);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if(gengine->IsHD())
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glEnable(GL_TEXTURE_2D);	
	
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
    //glVertexPointer(2, GL_FLOAT, 0, gridVerts);
	glVertexPointer(2, GL_FLOAT, 0, &opaqueGridVerts[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, 0, gridTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, &opaqueGridTexCoords[0]);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &(m_vertices[0].Color));
    glEnableClientState(GL_COLOR_ARRAY);
	
	//glDrawArrays(GL_TRIANGLES, 0, gridWidth*gridHeight*6);
	glDrawArrays(GL_TRIANGLES, 0, opaqueGridTexCoords.size()/2);


	glEnable(GL_ALPHA_TEST);
	glVertexPointer(2, GL_FLOAT, 0, &transGridVerts[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &transGridTexCoords[0]);
	glDrawArrays(GL_TRIANGLES, 0, transGridTexCoords.size()/2);

	glPopMatrix();				  
}

void TileBackgroundInternal::ReLoad()
{
	Free();
	LoadTileSet(const_cast<char*>(m_fileName.c_str()));
	//tiles->ReLoad();
}


