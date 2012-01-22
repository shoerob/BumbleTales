#pragma once
#include "..\CRCompilerLibrary\inodecompiler.h"

namespace CR
{
	namespace Compiler
	{
		class TopCompiler :
			public CR::Compiler::INodeCompiler
		{
		public:
			TopCompiler(void);
			virtual ~TopCompiler(void);
			void Compile(CR::Utility::BinaryWriter &writer) { realTop->Compile(writer);}
			INodeCompiler *realTop;
		};
	}
}
