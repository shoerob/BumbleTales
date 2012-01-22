#include "Graphics.h"
#include "GraphicsEngineInternal.h"

using namespace CR::Graphics;

GraphicsEngineInternal *gengine = NULL;

GraphicsEngine* CR::Graphics::GetGraphicsEngine()
{
	if(gengine == NULL)
	{
		gengine = new GraphicsEngineInternal();
	}
	gengine->AddRef();
	return gengine;
}