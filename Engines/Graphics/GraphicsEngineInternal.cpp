#include "GraphicsEngineInternal.h"
#include "SpriteInternal.h"
#include "BackgroundInternal.h"
//#include "asm.h"
#include "SceneGraph.h"

#include "s3e.h"
#include "../Utility/FunctionObjects.h"
#include <functional>
#include "..\..\thirdparty\lzo\minilzo\minilzo.h"

using namespace std;
using namespace std::tr1;
using namespace CR::Graphics;
using namespace CR::Utility;

extern GraphicsEngineInternal *gengine;

static void checkGLErrors()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "GL Error");
    }
}


static void checkEGLErrors()
{
    EGLint error = eglGetError();
    if (error != EGL_SUCCESS)
    {
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "EGL Error");
    }
}

GraphicsEngineInternal::GraphicsEngineInternal() : 
	m_ambientLight(1.0f,1.0f,1.0f) , m_fpsCounterCount(0), cur_font(NULL),
	m_windowWidth(0),
	m_windowHeight(0),
	m_eglDisplay(EGL_NO_DISPLAY),
	m_eglContext(EGL_NO_CONTEXT),
	m_eglSurface(EGL_NO_SURFACE)
{
	m_scene_graph = shared_ptr<SceneGraph>(new SceneGraph());
	
	textures = new TexturesInternal();
	

	ref_count = 0;
	cur_text_x = 20;
	cur_text_y = 20;
	cur_text_paragraph_x = 20;
	
	background_image = NULL;
	tile_image[0] = NULL;
	tile_image[1] = NULL;

	//default_clipper.SetClipper(0,0,479,319);
	//current_clipper = &default_clipper;
//	frame_pointer = (unsigned short*)GXBeginDraw();
	capture = false;
	clearscreen = true;
	CreateContext();

	/*IwGxInit();
	IwGxSetSortMode(IW_GX_SORT_NONE);
	IwGxSetFarZNearZ(50000, 50);
	IwGxSetPerspMul(IwGxGetScreenWidth() / 2);
	IwGxSetScreenOrient(IW_GX_ORIENT_90);
	IwGxSetColClear(0,0,0,255);

	m_defaultMaterial = new CIwMaterial;
	IwGxSetMaterial(m_defaultMaterial);*/
	ClearClipper();

	lzo_init();
}

GraphicsEngineInternal::~GraphicsEngineInternal()
{
	ClearContext();
	//delete m_defaultMaterial;
	//IwGxTerminate();
}

void GraphicsEngineInternal::ClearContext()
{
    eglMakeCurrent(m_eglDisplay, NULL, NULL, NULL);
    eglDestroyContext(m_eglDisplay, m_eglContext);
    eglDestroySurface(m_eglDisplay, m_eglSurface);
    eglTerminate(m_eglDisplay);
}

void GraphicsEngineInternal::CreateContext()
{
    static const EGLint configAttribs[] =
    {
        EGL_RED_SIZE,       8,
        EGL_GREEN_SIZE,     8,
        EGL_BLUE_SIZE,      8,
        EGL_DEPTH_SIZE,     0,
        EGL_ALPHA_SIZE,     EGL_DONT_CARE,
        EGL_STENCIL_SIZE,   0,
        //EGL_SURFACE_TYPE,   EGL_WINDOW_BIT,
        EGL_NONE
    };
    EGLBoolean success;
    EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;

    m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    success = eglInitialize(m_eglDisplay, &majorVersion, &minorVersion);
    if (success != EGL_FALSE)
        success = eglGetConfigs(m_eglDisplay, NULL, 0, &numConfigs);
    if (success != EGL_FALSE)
        success = eglChooseConfig(m_eglDisplay, configAttribs,
                                  &m_eglConfig, 1, &numConfigs);
    if (success != EGL_FALSE)
    {
        m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig,
                                             s3eGLGetNativeWindow(), NULL);
        if (m_eglSurface == EGL_NO_SURFACE)
            success = EGL_FALSE;
    }
    if (success != EGL_FALSE)
    {
        m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, NULL, NULL);
        if (m_eglContext == EGL_NO_CONTEXT)
            success = EGL_FALSE;
    }
    if (success != EGL_FALSE)
        success = eglMakeCurrent(m_eglDisplay, m_eglSurface,
                                 m_eglSurface, m_eglContext);

    if (success == EGL_FALSE)
        checkEGLErrors();
	
	backingWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	backingHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	if(backingWidth > 480 || backingHeight > 480)
		m_hd = true;
	else
		m_hd = false;

	glDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL,0.85f); 

	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);
	glDisable(GL_SCISSOR_TEST);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_DITHER);

	eglSwapInterval(m_eglDisplay,2);
}

