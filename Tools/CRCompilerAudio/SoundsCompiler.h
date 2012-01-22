#pragma once
#include "inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class SoundsCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			SoundsCompiler(void);
			virtual ~SoundsCompiler(void);
			virtual std::wstring IndexName() {return L"sounds";}
		};
	}
}
