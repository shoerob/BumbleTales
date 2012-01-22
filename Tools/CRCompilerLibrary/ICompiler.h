#pragma once
#include <string>

namespace CR
{
	namespace Compiler
	{
		//!Used by a plugin to retrieve basic values from the main compiler.
		/*
			You can implement an optional function in your plugin SetCompiler(ICompiler* compiler).
			This function must be exported from your dll without namemangling. If the Syntax Compiler 
			detects this function in your dll, it will be called, passing you an ICompiler* to use.
			This can be used to retrieve compiler setting passed in the xml or command line, and
			can be used to get the paths associated with the compile.
		*/
		class ICompiler
		{
		public:
			ICompiler(void)	{}
			virtual ~ICompiler(void) {}
			//! Returns the Path the the SyntaxCompiler exe file.
			virtual const std::wstring& CompilerPath() = 0;
			//! Returns the Path where the xml source file was located.
			virtual const std::wstring& DataPath() = 0;
			//! Can be used to determine if a setting exists.
			/*!
				Settings can be specified in the source xml file in Setting tags, or they
				can be passed in on the command line. 
			*/
			virtual bool SettingExists(const std::wstring &setting) const = 0;
			//! Get the value for a setting. Returns NULL if the setting doesnt exist.
			/*!
				If a value isnt specified, will return an empty string. This can happen if
				a value is passed in on the command line with no value(i.e. SyntaxCompiler data.xml rebuild). 
				rebuild would have an empty string as a value in this example. Can also happen if there is no value
				specified in the setting tag of an xml setting.
			*/
			virtual const std::wstring* GetSettingValue(const std::wstring &setting) const = 0;
			//!Add a new setting to the compiler. Not normally called from a plugin.
			/*!
				If a setting already exists, its value will be replaced.
			*/
                        virtual void AddSetting(const std::wstring &name,const std::wstring &value) = 0;
		};
	}
}
