#pragma once
#include "INodeCompiler.h"

namespace CR
{
	namespace Compiler
	{
		//! Interface a plugin has to implement to handle an xml tag in the source xml
		/*!
			Your plugin must export a non mangled function called GetHandlers(). This function 
			returns an stl vector of INodeHanlder*. You should create one copy of every handler in
			your plugin and return it in the vector returned from this function. The main compiler will take over managment
			of your handlers, so you do not need to keep track of them. when the compiler finishes, it
			will automaticly call Release on all your handlers, which will in turn call there destructors 
			and free them. 

			Every handler has to specify what tag it handles and what tag is should be beneath.

			The purpose of handlers is to handle the xml parsing. compilers are used to generate the data file.

			Each time the compiler encounters an instance of your tag in the source xml file. It will
			first call Startelement. You should create an implentation of ICompiler here and return it.
			Then the compiler will call handleAttribute for each attribute of the tag. You should pass these
			values to the compiler. The the compiler will call EndElement to signal it is done with this tag. 
			If another copy of the same tag occurs this process will repeat, but  you should normally be returning
			diffrent instances of your compiler for each one. The main compiler will automaticly assemble your INodeCompiler
			implementations into an appropriate tree structure.
		*/
		class INodeHandler
		{
		public:
			INodeHandler(void) {}
			virtual ~INodeHandler(void) {}
			//! Called by the compiler when the handler is no longer needed.
			void Release() {delete this;}
			//! plugin must return what tag this handler handles
			virtual std::wstring Handles() = 0;
			//! The parent tag that the tag this handlers handles must be beneath.
			virtual std::wstring Parent() = 0;
			//! Compiler will call this for each attribute in the tag specified by Handles.
			virtual void HandleAttribute(const std::wstring &name,const std::wstring& value) {}
			//! An instance of your tag was encountered. you should create a new compiler and return it.
			/*!
				Normally you will want to hold on to this compiler internally to pass attribute values to it.
				Any attributes passed will belong to this instance of the compiler until endelement is called.
			*/
			virtual INodeCompiler* StartElement() = 0;
			//! Not often needed, but  you can finalize any setting on your compiler here. called before moving to next tag.
			virtual void EndElement() {}
			//! This function will be called to let you know when processing of the data file has started.
			virtual void StartProcessing() {}
			//!This function will be called after the compiler has finished calling handlers for all xml data, but before calling any compilers.
			virtual void PreCompile() {}
			//! This function will be called to let you know when processing of the data file has ended.
			virtual void EndProcessing() {}
		};
	}
}
