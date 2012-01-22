// This is the main DLL file.

#include "stdafx.h"
#include "HGFGenerator.h"
#include "..\Utility\PowerOf2.h"
//#include "CompressionFilter.h"
#include "Compressor.h"

using namespace HGFGenerator;
using namespace std;
using namespace System::Runtime::InteropServices;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;
using namespace Syntax::Utility;

void Generator::GenerateImage(IHGFFile^ _hgfFile,IProgress^ _progress)
{
	wchar_t* fileName = (wchar_t*) Marshal::StringToHGlobalUni(_hgfFile->FileName).ToPointer();

	Syntax::Utility::BinaryWriter file(fileName);
	file << 'H' << 'G' << 'F'; //header
	file << 1; //version
	file << _hgfFile->Images->Count; //number of images

	for(int i = 0;i < _hgfFile->Images->Count;i++)
	{
		IHPTImage^ image = _hgfFile->Images[i];
		file << image->Width << image->Height;
		file << image->TotalWidth << image->TotalHeight;
		file << image->ColorKeyRed << image->ColorKeyGreen << image->ColorKeyBlue;
		file << image->DefaultFrameRate << image->DefaultAutoAnimate;
		file << image->NumFrameSets;
		for(int set = 0;set < image->NumFrameSets;set++)
			file << image->FramesPerSet[set];
		SaveImage(file,image);
		if((i&7)==0)
			_progress->ProgressUpdate(static_cast<int>((100.0f*i)/_hgfFile->Images->Count));
	}
	_progress->ProgressUpdate(100);
	
    Marshal::FreeHGlobal(IntPtr(fileName));
}

template<int BPP>
void Generator::ConvertSaveImage(Syntax::Utility::BinaryWriter &_file,Bitmap^ _image,unsigned short _colorKey)
{
	_file << (int)0;
	_int64 startPos = _file.Position();
	_file << (int)0;
//	_file.CompressingMode(true);
	BitmapData^ data = _image->LockBits(Rectangle(0,0,_image->Width,_image->Height),
		ImageLockMode::ReadWrite,_image->PixelFormat);

	unsigned char* rawImage = static_cast<unsigned char*>(data->Scan0.ToPointer());
	
	unsigned char pixels = rawImage[0];
	int pixelMask = PowerOf2<BPP>::Value-1;
	int pixelShift = 0;
	for(int y = 0;y < _image->Height;y++)
	{
		for(int x = 0;x < _image->Width;x++)
		{
			unsigned char red,green,blue;
			unsigned short color = _colorKey;
			if((pixels&pixelMask)>>pixelShift < _image->Palette->Entries->Length)
			{
				red = _image->Palette->Entries[(pixels&pixelMask)>>pixelShift].R;
				green = _image->Palette->Entries[(pixels&pixelMask)>>pixelShift].G;
				blue = _image->Palette->Entries[(pixels&pixelMask)>>pixelShift].B;
				color = (red>>3) << 11;
				color |= (green>>3) << 6;
				color |= (blue>>3) << 1;
				if(color != _colorKey)
					color |= 1;
			}
			_file << color;
			pixelShift +=BPP;
			pixelMask = pixelMask<<BPP;
			if(pixelShift >= 8 && !(y >= _image->Height-1 && x >= _image->Width-1))
			{
				pixelShift = 0;
				pixelMask = PowerOf2<BPP>::Value-1;
				rawImage++;
				pixels = rawImage[0];
			}
		}
		rawImage += data->Stride - (_image->Width/(8/BPP));
	}

	//_file.CompressingMode(false);
	
	_int64 endPos = _file.Position();
	_file.Position(startPos);
	_file << static_cast<int>(endPos-startPos-4);
	_file.Position(endPos);
}

template<>
void Generator::ConvertSaveImage<16>(Syntax::Utility::BinaryWriter &_file,Bitmap^ _image,unsigned short _colorKey)
{
	throw gcnew Exception("unsuported pixel format");
}

