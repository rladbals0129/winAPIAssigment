#include "stdafx.h"
#include "PNGRender.h"

HRESULT PNGRender::init(void)
{
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    _angle = 0;

    return S_OK;
}

void PNGRender::release(void)
{
    if (image) {
        delete image;
        image = nullptr;
    }
    GdiplusShutdown(gdiplusToken);
    ReleaseMemDC();
}


void PNGRender::LoadImage(wchar_t* filePath)
{
    if (image) {
        delete image;
        image = nullptr;
    }
    image = new Image(filePath);
  
}
//
//void PNGRender::LoadImage(wchar_t* filePath, int Width, int Height, int maxFrameX, int maxFrameY)
//{
//    if (image) {
//        delete image;
//        image = nullptr;
//    }
//    image = new Image(filePath);
//   
//    if (!frameImageInfo) {
//        frameImageInfo = new FrameImageInfo;
//    }
//
//
//
//    frameImageInfo->image = image;
//    frameImageInfo->frameWidth = Width / (maxFrameX);
//    frameImageInfo->frameHeight = Height / (maxFrameY);
//    frameImageInfo->maxFrameX = maxFrameX;
//    frameImageInfo->maxFrameY = maxFrameY;
//  
//   
//}





//void PNGRender::LoadImage(wchar_t* filePath, int clipX, int clipY, int clipWidth, int clipHeight)
//{
//    image = new Image(filePath);
//
//    frameImageInfo = new FrameImageInfo;
//    frameImageInfo->image = image;
//    frameImageInfo->frameWidth = 0;
//    frameImageInfo->frameHeight = 0;
//    frameImageInfo->maxFrameX = 0;
//    frameImageInfo->maxFrameY = 0;
//    frameImageInfo->clipX = clipX;
//    frameImageInfo->clipY = clipY;
//    frameImageInfo->clipWidth = clipWidth;
//    frameImageInfo->clipHeight = clipHeight;
//}

void PNGRender::LoadImage(wchar_t* filePath, int Width, int Height, int maxFrameX, int maxFrameY, int clipX, int clipY, int clipWidth, int clipHeight)
{
    image = new Image(filePath);

    frameImageInfo = new FrameImageInfo;
    
    frameImageInfo->image = image;
    frameImageInfo->frameWidth = Width / maxFrameX;
    frameImageInfo->frameHeight = Height / maxFrameY;
    frameImageInfo->maxFrameX = maxFrameX - 1;
    frameImageInfo->maxFrameY = maxFrameY - 1;
    frameImageInfo->clipX = clipX;
    frameImageInfo->clipY = clipY;
    frameImageInfo->clipWidth = Width;
    frameImageInfo->clipHeight = Height;
    HDC windowDC = GetDC(_hWnd); 
    CreateMemDC(windowDC, frameImageInfo->clipWidth, frameImageInfo->clipHeight);
    ReleaseDC(_hWnd, windowDC);
}

void PNGRender::CreateMemDC(HDC hdc, int width, int height)
{
    memDC = CreateCompatibleDC(hdc);
    hbmMem = CreateCompatibleBitmap(hdc, width, height);
    hbmOld = (HBITMAP)SelectObject(memDC, hbmMem);
}

void PNGRender::ReleaseMemDC()
{
    SelectObject(memDC, hbmOld);
    DeleteObject(hbmMem);
    DeleteDC(memDC);
}

void PNGRender::RotateRender(HDC hdc ,int x, int y, int width, int height, bool render)
{
    Gdiplus::Graphics graphics(hdc);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);


    int centerX = image->GetWidth() / 2;
    int centerY = image->GetHeight() / 2;
    graphics.TranslateTransform(x, y);
    graphics.RotateTransform(_angle);
    graphics.TranslateTransform(-x, -y);
    if (render)
    {
        graphics.DrawImage(image, x - centerX, y - centerY, width, height);
    }
}

void PNGRender::rotateImage(REAL delta_angle, bool isColliding)
{
    if (!isColliding)
    {
        _angle += delta_angle;
        if (_angle >= 360)
            _angle -= 360;
    }
}

void PNGRender::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
    _usePngDc = true;
    HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    RECT rc;
    SetRect(&rc, 0, 0, frameImageInfo->frameWidth, frameImageInfo->frameHeight);
    FillRect(memDC, &rc, hBrush);
    DeleteObject(hBrush);
  
    Graphics graphics(memDC);

  
    int srcX = currentFrameX * frameImageInfo->frameWidth;
    int srcY = currentFrameY * frameImageInfo->frameHeight;

    
    if (frameImageInfo->clipWidth > 0 && frameImageInfo->clipHeight > 0)
    {
        Rect clipRect(frameImageInfo->clipX, frameImageInfo->clipY, frameImageInfo->clipWidth, frameImageInfo->clipHeight);
        graphics.SetClip(clipRect); 
    }

  
    graphics.DrawImage(frameImageInfo->image,
        Rect(0, 0, frameImageInfo->frameWidth, frameImageInfo->frameHeight),
        srcX, srcY, frameImageInfo->frameWidth, frameImageInfo->frameHeight,
        UnitPixel);

    if (frameImageInfo->clipWidth > 0 && frameImageInfo->clipHeight > 0)
    {
        graphics.ResetClip();
    }

  
   
    blendFunc.BlendOp = AC_SRC_OVER;
    blendFunc.BlendFlags = 0;
    blendFunc.SourceConstantAlpha = 255;
    blendFunc.AlphaFormat = AC_SRC_ALPHA;

    AlphaBlend(hdc, destX, destY, frameImageInfo->frameWidth, frameImageInfo->frameHeight, memDC, 0, 0, frameImageInfo->frameWidth, frameImageInfo->frameHeight, blendFunc);
    
    
    
}

void PNGRender::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
    if (image) {
        currentFrameX = currentFrameX % (frameImageInfo->maxFrameX + 1);
        currentFrameY = currentFrameY % (frameImageInfo->maxFrameY + 1);

        Gdiplus::Graphics g(hdc);

        Gdiplus::ColorMatrix colorMatrix = { 1.0, 0.0, 0.0, 0.0, 0.0,
                                  0.0, 1.0, 0.0, 0.0, 0.0,
                                  0.0, 0.0, 1.0, 0.0, 0.0,
                                  0.0, 0.0, 0.0, static_cast<float>(alpha) / 255, 0.0,
                                  0.0, 0.0, 0.0, 0.0, 1.0 };

        ImageAttributes attributes;
        attributes.SetColorMatrix(&colorMatrix);

        Rect destRect(destX, destY, frameImageInfo->frameWidth, frameImageInfo->frameHeight);
        int sourceX = currentFrameX * frameImageInfo->frameWidth;
        int sourceY = currentFrameY * frameImageInfo->frameHeight;

        g.DrawImage(image, destRect,
            sourceX, sourceY, frameImageInfo->frameWidth, frameImageInfo->frameHeight,
            UnitPixel, &attributes);
    }
}
