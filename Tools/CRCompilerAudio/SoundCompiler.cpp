#include "StdAfx.h"
#include "SoundCompiler.h"

using namespace CR::Compiler;

SoundCompiler::SoundCompiler(void) : m_gain(1.0f), m_positional(false)
{
}

SoundCompiler::~SoundCompiler(void)
{
}

void SoundCompiler::CompileData(CR::Utility::BinaryWriter &writer)
{
	writer << m_buffer << m_gain << m_positional;
}