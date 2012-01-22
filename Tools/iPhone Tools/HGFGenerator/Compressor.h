#pragma once

#include "..\Utility\BinaryWriter.h"

class Compressor
{
public:
	Compressor(unsigned char* _source,unsigned int unCompressedSize,Syntax::Utility::BinaryWriter &_file);
	virtual ~Compressor(void);
private:
	unsigned char* m_source;
	unsigned char* m_compressed;
};
