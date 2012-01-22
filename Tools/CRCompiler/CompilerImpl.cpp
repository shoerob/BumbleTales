#include "CompilerImpl.h"
#include "FunctionObjects.h"
#include "INodeHandler.h"
#include "NodeHandler.h"
#include "DataHandler.h"
#include "CompilerSettingsHandler.h"
#include "OutputPathHandler.h"
#include "BinaryWriter.h"
#include "TopCompiler.h"
#include "SettingHandler.h"
#include "Asset.h"
#include "AssetPathHandler.h"
#include "AssetSectionHandler.h"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include <fstream>
#include "StringUtil.h"
#include <QFileInfo>
#include <QDir>
#include <QFile>

using namespace std;
using namespace std::tr1;
using namespace CR;
using namespace CR::Utility;
using namespace CR::Compiler;
using namespace boost;
//using namespace boost::filesystem;
//using namespace boost::lambda;

typedef vector<INodeHandler*> (*GetHandlers)(); 
typedef void (*SetCompiler)(CR::Compiler::ICompiler *compiler); 

void CompilerImpl::Init(const std::wstring &compilerPath,const std::wstring &dataPath,const std::wstring &dataFile)
{
        this->compilerPath = compilerPath;
	this->dataPath = dataPath;
	this->dataFile = dataFile;
	
	AddHandler(new DataHandler());
	AddHandler(new CompilerSettingsHandler());
	AddHandler(new OutputPathHandler());
	AddHandler(new SettingHandler());
	AddHandler(new AssetPathHandler());
	AddHandler(new AssetSectionHandler());

	LoadPlugins();
}

CompilerImpl::~CompilerImpl(void)
{
	for_each(handlers.begin(),handlers.end(),DeleteFOPair());
        //for_each(plugins.begin(),plugins.end(),ptr_fun(FreeLibrary));
        //plugins.clear();
	handlers.clear();
}

void CompilerImpl::AddHandler(INodeHandler* handler)
{
	handlers[handler->Handles()] = new NodeHandler(handler);
}

void CompilerImpl::LoadPlugins()
{
/*	for (wdirectory_iterator itr(compilerPath); itr!=wdirectory_iterator(); ++itr)
    {
		if(extension(itr->path()) == L".dll")
		{
			 wstring dllFile = itr->path().string();
			 HMODULE module = LoadLibrary(dllFile.c_str());
			 GetHandlers handlersCallback = (GetHandlers)GetProcAddress(module,"GetHandlers");
			 if(handlersCallback == NULL)
			 {
				 FreeLibrary(module);
			 }
			 else
			 {
				vector<INodeHandler*> newHandlers = handlersCallback();
				vector<INodeHandler*>::iterator iterator = newHandlers.begin();
				while(iterator != newHandlers.end())
				{
					NodeHandler *handler = new NodeHandler(*iterator);
					handlers[to_lower_copy(handler->Handles())] = handler;
					iterator++;
				}
				plugins.push_back(module);
				SetCompiler compilerCallback = (SetCompiler)GetProcAddress(module,"SetCompiler");
				if(compilerCallback != NULL)
				{
					compilerCallback(this);
				}
			 
			 }
		}
    }*/
}

NodeHandler* CompilerImpl::GetHandler(std::wstring name)
{
	to_lower(name);
        unordered_map<wstring,NodeHandler*>::iterator iterator = handlers.find(name);
	if(iterator == handlers.end())
		return NULL;
	return iterator->second;
}

const std::wstring& CompilerImpl::CompilerPath()
{
	return compilerPath;
}

const std::wstring& CompilerImpl::DataPath()
{
	return dataPath;
}

