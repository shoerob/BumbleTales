#pragma once
#include "inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class MusicCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			MusicCompiler(void);
			virtual ~MusicCompiler(void);
			virtual std::wstring IndexName() {return L"music";}
		};
	}
}
