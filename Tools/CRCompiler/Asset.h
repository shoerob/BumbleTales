#pragma once
#include "Guid.h"
#include <iostream>
#include <vector>
#include <fstream>

namespace CR
{
	namespace Compiler
	{
		class Asset
		{
		public:
			Asset(void);
			~Asset(void);
			const std::wstring& Name() const {return name;}
			void Name(const std::wstring &_name) {name = _name;}
			const CR::Utility::Guid& ID() {return id;}
			void ID(const std::wstring &_id) {id.Set(_id);}
			void ID(const CR::Utility::Guid &_id) {id = _id;}
			void AddChild(Asset *_child) {children.push_back(_child);}
			void GenerateFile(std::wofstream &_outputFile);
                        Asset* Parent() const {return m_parent;}
                        void Parent(Asset *_parent) {m_parent = _parent;}
		private:
			void OutputAsset(std::wofstream &_outputFile,std::wstring _tabs);
			std::wstring name;
			CR::Utility::Guid id;
			std::vector<Asset*> children;
                        Asset *m_parent;
		};
	}
}
