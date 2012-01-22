#pragma once
#include "inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class BuffersCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			BuffersCompiler(void);
			virtual ~BuffersCompiler(void);
			virtual std::wstring IndexName() {return L"buffers";}
		};
	}
}
