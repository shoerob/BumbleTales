#ifndef HPT_TEXTURES_INTERNAL_H
#define HPT_TEXTURES_INTERNAL_H

#include "texturestruct.h"

namespace CR
{
	namespace Graphics
	{		
		class TexturesInternal  
		{
		public:
			int GetNumEntrys();
			//void ReadBitmap(int entry,unsigned char *&data);
			void LoadHGF(char *name);
			TexturesInternal();
			virtual ~TexturesInternal();
			inline TextureStruct *GetTextureInfo(int entry)
			{
				if(entrys == 0) return 0;
				else
				{
					return &(entrys[entry]);
				}
			};
			void ReLoad();
			void DumpUsage();
			void Free();
		private:
			int num_entrys;
			TextureStruct *entrys;
		};
	}
}

#endif