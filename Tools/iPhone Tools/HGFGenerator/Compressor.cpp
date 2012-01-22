#include "StdAfx.h"
#include "Compressor.h"
//#include "lzmalib.h"
//#include "Snappy.h"

#include "lzo/lzoconf.h"
#include "lzo/lzo1x.h"

Compressor::Compressor(unsigned char* _source,unsigned int unCompressedSize,Syntax::Utility::BinaryWriter &_file) : m_source(_source)
{
	//_file.Write((char*)_source,unCompressedSize);

	unsigned long compressedSize = static_cast<unsigned long>(unCompressedSize*1.5);
	unsigned char* compressed = new unsigned char[compressedSize];
	lzo_init();
	unsigned char* wrkmem = new unsigned char[LZO1X_999_MEM_COMPRESS];
	lzo1x_999_compress(_source,unCompressedSize,compressed,&compressedSize,wrkmem);
	lzo1x_optimize(compressed,compressedSize,_source,(lzo_uint*)&unCompressedSize,NULL);
	_file.Write((char*)compressed,compressedSize);
	delete[] compressed;

	/*size_t compressedSize = snappy::MaxCompressedLength(unCompressedSize);
	char* compressed = new char[compressedSize];
	snappy::RawCompress((char*)_source, unCompressedSize,compressed,&compressedSize);
	_file.Write(compressed,compressedSize);
	delete[] compressed;*/

	/*size_t propSize = LZMA_PROPS_SIZE;
	unsigned char *props = new unsigned char[propSize];
	unsigned int compressedSize = compressedSize*1.5;
	unsigned char* compressed = new unsigned char[compressedSize];
	
	LzmaCompress(compressed,&compressedSize,m_source,unCompressedSize,
		props,&propSize,9,128*1024,-1,-1,-1,-1,-1);

	_file.Write((char*)props,propSize);
	_file.Write((char*)compressed,compressedSize);
	delete[] props;
	delete[] compressed;*/
}

Compressor::~Compressor(void)
{
}
