#include "NodeHandler.h"
#include "INodeHAndler.h"
#include "CompilerImpl.h"
#include "Asset.h"

using namespace std;
using namespace CR;
using namespace CR::Compiler;
using namespace boost;

NodeHandler::NodeHandler(INodeHandler* handler)
{
	this->handler = handler;
}

NodeHandler::~NodeHandler(void)
{
	handler->Release();
}

wstring NodeHandler::Handles()
{
	return handler->Handles();
}

wstring NodeHandler::Parent()
{
	return handler->Parent();
}

void  NodeHandler::HandleAttribute(const std::wstring &name,const std::wstring& value)
{
	handler->HandleAttribute(name,value);
}

void NodeHandler::HandleNode(/*CComPtr<IXmlReader> &pReader,*/INodeCompiler *parent,Asset *parentAsset,bool emptyElement)
{
        /*INodeCompiler *compiler = handler->StartElement();
	if(parent != NULL)
		parent->AddChild(compiler);

	Asset *childAsset;
	if(compiler && parentAsset)
	{
		childAsset = new Asset();
		parentAsset->AddChild(childAsset);
	}
	else
		childAsset = NULL;

	HRESULT hr;
    XmlNodeType nodeType;
    const WCHAR* localName;

	while(S_OK == (hr = pReader->MoveToNextAttribute()))
	{

		if (FAILED(hr = pReader->GetLocalName(&localName, NULL)))
		{
			wclog << "Failed to read xml attribute name" << endl;
			return;
		}
		wstring attribute(localName);
		const WCHAR* localValue;
		if (FAILED(hr = pReader->GetValue(&localValue, NULL)))
		{
			wclog << "Failed to read xml attribute value for " << attribute << endl;
		}
		wstring value(localValue);
		this->HandleAttribute(attribute,value);
	}
	
	if(compiler)
	{
		childAsset->ID(compiler->Index());
		childAsset->Name(compiler->Name());
	}
	if(emptyElement)
		return;
	while (S_OK == (hr = pReader->Read(&nodeType)))
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
				bool skip = false;
				wstring tag(localName);
				NodeHandler* handler = CompilerImpl::Instance().GetHandler(tag);
				if(handler == NULL)
				{
					wclog << "Unknown xml tag encountered: " << tag << endl;
					skip = true;
				}
				if(!skip)
				{
					if(handler->Parent() != this->Handles())
					{
						wclog << "Tag " << tag << " can not be nested under " << Handles() << endl;
						skip = true;
					}
					handler->HandleNode(pReader,compiler,childAsset,pReader->IsEmptyElement()!=0);
				}
				else
				{
					bool done = false;
					while (S_OK == (hr = pReader->Read(&nodeType)) && !done)
					{
						switch (nodeType)
						{
							case XmlNodeType_EndElement:
								if (FAILED(hr = pReader->GetLocalName(&localName, NULL)))
								{
									continue;
								}
								wstring endtag(localName);
								if(endtag == tag)
									done = true;
								break;
						};
					}
				}
			}
			break;
		case XmlNodeType_Attribute:

			break;
        case XmlNodeType_EndElement:
			return;
			break;
        case XmlNodeType_XmlDeclaration:
        case XmlNodeType_Text:
        case XmlNodeType_Whitespace:
        case XmlNodeType_CDATA:
        case XmlNodeType_ProcessingInstruction:
        case XmlNodeType_Comment:
        case XmlNodeType_DocumentType:
            break;
        }
    }*/
}			
void NodeHandler::StartProcessing()
{
	handler->StartProcessing();
}

void NodeHandler::EndProcessing()
{
	handler->EndProcessing();
}

void NodeHandler::PreCompile()
{
	handler->PreCompile();
}
