#include "texturestruct.h"
#include "GraphicsEngineInternal.h"
//#include "zlib.h"
#include "..\..\BumbleTales\AppConfig.h"
#include "FunctionObjects.h"
//#include "LZmaDec.h"
#include "..\..\thirdparty\lzo\minilzo\minilzo.h"

//#include "Alloc.h"

//static void* SzAlloc(void *p, size_t size) { p = p; return MyAlloc(size); }
//static void SzFree(void *p, void *address) { p=p; MyFree(address); }
//static ISzAlloc g_Alloc = {SzAlloc, SzFree };

using namespace CR::Graphics;
extern GraphicsEngineInternal *gengine;
//extern void GENEW(void *arg);
#include "s3e.h"

using namespace std;
using namespace CR::Utility;

static void checkEGLErrors()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR /*EGL_SUCCESS*/)
    {
		//stringstream error;
		//error << "gl error" << error;
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "EGL Error");
    }
}

int TextureStruct::ReadPNG(char *name,FILE* &filep)
{
	padded_height = GetNextPowerOf2(height);
	strcpy(file_name,name);

	int bytes_read = 0;
	fread(&bytes_read,sizeof(int),1,filep);
	zlib_size = bytes_read;
	zlib_pos = ftell(filep);
	fseek(filep,bytes_read,SEEK_CUR);

	return bytes_read+4;
}

void TextureStruct::LoadTexture()
{
	if(glTextureIds != NULL) FreeTexture();
		
	unsigned char *stream;
	FILE *filep = NULL;
	if(m_stream)
	{
		stream = m_stream;
	}
	else
	{
		filep = fopen(file_name,"rb");
		fseek(filep,zlib_pos,SEEK_SET);

		stream = new unsigned char[zlib_size];
		fread(stream,sizeof(unsigned char),zlib_size,filep);
	}
	
	unsigned long unCompressedSize = 0;
	unsigned long unCompressedSizeOrig = 0;
	if(type == 0 || type == 1)
		unCompressedSize = unCompressedSizeOrig = total_width * total_height*2;
	else if(type == 2)
		unCompressedSize = unCompressedSizeOrig = total_width * total_height*4;
	else if(type == 3)
		unCompressedSize = unCompressedSizeOrig = total_width * total_height*3;

	vector<unsigned char> unCompressed;
	unCompressed.resize(unCompressedSize);

	lzo1x_decompress(stream, zlib_size, &unCompressed[0], &unCompressedSize, NULL);
	assert(unCompressedSize == unCompressedSizeOrig);

	old_num_frame_sets = num_frame_sets;
	numTextures = num_frame_sets;

	eglGetError();
	glTextureIds = new GLuint[numTextures];
	//glGenTextures(numTextures,glTextureIds);
	//checkEGLErrors();
		
	assert(numTextures == num_frame_sets);
	for(int count = 0;count < num_frame_sets;count++)
	{
		glGenTextures(1, &glTextureIds[count]);
		GLuint temp = glTextureIds[count];
		glBindTexture(GL_TEXTURE_2D,temp);	
		assert(glIsTexture(temp));
		checkEGLErrors();
	    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					   GL_LINEAR);
	    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
					   GL_LINEAR);
		checkEGLErrors();

		if(type == 0)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,&unCompressed[total_width*padded_height*2*count]);
		else if(type == 1)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_4_4_4_4,&unCompressed[total_width*padded_height*2*count]);
		else if(type == 2)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_BYTE,&unCompressed[total_width*padded_height*4*count]);
		else if(type == 3)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, total_width,padded_height,0,
						 GL_RGB,GL_UNSIGNED_BYTE,&unCompressed[total_width*padded_height*3*count]);
		checkEGLErrors();
		assert(glIsTexture(temp));
	}
	/*z_stream zlib_stream;
	unsigned long size = total_width*1*2+1;

	memset(&zlib_stream,0,sizeof(z_stream));
	zlib_stream.next_in = stream;
	zlib_stream.avail_in = zlib_size;
	zlib_stream.data_type = Z_BINARY;

	inflateInit(&zlib_stream);

	old_num_frame_sets = num_frame_sets;
	numTextures = num_frame_sets;

	glTextureIds = new GLuint[numTextures];
	glGenTextures(numTextures,glTextureIds);
	
	for(int count = 0;count < num_frame_sets;count++)
	{
		unsigned char *tempout = NULL;
		if(type <= 1)
			tempout = new unsigned char[total_width*padded_height*2];
		else if(type == 2)
			tempout = new unsigned char[total_width*padded_height*4];
		else if(type == 3)
			tempout = new unsigned char[total_width*padded_height*3];
			
		zlib_stream.next_out = tempout;//reinterpret_cast<unsigned char*>(tempout);
		if(type <= 1)
			zlib_stream.avail_out = total_width*padded_height*2;
		else if(type == 2)
			zlib_stream.avail_out = total_width*padded_height*4;
		else if(type == 3)
			zlib_stream.avail_out = total_width*padded_height*3;
			
		//while(zlib_stream.avail_out > 0)
			inflate(&zlib_stream,Z_FINISH);
		
		glBindTexture(GL_TEXTURE_2D,glTextureIds[count]);	
		if(type == 0)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,tempout);
		else if(type == 1)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_4_4_4_4,tempout);
		else if(type == 2)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_BYTE,tempout);
		else if(type == 3)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, total_width,padded_height,0,
						 GL_RGB,GL_UNSIGNED_BYTE,tempout);
				
		delete[] tempout;
	}
	
	inflateEnd(&zlib_stream);*/

	if(!m_stream)
		delete[] stream;

	fclose(filep);
}