template<>
void Generator::ConvertSaveImage<24>(Syntax::Utility::BinaryWriter &_file,Bitmap^ _image,unsigned short _colorKey)
{
	_file << (int)0;
	_int64 startPos = _file.Position();
	_file << (int)0;
	//_file.CompressingMode(true);
	BitmapData^ data = _image->LockBits(Rectangle(0,0,_image->Width,_image->Height),
		ImageLockMode::ReadWrite,_image->PixelFormat);

	unsigned char* rawImage = static_cast<unsigned char*>(data->Scan0.ToPointer());
	
	for(int y = 0;y < _image->Height;y++)
	{
		for(int x = 0;x < _image->Width;x++)
		{
			unsigned char red,green,blue;
			red = rawImage[2];
			green = rawImage[1];
			blue = rawImage[0];
			unsigned short color = (red>>3) << 11;
			color |= (green>>3) << 6;
			color |= (blue>>3) << 1;
			if(color != _colorKey)
				color |= 1;
			_file << color;
			rawImage += 3;
		}
		rawImage += data->Stride - (_image->Width*3);
	}

//	_file.CompressingMode(false);
	
	_int64 endPos = _file.Position();
	_file.Position(startPos);
	_file << static_cast<int>(endPos-startPos-4);
	_file.Position(endPos);
}

template<>
void Generator::ConvertSaveImage<32>(Syntax::Utility::BinaryWriter &_file,Bitmap^ _image,unsigned short _colorKey)
{
	_file << (int)1;
	_int64 startPos = _file.Position();
	_file << (int)0;
	//_file.CompressingMode(true);
	BitmapData^ data = _image->LockBits(Rectangle(0,0,_image->Width,_image->Height),
		ImageLockMode::ReadWrite,_image->PixelFormat);

	unsigned char* rawImage = static_cast<unsigned char*>(data->Scan0.ToPointer());
	
	for(int y = 0;y < _image->Height;y++)
	{
		for(int x = 0;x < _image->Width;x++)
		{
			unsigned char red,green,blue,alpha;
			red = rawImage[2];
			green = rawImage[1];
			blue = rawImage[0];
			alpha = rawImage[3];
			unsigned short color = (red>>4) << 12;
			color |= (green>>4) << 8;
			color |= (blue>>4) << 4;
			color |= (alpha>>4);
			_file << color;
			rawImage += 4;
		}
		rawImage += data->Stride - (_image->Width*4);
	}

	//_file.CompressingMode(false);
	
	_int64 endPos = _file.Position();
	_file.Position(startPos);
	_file << static_cast<int>(endPos-startPos-4);
	_file.Position(endPos);
}

void Generator::ConvertSaveImageHighQuality24(Syntax::Utility::BinaryWriter &_file,Bitmap^ _image)
{
	_file << (int)3;
	_int64 startPos = _file.Position();
	_file << (int)0;
	//_file.CompressingMode(true);
	BitmapData^ data = _image->LockBits(Rectangle(0,0,_image->Width,_image->Height),
		ImageLockMode::ReadWrite,_image->PixelFormat);

	unsigned char* origImage = static_cast<unsigned char*>(data->Scan0.ToPointer());
	
	unsigned int origSize = _image->Width*_image->Height*3;
	unsigned char* rawImage = new unsigned char[origSize];
	//unsigned char* rawImage2 = new unsigned char[origSize];
	unsigned char* imagePtr = rawImage;	

	for(int y = 0;y < _image->Height;y++)
	{
		for(int x = 0;x < _image->Width;x++)
		{
			imagePtr[0] = origImage[2];
			imagePtr[1] = origImage[1];
			imagePtr[2] = origImage[0];
			
			origImage += 3;
			imagePtr += 3;
		}
		origImage += data->Stride - (_image->Width*3);
	}

	//unsigned char* imagePtr;	
	/*for(int y = 1;y < _image->Height;y++)
	{
		for(int x = 1;x < _image->Width;x++)
		{
			for(int i = 0;i < 3;++i)
			{
				int w = rawImage[3*y*_image->Width+3*(x-1)+i];
				int n = rawImage[3*(y-1)*_image->Width+3*x+i];
				int nw = rawImage[3*(y-1)*_image->Width+3*(x-1)+i];
				int pred;
				if(nw >= std::max(n, w))
					pred = std::min(n, w);
				else if(nw <= std::min(n, w))
					pred = std::max(n, w);
				else
					pred = n + w - nw;
				rawImage2[3*y*_image->Width+3*x+i] = rawImage[3*y*_image->Width+3*x+i] - pred;
			}
		}
	}*/

	Compressor compressor(rawImage,origSize,_file);

	/*unsigned long compressedSize = compressBound(origSize);
	unsigned char* compressed = new unsigned char[compressedSize];
	compress2(compressed,&compressedSize,rawImage,origSize,9);
	
	_file.Write((char*)compressed,compressedSize);
	*/
	/*for(int y = 0;y < _image->Height;y++)
	{
		for(int x = 0;x < _image->Width;x++)
		{
			unsigned char red,green,blue;
			red = rawImage[2];
			green = rawImage[1];
			blue = rawImage[0];
			
			_file << red << green << blue;
			rawImage += 3;
		}
		rawImage += data->Stride - (_image->Width*3);
	}*/
	//_file.CompressingMode(false);
	
	_int64 endPos = _file.Position();
	_file.Position(startPos);
	_file << static_cast<int>(endPos-startPos-4);
	_file.Position(endPos);

	delete[] rawImage;
	//delete[] rawImage2;
	//delete[] compressed;
}

