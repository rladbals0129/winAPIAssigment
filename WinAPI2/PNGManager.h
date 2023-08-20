#pragma once
#include "PNGRender.h"

class PNGManager //: public GameNode
{
private:
    typedef map<string, PNGRender*> mImageList;
    typedef map<string, PNGRender*>::iterator mapImageIter;
private:
    mImageList _mImageList;
public:
    HRESULT init(void);
    void release(void);

    PNGRender* addFrameImage(string strKey, wchar_t* fileName, int frameWidth, int frameHeight, int maxFrameX, int maxFrameY);
    void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
    void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
    PNGRender* findImage(string strKey);

    bool deleteAll();
    bool deleteImage(string strKey);



};

