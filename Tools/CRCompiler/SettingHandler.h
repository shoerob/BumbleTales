#pragma once
#include "..\CRCompilerlibrary\inodehandler.h"

namespace CR
{
	namespace Compiler
	{
		class SettingHandler :
			public CR::Compiler::INodeHandler
		{
		public:
			SettingHandler(void);
			virtual ~SettingHandler(void);
			virtual std::wstring Handles() {return L"setting";}
			virtual std::wstring Parent() {return L"compiler-settings";}
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value);
			virtual CR::Compiler::INodeCompiler* StartElement() {return NULL;}
			virtual void EndElement();
		private:
			std::wstring name;
			std::wstring value;
		};
	}
}