int GraphicsEngineInternal::LoadHGF(const char *_name)
{

//	Sleep(1000);
 
	char *name = const_cast<char*>(_name);

	textures->LoadHGF(name);

	return 0;
}
void GraphicsEngineInternal::Release()
{
		ref_count--;
	if(ref_count == 0)
	{
		gengine = NULL;
		delete this;
	}
}

Sprite* GraphicsEngineInternal::CreateSprite1(bool _singleSetMode,int _zInitial)
{
	SpriteInternal *temp;
	temp = new SpriteInternal(_singleSetMode,_zInitial);
	temp->SetPositionAbsolute(0, 0);
	return temp;
}

Background* GraphicsEngineInternal::CreateBackground()
{
	BackgroundInternal *temp = new BackgroundInternal();
	return temp;
}

TileBackground* GraphicsEngineInternal::CreateTileBackground()
{
	TileBackgroundInternal *temp = new TileBackgroundInternal();
	return temp;
}

Font* GraphicsEngineInternal::CreateFont1()
{
	FontInternal *temp = new FontInternal();
	m_fonts.push_back(temp);
	return temp;

	return 0;
}

/*HPTClipper1* GraphicsEngineInternal::CreateClipper1()
{
	HPTClipperInternal1 *temp = new HPTClipperInternal1();
	//GENEW(temp);
	return temp;
}*/


extern s3eSurfaceBlitDirection hooptyFlip;
void GraphicsEngineInternal::BeginFrame()
{

	backingWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
	backingHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
	
	m_widthFactor = 320.0f/backingWidth;
	m_heightFactor = 480.0f/backingHeight;

	bool iphone = false;
	if(s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_IPHONE)
		iphone = true;
	
	if(!iphone)
		glViewport(0, 0, backingWidth, backingHeight);
	else
		glViewport(0, 0, backingHeight, backingWidth);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	//if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT90 || hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT270)
		glOrthof(-160.0f, 160.0f, -240.0f, 240.0f, 0.0f, 10001.0f);
	//else
	//	glOrthof(-240.0f, 240.0f, -160.0f, 160.0f, 0.0f, 100.0f);
	//if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT90)
	//	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	//else if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT180)
	//	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	//else if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT270)
	//	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	//else
	//	glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
	if(!iphone)
	{
		glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
		//glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
		glScalef(480.0f/480.0f, 480.0f/480.0f, 1.0f);
	}
	else
	{
		if(hooptyFlip == S3E_SURFACE_BLIT_DIR_ROT270)
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		else
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(480.0f/480.0f, 320.0f/320.0f, 1.0f);
	}
	//glScalef(320.0f/480.0f, 480.0f/320.0f, 1.0f);
	//glScalef(480.0f/480.0f, 320.0f/320.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	
	if(background_image == NULL)
	{
		if(clearscreen)
			clear_screen();
	}
	else background_image->Render();
	//clear_screen();
	//if(background_image)
	//	background_image->RenderHighQuality(0,0);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);

	m_scene_graph->BeginFrame();
}

