#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class SoundCompiler;

		class SoundHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			SoundHandler(void);
			virtual ~SoundHandler(void);
			virtual std::wstring Handles() {return L"sound";}
			virtual std::wstring Parent() {return L"sounds";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value);
			virtual CR::Compiler::INodeCompiler* StartElement();
		private:
			SoundCompiler* compiler;
		};
	}
}
