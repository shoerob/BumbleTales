#pragma once
#include<fstream>
#include<vector>
#include "..\..\Engines\Utility\BinaryWriter.h"
#include "..\..\Engines\Utility\Guid.h"

namespace CR
{
	namespace Compiler
	{
		//! This will actually compile the data from the xml file into its binary equivalent.
		/*!
			Implement this interface for each compiler that you need. Usually one for each handler and corresponding
			xml tag. Your handler will be responsible for creating these.
		*/
		class INodeCompiler
		{
		public:
			INodeCompiler(void);
			INodeCompiler(const std::wstring &_name,const std::wstring &_guid);
			virtual ~INodeCompiler(void);
			//! This must never be called by/from a plugin. it is an internal compiler use only function
			void AddChild(INodeCompiler* child);
			//! This must never be called by/from a plugin. it is an internal compiler use only function
			void Compile(CR::Utility::BinaryWriter &writer);
			//user functions
			//! Should return the name that will be used in your game to get to this data
			/*!
				The reader used in game treats its records in a tree fashion according the xml.
				If your compiler is for a section then just return the name of the section here.
				Or return the name of the resource.
			*/
			virtual CR::Utility::Guid& Index() {return guid;}
			virtual void Index(const std::wstring _id) {guid.Set(_id);}
			virtual std::wstring& Name() {return name;}
			virtual void Name(const std::wstring& _name) {name = _name;}
			//! This is called when the actual data needs to be compiled. Your should write out all data to the provided writer.
			virtual void CompileData(CR::Utility::BinaryWriter &writer) {};
                        INodeCompiler* Parent() const {return m_parent;}
                        void Parent(INodeCompiler *_parent) {m_parent = _parent;}
                protected:
			std::vector<INodeCompiler*> children;
			std::wstring name;
			CR::Utility::Guid guid;
                        INodeCompiler *m_parent;
		};
	}
}