void CompilerImpl::Run()
{
    Convert stringConvert;
    string errorPath = stringConvert(compilerPath)+"/error_log.txt";
    wofstream logFile(errorPath.c_str(),ios::out|ios::trunc);
    wclog.rdbuf(logFile.rdbuf());

    outputPaths.clear();

    QFileInfo file(QDir(QString::fromStdWString(dataPath)),QString::fromStdWString(dataFile));

    QFile xmlFile( file.absoluteFilePath() );
    QXmlInputSource source( &xmlFile );

    XMLHandler handler;

    QXmlSimpleReader reader;
    reader.setContentHandler( &handler );

    CallOn2nd(handlers,&NodeHandler::StartProcessing);

    top = new TopCompiler();
    topAsset = new Asset();

    reader.parse( source );

    CallOn2nd(handlers,&NodeHandler::PreCompile);

    Compile();

    BuildAssetList();

    CopyFiles();

    CallOn2nd(handlers,&NodeHandler::EndProcessing);

    delete top;
    delete topAsset;

   /* HRESULT hr;
    CComPtr<IStream> pFileStream;
    CComPtr<IXmlReader> pReader;
    XmlNodeType nodeType;
    const WCHAR* localName;

	wpath file(dataPath);
	file /= dataFile;
	if (FAILED(hr = SHCreateStreamOnFile(file.string().c_str(), STGM_READ, &pFileStream)))
    {
		wclog << "Error creating file reader" << endl;
        return;
    }

    if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL)))
    {
		wclog << "Error creating xml reader" << endl;
        return;
    }

    if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
    {
		wclog << "Error setting XmlReaderProperty_DtdProcessing" << endl;
        return;
    }

    if (FAILED(hr = pReader->SetInput(pFileStream)))
    {
		wclog << "Error setting input for reader" << endl;
        return;
    }

	CallOn2nd(handlers,&NodeHandler::StartProcessing);
	
	top = new TopCompiler();
	topAsset = new Asset();

    //read until there are no more nodes
	bool done = false;
	while(!done)
	{
		if(S_OK == (hr = pReader->Read(&nodeType)))
		{
			switch (nodeType)
			{
			case XmlNodeType_Element:
				{
					if (FAILED(hr = pReader->GetLocalName(&localName, NULL)))
					{
						wclog << "Failed to read xml tag, invalid xml structure" << endl;
						return;
					}
					wstring tag(localName);
					to_lower(tag);
					if(tag != L"data")
					{
						wclog << "Top level tag must be data. top level tag was <" << tag << ">" << endl;
						done = true;
						break;
					}
					handlers[tag]->HandleNode(pReader,top,topAsset,pReader->IsEmptyElement()!=0);
					done = true;
				}
				break;
			case XmlNodeType_XmlDeclaration:
			case XmlNodeType_EndElement:
			case XmlNodeType_Text:
			case XmlNodeType_Whitespace:
			case XmlNodeType_CDATA:
			case XmlNodeType_ProcessingInstruction:
			case XmlNodeType_Comment:
			case XmlNodeType_DocumentType:
				break;
			}
		}
	}

	//MessageBox(NULL,L"error",L"error",MB_OK);
	CallOn2nd(handlers,&NodeHandler::PreCompile);

	Compile();

	BuildAssetList();

	CopyFiles();
	
	CallOn2nd(handlers,&NodeHandler::EndProcessing);

	delete top;
	delete topAsset;
        */
}

void CompilerImpl::Compile()
{
	if(outputPaths.size() == 0)
	{
		return;
	}
	BinaryWriter writer(dataPath+outputPaths[0]);

	top->Compile(writer);
}

void CompilerImpl::BuildAssetList()
{
    Convert convert;
        string outputFileName = convert(dataPath+assetPaths[0]);
	wofstream outputFile(outputFileName.c_str());

	topAsset->GenerateFile(outputFile);
}

void CompilerImpl::SetTop(CR::Compiler::INodeCompiler *top)
{
	this->top->realTop = top;
}

void CR::Compiler::CompilerImpl::CopyFiles(void)
{
    if(outputPaths.size() > 0)
    {
        QString original = QString::fromStdWString(dataPath+outputPaths[0]);
        for(unsigned int i = 1;i < outputPaths.size();i++)
        {
            QString newFile = QString::fromStdWString(dataPath+outputPaths[i]);
            QFile::remove(newFile);
            QFile::copy(original,newFile);
        }
    }

    if(assetPaths.size() > 0)
    {
        QString original = QString::fromStdWString(dataPath+assetPaths[0]);
            for(unsigned int i = 1;i < assetPaths.size();i++)
            {
                QString newFile = QString::fromStdWString(dataPath+assetPaths[i]);
                QFile::remove(newFile);
                QFile::copy(original,newFile);
            }
    }
}

bool CompilerImpl::SettingExists(const wstring &setting) const
{
        unordered_map<wstring,wstring>::const_iterator iterator = settings.find(setting);
	if(iterator == settings.end())
		return false;
	else
		return true;
}

const wstring* CompilerImpl::GetSettingValue(const wstring &setting) const
{
	if(!SettingExists(setting))
		return NULL;

        unordered_map<wstring,wstring>::const_iterator iterator = settings.find(setting);
	return &(iterator->second);
}

void CompilerImpl::AddSetting(const std::wstring &name,const std::wstring &value)
{
	settings[name] = value;
}

bool CompilerImpl::XMLHandler::startDocument()
{
    return true;
}

bool CompilerImpl::XMLHandler::startElement( const QString&, const QString& _localName, const QString& ,
                   const QXmlAttributes& )
{
    wstring tag(_localName.toStdWString());
    to_lower(tag);

    NodeHandler* handler = CompilerImpl::Instance().GetHandler(tag);
    //handler->HandleNode(top,topAsset,false);

    return true;
}

bool CompilerImpl::XMLHandler::endElement( const QString&, const QString&, const QString& )
{
    SwitchToParent();
    return true;
}
