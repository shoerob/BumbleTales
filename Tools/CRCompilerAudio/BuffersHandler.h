#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class BuffersHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			BuffersHandler(void);
			virtual ~BuffersHandler(void);
			virtual std::wstring Handles() {return L"buffers";}
			virtual std::wstring Parent() {return L"data";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value) {}
			virtual CR::Compiler::INodeCompiler* StartElement();
		};
	}
}