void GraphicsEngineInternal::DrawTiles1()
{
	if(m_hd)
	{
		glDisable(GL_ALPHA_TEST);
		//glEnable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
	if(tile_image[0])
		tile_image[0]->Render();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void GraphicsEngineInternal::DrawTiles2()
{	
	if(m_hd)
	{
		glDisable(GL_ALPHA_TEST);
		//glEnable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
	if(tile_image[1])
		tile_image[1]->Render();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void GraphicsEngineInternal::DisableAlphaTest()
{
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void GraphicsEngineInternal::EnableAlphaTest()
{
	if(m_hd)
	{
		glEnable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
}

void GraphicsEngineInternal::EndFrame()
{
	m_scene_graph->Render();
	
	m_fpsTimer.Update();
	m_fpsCounterCount++;
	if(m_fpsCounterCount >= 60)
	{
		m_fps = 60.0f/m_fpsTimer.GetTotalTime();
		m_fpsTimer.Reset();
		m_fpsCounterCount = 0;
	}
	if(m_showFPS)
	{
		if(cur_font)
		{			
			Position(50,50);
			(*this) << "FPS " << m_fps;
		}
		//else if(m_fpsCounterCount == 0)
		//	cout << "FPS " << setprecision(2) << m_fps << endl;
	}
	if(m_showSceneGraphCount)
	{		
		if(cur_font)
		{	
			Position(50,100);
			(*this) << "Scene Graph Batches " << m_scene_graph->NumGroups() << " Scene Graph Count " << m_scene_graph->Size();
		}
		//else if(m_fpsCounterCount == 0)
		//	cout << "Scene Graph Batches " << m_scene_graph->NumGroups() << " Scene Graph Count " << m_scene_graph->Size() << endl;
		
	}
	
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
    checkEGLErrors();
	s3eDeviceYield(0);

}

void GraphicsEngineInternal::AddRef()
{
		ref_count++;

}

void GraphicsEngineInternal::SetBackgroundColor(int red,int green,int blue)
{
	clear_red = red;
	clear_green = green;
	clear_blue = blue;
}

void GraphicsEngineInternal::SetBackgroundImage(Background *arg)
{
		background_image = static_cast<BackgroundInternal*>(arg);

}

void GraphicsEngineInternal::SetClearScreen(bool arg)
{
		clearscreen = arg;

}

/*void GraphicsEngineInternal::SetClipper(HPTClipper1 *clipper)
{
		if(clipper == NULL) current_clipper = &default_clipper;
	else current_clipper = static_cast<HPTClipperInternal1*>(clipper);

}*/

void GraphicsEngineInternal::SetTileBackgroundImage(int number,TileBackground *arg)
{
	if(number > 1) number = 1;
	tile_image[number] = static_cast<TileBackgroundInternal*>(arg);

}

GraphicsEngine& GraphicsEngineInternal::operator<<(Font* arg)
{
	cur_font = (FontInternal*)arg;
	//cur_font->SetPosition(20,20);
	return *this;
}

GraphicsEngine& GraphicsEngineInternal::operator<<(int arg)
{
	char temp[12];
	sprintf(temp,"%d",arg);
	(*this) << temp;
	return *this;
}

GraphicsEngine& GraphicsEngineInternal::operator<<(double arg)
{
	char temp[30];
	sprintf(temp,"%f",arg);
	int pos = 0;
	for(unsigned int count = 0;count < strlen(temp);count++)
	{
		if(temp[count] != '0') pos = count;
	}
	temp[pos+1] = 0;
	(*this) << temp;
	return *this;
}

GraphicsEngine& GraphicsEngineInternal::operator<<(unsigned int arg)
{
	char temp[12];
	sprintf(temp,"%u",arg);
	(*this) << temp;
	return *this;
}

void GraphicsEngineInternal::clear_screen()
{
	
	//clear_red = 255;
    glClearColor(clear_red/255.0f,clear_green/255.0f,clear_blue/255.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
			
}

void GraphicsEngineInternal::RemoveSprite(SpriteInternal *arg)
{

}

int GraphicsEngineInternal::GetTextureEntrys()
{
	return textures->GetNumEntrys();
}

int GraphicsEngineInternal::GetAvailableMemory()
{
	long result = 0;
	return result;
}

void GraphicsEngineInternal::Free()
{
	textures->Free();
	if(tile_image[0] != NULL) tile_image[0]->Free();
	if(tile_image[1] != NULL) tile_image[1]->Free();
	ForEach(m_fonts,mem_fun(&FontInternal::Free));
	ClearContext();
}

void GraphicsEngineInternal::ReLoadGraphics()
{
	CreateContext();
	textures->ReLoad();
	if(tile_image[0] != NULL) tile_image[0]->ReLoad();
	if(tile_image[1] != NULL) tile_image[1]->ReLoad();
	ForEach(m_fonts,mem_fun(&FontInternal::Reload));
}

void GraphicsEngineInternal::ReleaseFont(FontInternal *_font)
{
	m_fonts.erase(remove(m_fonts.begin(),m_fonts.end(),_font),m_fonts.end());
}

void GraphicsEngineInternal::CacheTexture(int _texture)
{
	textures->GetTextureInfo(_texture)->Cached();
}

void GraphicsEngineInternal::SetClipper(int _left,int _top,int _width,int _height)
{
	m_clipping = true;
	m_clipper.Left(_left/m_widthFactor);
	m_clipper.Top(_top/m_heightFactor);
	m_clipper.Width(_width/m_widthFactor);
	m_clipper.Height(_height/m_heightFactor);
	
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(_left, _top, _width, _height);
}

void GraphicsEngineInternal::ClearClipper()
{
	//SetClipper(0,0,600,1024);

	m_clipping = false;
	//glDisable(GL_SCISSOR_TEST);	
}