void TextureStruct::Cached()
{
	if(!m_stream)
	{
		FILE *filep = fopen(file_name,"rb");
		fseek(filep,zlib_pos,SEEK_SET);

		m_stream = new unsigned char[zlib_size];

		fread(m_stream,sizeof(unsigned char),zlib_size,filep);
	}

}

void TextureStruct::LoadTexture(FILE *filep)
{
	if(glTextureIds != NULL) FreeTexture();

	
	unsigned char *stream;
	fseek(filep,zlib_pos,SEEK_SET);

	stream = new unsigned char[zlib_size];
	fread(stream,sizeof(unsigned char),zlib_size,filep);
	
	unsigned long unCompressedSize = total_width * total_height;
	vector<unsigned char> unCompressed;
	unCompressed.resize(unCompressedSize);

	lzo1x_decompress(stream, zlib_size, &unCompressed[0], &unCompressedSize, NULL);
	
	old_num_frame_sets = num_frame_sets;
	numTextures = num_frame_sets;

	glTextureIds = new GLuint[numTextures];
	glGenTextures(numTextures,glTextureIds);

	
	for(int count = 0;count < num_frame_sets;count++)
	{
		glBindTexture(GL_TEXTURE_2D,glTextureIds[count]);	
		if(type == 0)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,&unCompressed[total_width*padded_height*2*count]);
		else if(type == 1)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_SHORT_4_4_4_4,&unCompressed[total_width*padded_height*2*count]);
		else if(type == 2)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
						 GL_RGBA,GL_UNSIGNED_BYTE,&unCompressed[total_width*padded_height*4*count]);
		else if(type == 3)
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, total_width,padded_height,0,
						 GL_RGB,GL_UNSIGNED_BYTE,&unCompressed[total_width*padded_height*3*count]);
	}
	delete[] stream;
}

void TextureStruct::FreeTexture()
{
	if(ref_count == 0) return;
	
	if(glTextureIds != NULL)
	{
		glDeleteTextures(numTextures,glTextureIds);
		delete[] glTextureIds;
		glTextureIds = NULL;
	}	
}

void TextureStruct::UseTexture()
{
	if(ref_count == 0) LoadTexture();
	ref_count++;	
}

void TextureStruct::ReleaseTexture()
{
	if(ref_count == 1) FreeTexture();
	ref_count--;
}

void TextureStruct::ReLoad()
{
	if(ref_count == 0) return;
	FreeTexture();
	LoadTexture();
	/*FILE *filep = fopen(file_name,"rb");
	fseek(filep,zlib_pos,SEEK_SET);
	z_stream zlib_stream;

	unsigned char *stream = new unsigned char[zlib_size];

	fread(stream,sizeof(unsigned char),zlib_size,filep);
	unsigned long size = total_width*1*3+1;
	unsigned char *tdata = new unsigned char[size];

	zlib_stream.next_in = stream;
	zlib_stream.avail_in = zlib_size;
	zlib_stream.total_in = 0;
	zlib_stream.next_out = tdata;
	zlib_stream.avail_out = size;
	zlib_stream.total_out = 0;
	zlib_stream.data_type = Z_BINARY;
	zlib_stream.zalloc = Z_NULL;
	zlib_stream.zfree = Z_NULL;

	inflateInit(&zlib_stream);

	for(int count = 0;count < num_frame_sets;count++)
	{
		unsigned short *tempout = new unsigned short[total_width*padded_height];
		int i=0;
			unsigned short tempi;
			for(int count3 = 0;count3 < padded_height;count3++)
			{
				zlib_stream.next_out = tdata;
				zlib_stream.avail_out = size;
				inflate(&zlib_stream,Z_SYNC_FLUSH);
				unsigned char *tempin = tdata;
	
				tempin++;

				for(int count2 = 0;count2 < total_width;count2++)
				{
					tempi = 0;
					tempi += (*tempin)>>3;
					tempi = tempi<<5;
					tempin++;
					tempi += (*tempin)>>3;
					tempi = tempi<<5;
					tempin++;
					tempi+= (*tempin)>>3;
					tempi = tempi<<1;
					if(color_key == 0 || tempi != color_key)
						tempi += 1;
					tempin++;
					tempout[(padded_height-count3-1)*total_width+count2] = tempi;
					i++;
				}
			}
		glBindTexture(GL_TEXTURE_2D,glTextureIds[count]);	
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, total_width,padded_height,0,
					 GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,tempout);
		
		delete[] tempout;
	}
	
	inflateEnd(&zlib_stream);
	delete[] tdata;
	delete[] stream;

	fclose(filep);*/
}

