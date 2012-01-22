#pragma once
#include "inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class DataCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			DataCompiler(void);
			virtual ~DataCompiler(void);
		};
	}
}
