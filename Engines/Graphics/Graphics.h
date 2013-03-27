#pragma once

#define HFLIP 0x01
#define VFLIP 0x02
#define HPTOPAQUE 0x04

#define NORMAL_SIZE 0x01
#define DOUBLE_SIZE 0x02
#ifndef NULL 
#define NULL 0L
#endif
#include "Color.h"

namespace CR
{
	namespace Graphics
	{		
		class Background
		{
		public:
			Background() {};
			virtual ~Background() {};
			virtual void SetImage(int pallette_entry) = 0;
			virtual void Release() = 0;
			virtual CR::Math::Color32 Color() const = 0;
			virtual void Color(const CR::Math::Color32 &_color) = 0;
			virtual bool Lighting() const = 0;
			virtual void Lighting(bool _enable) = 0;
		};

		class TileBackground
		{
		public:
			TileBackground() {};
			virtual ~TileBackground() {};
			virtual void LoadTileSet(char *name) = 0;
			virtual void Release() = 0;
			virtual void SetPositionAbsolute(float x,float y) = 0;
			virtual void SetPositionRelative(int x,int y) = 0;
			virtual CR::Math::Color32 Color() const = 0;
			virtual void Color(const CR::Math::Color32 &_color) = 0;
			virtual bool Lighting() const = 0;
			virtual void Lighting(bool _enable) = 0;
			
		};


		class Sprite {
		public:
			Sprite() {};
			virtual ~Sprite() {};
			virtual void StepFrame() = 0;
			virtual void SetFrame(int frame) = 0;
			virtual void SetImage(int pallette_entry,bool _resetAnimation = true) = 0;
			virtual int GetImage() const = 0;
			virtual void SetFrameRate(float rate) = 0;
			virtual void UpdateFrameRate(float rate) = 0;
			virtual void SetAutoAnimate(bool arg) = 0;
			//virtual void Render() = 0;
			//virtual void RenderBatch(int _num) = 0;
			//virtual void RenderHFlip() = 0;
			//virtual void RenderVFlip() = 0;
			//virtual void RenderHVFlip() = 0;
			virtual void SetPositionAbsolute(float x,float y) = 0;
			virtual void SetPositionRelative(int x,int y) = 0;
			virtual void Release() = 0;
			virtual void SetFrameSet(int set) = 0;
			virtual void NextFrameSet() = 0;
			virtual bool IsAnimating() = 0;
			virtual void AutoStopAnimate() = 0;
			virtual int GetFrameSet() = 0;
			virtual int GetFrame() = 0;
			//virtual int GetFrameWidth() = 0;
			//virtual int GetFrameHeight() = 0;
			virtual void EnableFrameSkip(bool arg) = 0;
			virtual void SetReverseAnimation(bool arg) = 0;
			virtual void PauseAnimation(bool arg) = 0;
			virtual void SetDesignSize(int _width,int _height) = 0;	
			virtual int DesignWidth() const = 0;
			virtual int DesignHeight() const = 0;
			virtual CR::Math::Color32 Color() const = 0;
			virtual void Color(const CR::Math::Color32 &_color) = 0;
			virtual bool Lighting() const = 0;
			virtual void Lighting(bool _enable) = 0;	
			//virtual void Visible(bool _visible) = 0;
			//virtual bool Visible() const = 0;
			virtual void Render() = 0;

			//virtual void SetFlip(bool _hflip,bool vflip) = 0;
		};

		class Font {
		public:
			Font() {};
			virtual ~Font() {};
			virtual void LoadHFFFont(char *fontname) = 0;
			virtual void Release() = 0;
			virtual CR::Math::Color32 Color() const = 0;
			virtual void Color(const CR::Math::Color32 &_color) = 0;
		};

		class GraphicsEngine {
		public:
			GraphicsEngine() {};
			virtual ~GraphicsEngine() {};
			virtual int LoadHGF(const char *name) = 0;
			virtual int GetAvailableMemory() = 0;
			virtual void Release() = 0;
			//virtual HPTClipper1* CreateClipper1() = 0;
			virtual Sprite* CreateSprite1(bool _singleSetMode = false,int _zInitial = 0) = 0;
			virtual Font* CreateFont1() = 0;
			virtual Background* CreateBackground() = 0;
			virtual TileBackground* CreateTileBackground() = 0;
			virtual void BeginFrame() = 0;
			virtual void EndFrame() = 0;
			virtual void SetBackgroundColor(int red,int green,int blue) = 0;
			virtual void SetBackgroundImage(Background *arg) = 0;
			virtual void SetTileBackgroundImage(int number,TileBackground *arg) = 0;
			//virtual void SetClipper(HPTClipper1 *clipper) = 0;
			virtual void SetClearScreen(bool arg) = 0;
			virtual GraphicsEngine& operator<<(Font* arg) = 0;
			virtual GraphicsEngine& operator<<(char *arg) = 0;
			virtual GraphicsEngine& operator<<(int arg) = 0;
			virtual GraphicsEngine& operator<<(unsigned int arg) = 0;
			virtual GraphicsEngine& operator<<(double arg) = 0;

			virtual GraphicsEngine& Position(int x,int y) = 0;
			virtual void EnableCapture(bool arg) = 0;
			virtual void ReLoadGraphics() = 0;
			virtual void Free() = 0;
			virtual void EnableAlphaTest() = 0;	
			virtual void DisableAlphaTest() = 0;
			virtual void CacheTexture(int _texture) = 0;
			virtual void DrawTiles1() = 0;
			virtual void DrawTiles2() = 0;
			
			virtual CR::Math::Color96 AmbientLight() const = 0;
			virtual void AmbientLight(const CR::Math::Color96 &_ambientLight) = 0;
			virtual void SetClipper(int _left,int _top,int _width,int _height) = 0;
			virtual void ClearClipper() = 0;
			virtual void ShowFPS(bool _show) = 0;
			virtual void ShowSceneGraphCount(bool _show) = 0;

			virtual void DumpUsage() = 0;
		};

		GraphicsEngine* GetGraphicsEngine();
	}
}
