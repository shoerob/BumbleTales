#ifndef HPT_GRAPHICS_ENGINE_INTERNAL
#define HPT_GRAPHICS_ENGINE_INTERNAL

#define FORMAT555 1
#define FORMAT565 2
#define FORMAT888 4

#include <tr1/memory>

#include "Timer.h"
#include "Rectangle.h"

#include "Graphics.h"
#include "TexturesInternal.h"
#include "FontInternal.h"
//#include "HPTClipperInternal1.h"

#include "BackgroundInternal.h"
#include "TileBackgroundInternal.h"

//#include "IwGx.h"

#include "GLES/gl.h"
#include "GLES/egl.h"
//#import <GLES/EAGL.h>
//#import <OpenGLES/ES1/gl.h>
//#import <OpenGLES/ES1/glext.h>

//#include "HPTList.h"
//#include<list>
//using namespace std;

#define HIGH_QUALITY 1
#define MED_QUALITY 2
#define LOW_QUALITY 3

namespace CR
{
	namespace Graphics
	{		
		class SceneGraph;
		
		class GraphicsEngineInternal : public GraphicsEngine  
		{
		public:
			int GetTextureEntrys();
			void RemoveSprite(SpriteInternal* arg);
			void clear_screen();
			virtual int GetAvailableMemory();
			inline TextureStruct* GetTexture(int number)
			{
				return textures->GetTextureInfo(number);
			};
			void AddRef();
			GraphicsEngineInternal();
			virtual ~GraphicsEngineInternal();
			virtual int LoadHGF(const char *name);
			virtual void Release();
			//virtual HPTClipper1* CreateClipper1();
			virtual Sprite* CreateSprite1(bool _singleSetMode = false,int _zInitial = 0);
			virtual Font* CreateFont1();
			virtual Background* CreateBackground();
			virtual TileBackground* CreateTileBackground();
			virtual void BeginFrame();
			virtual void EndFrame();
			virtual void SetBackgroundColor(int red,int green,int blue);
			virtual void SetBackgroundImage(Background *arg);
			virtual BackgroundInternal* GetBackgroundImage() const { return background_image;}
			virtual void SetTileBackgroundImage(int number,TileBackground *arg);
			//virtual void SetClipper(HPTClipper1 *clipper);
			virtual void SetClearScreen(bool arg);
		/*	inline int GetScreenFormat()
			{
				return screen_format;
			};*/
			/*inline HPTClipperInternal1* GetClipper()
			{
				return current_clipper;
			};*/
			virtual GraphicsEngine& operator<<(Font* arg);
			inline virtual GraphicsEngine& operator<<(char* arg)
			{
				cur_font->Render(arg,cur_text_x,cur_text_y,cur_text_paragraph_x);	
				return *this;
			};
			virtual GraphicsEngine& operator<<(int arg);
			virtual GraphicsEngine& operator<<(double arg);
			virtual GraphicsEngine& operator<<(unsigned int arg);
			inline virtual GraphicsEngine& Position(int x,int y)
			{
				cur_text_x = x;
				cur_text_y = y;
				cur_text_paragraph_x = x;
				return *this;
			};
			virtual void EnableCapture(bool arg) {capture = arg; if(arg == true) next_capture = 0;};
		//	virtual void SetScreenSize(int arg) {screen_size = arg;};
			/*TwGfxType* GetGFXHandle()
			{
				return twgfx_handle;
			};*/
			virtual void ReLoadGraphics();
			virtual void Free();
			
			/* The pixel dimensions of the backbuffer */
			GLint backingWidth;
			GLint backingHeight;
			
			//EAGLContext *context;
			
			/* OpenGL names for the renderbuffer and framebuffers used to render to this view */
			GLuint viewRenderbuffer, viewFramebuffer;
			
			virtual CR::Math::Color96 AmbientLight() const {return m_ambientLight;}
			virtual void AmbientLight(const CR::Math::Color96 &_ambientLight) {m_ambientLight = _ambientLight;}
			virtual void SetClipper(int _left,int _top,int _width,int _height);
			virtual void ClearClipper();
			virtual std::tr1::shared_ptr<SceneGraph> GetSceneGraph() { return  m_scene_graph;}
			virtual void ShowFPS(bool _show) {m_showFPS = _show;}
			virtual void ShowSceneGraphCount(bool _show) {m_showSceneGraphCount = _show;}
			bool IsClipping() {return m_clipping;}
			CR::Math::RectangleI& GetClip() {return m_clipper;} 
			
			void ReleaseFont(FontInternal *_font);
			virtual void DisableAlphaTest();
			virtual void EnableAlphaTest();
			virtual void CacheTexture(int _texture);
			virtual void DrawTiles1();
			virtual void DrawTiles2();	
			bool IsHD() const {return m_hd;}
			virtual void DumpUsage() {textures->DumpUsage();}
	
		private:

			void ClearContext();
			void CreateContext();
	
			bool clearscreen;
			int quality;
			bool capture;
			int next_capture;
			bool landscape;
			int cur_text_paragraph_x;
			int cur_text_y;
			int cur_text_x;
			int clear_blue;
			int clear_green;
			int clear_red;
			int screen_format;
			//int screen_xpitch;
			//int screen_ypitch;
			//int screen_height;
			//int screen_width;
			int ref_count;
		//	unsigned char *back_buffer;
			//TwGfxSurfaceType* back_buffer;
			//TwGfxSurfaceType* scratch_buffer;
			TexturesInternal* textures;
			FontInternal *cur_font;
			BackgroundInternal *background_image;
			TileBackgroundInternal *tile_image[2];
			//HPTClipperInternal1 default_clipper;
			//HPTClipperInternal1 *current_clipper;
			//list<SpriteInternal*> sprite_list;
			std::tr1::shared_ptr<SceneGraph> m_scene_graph;
		//	HDC memdc;
		//	HDC hdc;
		//	HBITMAP back_buffer_bitmap;
		//	HBITMAP scale_buffer_bitmap;
			unsigned short *frame_pointer;
			int screen_size;
			//TwGfxType* twgfx_handle;

			CR::Math::Color96 m_ambientLight;
			CR::Utility::Timer m_fpsTimer;
			int m_fpsCounterCount;
			float m_fps;
			bool m_showFPS;
			bool m_showSceneGraphCount;
			CR::Math::RectangleI m_clipper;
			bool m_clipping;


			int m_windowWidth;
			int m_windowHeight;
			EGLDisplay m_eglDisplay;
			EGLConfig m_eglConfig;
			EGLContext m_eglContext;
			EGLSurface m_eglSurface;
			std::vector<FontInternal*> m_fonts;
			bool m_hd;
			float m_widthFactor;
			float m_heightFactor;
	
		protected:
		};
	}
}
#endif