unsigned int TextureStruct::GetNextPowerOf2(unsigned int _original)
{
	unsigned int result = 2048;
	while ((result&_original) == 0 && result > 0)
	{
		result = result >> 1;
	}
	if(result == 0)
		return 0;
	if((_original&(result-1)) == 0)
		return result;
	else
		return result<<1;
}

void TextureStruct::LoadTextureTiles(FILE *filep,vector<unsigned char> &_opacityCollecter)
{
	/*if(glTextureIds != NULL) FreeTexture();
	
	int padded_width = GetNextPowerOf2(total_width);
	int padded_height = GetNextPowerOf2(total_height);
	
	fseek(filep,zlib_pos,SEEK_SET);
	z_stream zlib_stream;
	
	//vector<unsigned char> opacityColecter;
	_opacityCollecter.resize(total_width*total_height/16);
	FillAll(_opacityCollecter,0);

	unsigned char *stream = new unsigned char[zlib_size];
	
	fread(stream,sizeof(unsigned char),zlib_size,filep);
	unsigned long size = total_width*1*3+1;
	unsigned char *tdata = new unsigned char[size];
	
	zlib_stream.next_in = stream;
	zlib_stream.avail_in = zlib_size;
	zlib_stream.total_in = 0;
	zlib_stream.next_out = tdata;
	zlib_stream.avail_out = size;
	zlib_stream.total_out = 0;
	zlib_stream.data_type = Z_BINARY;
	zlib_stream.zalloc = Z_NULL;
	zlib_stream.zfree = Z_NULL;
	
	inflateInit(&zlib_stream);
	
	old_num_frame_sets = num_frame_sets;
	numTextures = 1;
	
	glTextureIds = new GLuint[numTextures];
	glGenTextures(numTextures,glTextureIds);
	unsigned short tempi;
	unsigned int tempipad;

	unsigned short *tempout = NULL;
	unsigned char *tempoutipad = NULL;

	if(AppConfig::Instance().IsIpad())
		tempoutipad = new unsigned char[padded_width*padded_height*4];
	else
		tempout = new unsigned short[padded_width*padded_height];
	

	int i=0;
		
	for(int count3 = 0;count3 < total_height;count3++)
	{
		zlib_stream.next_out = tdata;
		zlib_stream.avail_out = size;
		inflate(&zlib_stream,Z_SYNC_FLUSH);
		unsigned char *tempin = tdata;
			
		tempin++;
			
		if(AppConfig::Instance().IsIpad())
		{
			for(int count2 = 0;count2 < total_width;count2++)
			{
				unsigned char red = *tempin;
				tempin++;
				unsigned char green = *tempin;
				tempin++;
				unsigned char blue = *tempin;
				tempin++;

				unsigned char alpha = 0;
				bool transparent = (red == 255 && green == 0 && blue == 255);
				if(!transparent)
					alpha = 255;
				else
				{
					unsigned int index = ((count3/16)*(total_width/16)) + count2/16;
					if(_opacityCollecter[index] < 255)
						_opacityCollecter[index] += 1;
				}
				
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4] = red;
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4+1] = green;
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4+2] = blue;
				tempoutipad[(padded_height-count3-1)*padded_width*4+count2*4+3] = alpha;
				i++;
			}
		}
		else
		{
			for(int count2 = 0;count2 < total_width;count2++)
			{
				tempi = 0;
				tempi += (*tempin)>>3;
				tempi = tempi<<5;
				tempin++;
				tempi += (*tempin)>>3;
				tempi = tempi<<5;
				tempin++;
				tempi+= (*tempin)>>3;
				tempi = tempi<<1;
				if(color_key == 0 || tempi != color_key)
					tempi += 1;
				else
					_opacityCollecter[((count3/16)*total_width) + count2/16] += 1;
				tempin++;
				tempout[(padded_height-count3-1)*padded_width+count2] = tempi;
				i++;
			}
		}
	}
	glBindTexture(GL_TEXTURE_2D,glTextureIds[0]);	
	
	if(AppConfig::Instance().IsIpad())
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, padded_width,padded_height,0,
					GL_RGBA,GL_UNSIGNED_BYTE,tempoutipad);
	else
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, padded_width,padded_height,0,
					GL_RGBA,GL_UNSIGNED_SHORT_5_5_5_1,tempout);
		
	delete[] tempout;
	delete[] tempoutipad;

	inflateEnd(&zlib_stream);
	delete[] tdata;
	delete[] stream;*/
}

