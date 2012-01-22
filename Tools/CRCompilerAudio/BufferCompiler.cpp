#include "StdAfx.h"
#include "BufferCompiler.h"
#include "CRCompilerAudio.h"
#include "Binaryreader.h"
#include "BinaryWriter.h"
#include "shellapi.h"
#include "StringUtil.h"

using namespace CR::Compiler;
using namespace CR::Utility;
using namespace std;
using namespace boost;
using namespace boost::filesystem;

BufferCompiler::BufferCompiler(void) : m_compressionType(OGG) , m_quality(2)
{
}

BufferCompiler::~BufferCompiler(void)
{
}

void BufferCompiler::CompileData(CR::Utility::BinaryWriter &writer)
{
	SetUpFileNames();
	CheckFile();
	if(needsToUpdate)
	{
		//Sleep(100);
		BuildFinal();
	}
	
	unsigned int numBytes = static_cast<unsigned long>(file_size(fileName)) - 44;
	/*BinaryReader reader(fileName);
	unsigned char header[40];
	unsigned int numBytes;
	reader >> header >> numBytes;*/
		
	unsigned long inputFileSize = static_cast<unsigned long>(file_size(finalFileName));
	scoped_array<char> inputBuffer(new char[inputFileSize]);
	ifstream inputFile(finalFileName.c_str(),ios::in | ios::binary);
	inputFile.read(inputBuffer.get(),inputFileSize);
	writer << numBytes << inputFileSize;
	if(m_compressionType == SPEEX)
		writer << 1;
	else
		writer << 0;
	writer.Write(inputBuffer.get(),inputFileSize);
}


void BufferCompiler::SetUpFileNames()
{
	wpath original(this->fileName);
	original.remove_leaf();
	wpath fileName(basename(this->fileName));
	wstringstream compiledFileName;
	compiledFileName << original << fileName;
	if(m_compressionType == SPEEX)
		compiledFileName << ".spx";
	else
		compiledFileName << ".ogg";

	this->fileName = Globals::Instance().Compiler()->DataPath() + this->fileName;

	this->finalFileName = Globals::Instance().Compiler()->DataPath() + compiledFileName.str();
}

void BufferCompiler::CheckFile()
{
	if(Globals::Instance().Compiler()->SettingExists(L"rebuild"))
	{
		needsToUpdate = true;
		return;
	}
	needsToUpdate = false;
	wpath finalPath(finalFileName);
	if(!exists(finalPath))
	{
		needsToUpdate = true;
		return;
	}
	wpath origPath(fileName);
	time_t originalFileTime = last_write_time(origPath);
	time_t finalFileTime = last_write_time(finalPath);
	if(originalFileTime > finalFileTime)
		needsToUpdate = true;
}


void BufferCompiler::BuildFinal()
{		
	wstringstream cmd;
	scoped_array<wchar_t> exe;
	if(m_compressionType == SPEEX)
	{
		cmd << L"speexenc.exe";
		
		cmd << L" --vbr --quality " << m_quality << L" ";
		cmd << L"\"" << fileName << L"\"" ; 
		
		wpath noextFilename(fileName);
		noextFilename.remove_leaf();
		cmd << L" \"" << finalFileName << L"\"" ; 

		exe.reset(new wchar_t[cmd.str().length()+2]);
		wcscpy(exe.get(),cmd.str().c_str());
	}
	else
	{
		cmd << L"oggenc2.exe";
		if(m_quality < 2)
			cmd << L" --resample 8000 -S 0";
		if(m_quality >= 2)
			m_quality -= 2;
		m_quality -= 1;
		cmd << L" -q " << m_quality << L" ";
		cmd << L"\"" << fileName << L"\"" ;  
		exe.reset(new wchar_t[cmd.str().length()+2]);
		wcscpy(exe.get(),cmd.str().c_str());
	}
	
	STARTUPINFO startupInfo;    
	PROCESS_INFORMATION processInfo;

    ZeroMemory( &startupInfo, sizeof(startupInfo) );
    startupInfo.cb = sizeof(startupInfo);
    ZeroMemory( &processInfo, sizeof(processInfo) );
	
	CreateProcess(NULL,exe.get(),NULL,NULL,false,0,NULL,NULL,&startupInfo,&processInfo);

	WaitForSingleObject( processInfo.hProcess, INFINITE );

    CloseHandle( processInfo.hProcess );
    CloseHandle( processInfo.hThread );	
}

void BufferCompiler::CompressionType(const std::wstring &_compressionType)
{
	if(CaseInsensitiveCompare(_compressionType,L"speex"))
		m_compressionType = SPEEX;
	else
		m_compressionType = OGG;
}