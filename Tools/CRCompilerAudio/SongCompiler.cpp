#include "StdAfx.h"
#include "SongCompiler.h"
#include "CRCompilerAudio.h"
#include "Binaryreader.h"
#include "BinaryWriter.h"

using namespace CR::Compiler;
using namespace CR::Utility;
using namespace std;
using namespace boost;
using namespace boost::filesystem;

SongCompiler::SongCompiler(void)
{
}

SongCompiler::~SongCompiler(void)
{
}

void SongCompiler::CompileData(CR::Utility::BinaryWriter &writer)
{
	SetUpFileNames();
	CheckFile();
	if(needsToUpdate)
	{
		//Sleep(100);
		BuildFinal();
	}
	
	BinaryReader reader(fileName);
	unsigned char header[40];
	unsigned int numBytes;
	reader >> header >> numBytes;

	unsigned long inputFileSize = static_cast<unsigned long>(file_size(finalFileName));
	scoped_array<char> inputBuffer(new char[inputFileSize]);
	ifstream inputFile(finalFileName.c_str(),ios::in | ios::binary);
	inputFile.read(inputBuffer.get(),inputFileSize);
	writer << numBytes << inputFileSize;
	writer.Write(inputBuffer.get(),inputFileSize);
}


void SongCompiler::SetUpFileNames()
{
	wpath original(this->fileName);
	original.remove_leaf();
	wpath fileName(basename(this->fileName));
	wstringstream compiledFileName;
	compiledFileName << original << fileName << ".mp3";

	this->fileName = Globals::Instance().Compiler()->DataPath() + this->fileName;

	this->finalFileName = Globals::Instance().Compiler()->DataPath() + compiledFileName.str();
}

void SongCompiler::CheckFile()
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


void SongCompiler::BuildFinal()
{	
	wstringstream cmd;
	scoped_array<wchar_t> exe;
	
	/*cmd << L"oggenc2.exe";
	if(m_quality < 2)
		cmd << L" --resample 8000 -S 0";
	if(m_quality >= 2)
		m_quality -= 2;
	m_quality -= 1;
	cmd << L" -q " << m_quality << L" ";
	cmd << L"\"" << fileName << L"\"" ; */ 

	
	cmd << L"lame.exe";
	cmd << L" -h --nores -V " << m_quality << L" ";
	cmd << L"\"" << fileName << L"\" \"" << finalFileName << L"\"";  

	exe.reset(new wchar_t[cmd.str().length()+2]);
	wcscpy(exe.get(),cmd.str().c_str());
	
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