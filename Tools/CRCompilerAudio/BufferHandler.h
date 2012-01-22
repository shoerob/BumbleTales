#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class BufferCompiler;

		class BufferHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			BufferHandler(void);
			virtual ~BufferHandler(void);
			virtual std::wstring Handles() {return L"buffer";}
			virtual std::wstring Parent() {return L"buffers";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value);
			virtual CR::Compiler::INodeCompiler* StartElement();
		private:
			BufferCompiler* compiler;
		};
	}
}
