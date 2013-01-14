//
//  main.cpp
//  CR Image Doubler
//
//  Created by Eric Duhon on 12/30/12.
//  Copyright (c) 2012 Eric Duhon. All rights reserved.
//

#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <FreeImage.h>

using namespace std;

void WalkFolder(const char* _src, const char* _dest)
{
    DIR *dp;
    struct dirent *ep;
    dp = opendir (_src);
    
    if (dp != NULL)
    {
        vector<pair<string,string>> subFolders;
        
        while ((ep = readdir (dp)))
        {
            string srcfolder = _src;
            srcfolder += "/";
            srcfolder += ep->d_name;
            string dstfolder = _dest;
            dstfolder += "/";
            dstfolder += ep->d_name;
            if(ep->d_type == DT_DIR)
            {
                if(strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0)
                {
                    subFolders.push_back(make_pair(srcfolder,dstfolder));
                    mkdir(dstfolder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                }
            }
            else if (ep->d_type == DT_REG && strcasecmp(srcfolder.c_str() + srcfolder.length() - 4, ".png") == 0)
            {                
                cout << "convert " << srcfolder << " to " << dstfolder << endl;
                FIBITMAP *bitmap = FreeImage_Load(FIF_PNG, srcfolder.c_str(), PNG_DEFAULT);
                if (!bitmap)
                {
                    cout << "failed to load png " << srcfolder << endl;
                    continue;
                }
                int newWidth = FreeImage_GetWidth(bitmap) * 2;
                int newHeight = FreeImage_GetHeight(bitmap) * 2;
                
                FIBITMAP* newBitmap = FreeImage_Rescale(bitmap, newWidth, newHeight, FILTER_LANCZOS3);
                
                FreeImage_Save(FIF_PNG, newBitmap, dstfolder.c_str(), PNG_Z_BEST_COMPRESSION);
                
                FreeImage_Unload(bitmap);
                FreeImage_Unload(newBitmap);
            }
        }
        
        closedir (dp);
        for(auto& folderName : subFolders)
        {
            WalkFolder(folderName.first.c_str(), folderName.second.c_str());
        }
    }
    else
        perror ("Couldn't open the directory");
    
}

int main(int argc, const char * argv[])
{
    if(argc < 3)
    {
        cout << "you must provide a source and destination folder";
        return 1;
    }
    cout << "Converting images from folder " << argv[1] << " to folder " << argv[2] << endl << endl;
    
    FreeImage_Initialise();
    FreeImage_SetOutputMessage([](FREE_IMAGE_FORMAT fif, const char *message){
        cout << "free image error: " << message << endl;
        exit(0);
    });
    
    WalkFolder(argv[1], argv[2]);
    
    FreeImage_DeInitialise();
    
    return 0;
}

