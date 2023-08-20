#include "stdafx.h"
#include "PNGManager.h"

HRESULT PNGManager::init(void)
{
    return E_NOTIMPL;
}

void PNGManager::release()
{
    this->deleteAll();
}

PNGRender* PNGManager::addFrameImage(string strKey, wchar_t* fileName, int frameWidth, int frameHeight, int maxFrameX, int maxFrameY)
{
    PNGRender* img = findImage(strKey);
    if (img) return img;
    img = new PNGRender;
    img->LoadImage(fileName, frameWidth, frameHeight, maxFrameX, maxFrameY);
    _mImageList.insert(make_pair(strKey, img));
    return img;
}

void PNGManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    PNGRender* img = findImage(strKey);
    if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void PNGManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
    PNGRender* img = findImage(strKey);
    if (img) img->frameAlphaRender(hdc, destX, destY, currentFrameX, currentFrameY, alpha);
}

PNGRender* PNGManager::findImage(string strKey)
{
    map<string, PNGRender*>::iterator it = _mImageList.find(strKey);
    if (it != _mImageList.end())
    {
        return it->second;
    }

    return NULL;
}

bool PNGManager::deleteAll()
{
    auto iter = _mImageList.begin();
    for (; iter != _mImageList.end();)
    {
        if (iter->second != NULL) 
        {
            iter->second->release();
            SAFE_DELETE(iter->second);
            iter = _mImageList.erase(iter); 
        }
        else
        {
            ++iter;
        }
    }
    _mImageList.clear();
    return true;
}

bool PNGManager::deleteImage(string strKey)
{
    auto key = _mImageList.find(strKey);
    if (key != _mImageList.end())
    {
        key->second->release();
        SAFE_DELETE(key->second);
        _mImageList.erase(key);

        return true;
    }
    return false;
}
