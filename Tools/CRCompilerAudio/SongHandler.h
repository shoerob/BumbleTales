#pragma once
#include "inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class SongCompiler;

		class SongHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			SongHandler(void);
			virtual ~SongHandler(void);
			virtual std::wstring Handles() {return L"song";}
			virtual std::wstring Parent() {return L"music";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value);
			virtual CR::Compiler::INodeCompiler* StartElement();
		private:
			SongCompiler* compiler;
		};
	}
}