void Generator::ConvertSaveImageHighQuality(Syntax::Utility::BinaryWriter &_file,Bitmap^ _image)
{
	_file << (int)2;
	_int64 startPos = _file.Position();
	_file << (int)0;
	BitmapData^ data = _image->LockBits(Rectangle(0,0,_image->Width,_image->Height),
		ImageLockMode::ReadWrite,_image->PixelFormat);

	unsigned char* origImage = static_cast<unsigned char*>(data->Scan0.ToPointer());
	
	unsigned int origSize = _image->Width*_image->Height*4;
	unsigned char* rawImage = new unsigned char[origSize];
	//unsigned char* rawImage2 = new unsigned char[origSize];

	unsigned char* imagePtr = rawImage;
	for(int y = 0;y < _image->Height;y++)
	{
		for(int x = 0;x < _image->Width;x++)
		{
			imagePtr[0] = origImage[2];
			imagePtr[1] = origImage[1];
			imagePtr[2] = origImage[0];
			imagePtr[3] = origImage[3];			
			imagePtr += 4;			
			origImage += 4;
		}
		origImage += data->Stride - (_image->Width*4);
	}

	/*for(int y = 1;y < _image->Height;y++)
	{
		for(int x = 1;x < _image->Width;x++)
		{
			for(int i = 0;i < 4;++i)
			{
				int w = rawImage[4*y*_image->Width+4*(x-1)+i];
				int n = rawImage[4*(y-1)*_image->Width+4*x+i];
				int nw = rawImage[4*(y-1)*_image->Width+4*(x-1)+i];
				int pred;
				if(nw >= std::max(n, w))
					pred = std::min(n, w);
				else if(nw <= std::min(n, w))
					pred = std::max(n, w);
				else
					pred = n + w - nw;
				rawImage2[4*y*_image->Width+4*x+i] = rawImage[4*y*_image->Width+4*x+i] - pred;
			}
		}
	}*/

	Compressor compressor(rawImage,origSize,_file);

	/*unsigned long compressedSize = compressBound(origSize);
	unsigned char* compressed = new unsigned char[compressedSize];
	compress2(compressed,&compressedSize,rawImage,origSize,9);
	
	_file.Write((char*)compressed,compressedSize);
	*/
	_int64 endPos = _file.Position();
	_file.Position(startPos);
	_file << static_cast<int>(endPos-startPos-4);
	_file.Position(endPos);

	delete[] rawImage;
	//delete[] rawImage2;
	//delete[] compressed;
}

void Generator::SaveImage(Syntax::Utility::BinaryWriter &_file,IHPTImage^ _image)
{
	Bitmap^ image;
    
	FileStream^ fs = gcnew FileStream(_image->FileName, FileMode::Open);
	image = static_cast<Bitmap^>(Bitmap::FromStream(fs));
    fs->Close();
	unsigned short colorKey = (255>>3) << 11;
	colorKey |= (0>>3) << 6;
	colorKey |= (255>>3) << 1;
	if(image->PixelFormat == PixelFormat::Format1bppIndexed)
		ConvertSaveImage<1>(_file,image,colorKey);
	else if(image->PixelFormat == PixelFormat::Format4bppIndexed)
		ConvertSaveImage<4>(_file,image,colorKey);
	else if(image->PixelFormat == PixelFormat::Format8bppIndexed)
		ConvertSaveImage<8>(_file,image,colorKey);
	else if(image->PixelFormat == PixelFormat::Format24bppRgb/* && _image->HighQuality*/)
		ConvertSaveImageHighQuality24(_file,image);
	//else if(image->PixelFormat == PixelFormat::Format24bppRgb)
	//	ConvertSaveImage<24>(_file,image,colorKey);
	else if(image->PixelFormat == PixelFormat::Format32bppArgb/* && _image->HighQuality*/)
		ConvertSaveImageHighQuality(_file,image);
	//else if(image->PixelFormat == PixelFormat::Format32bppArgb)
	//	ConvertSaveImage<32>(_file,image,colorKey);
	else
		throw gcnew Exception("unsuported pixel format");
}