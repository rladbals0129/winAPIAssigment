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

}

void PNGRender::LoadImage(wchar_t* filePath)
{
    if (image) {
        delete image;
        image = nullptr;
    }
    image = new Image(filePath);
}

void PNGRender::LoadImage(wchar_t* filePath, int Width, int Height, int maxFrameX, int maxFrameY)
{
    if (image) {
        delete image;
        image = nullptr;
    }
    image = new Image(filePath);

    if (!frameImageInfo) {
        frameImageInfo = new FrameImageInfo;
    }
  //  cout << "dd" << endl;
    frameImageInfo->image = image;
    frameImageInfo->frameWidth = Width / (maxFrameX);
    frameImageInfo->frameHeight = Height / (maxFrameY);
    frameImageInfo->maxFrameX = maxFrameX;
    frameImageInfo->maxFrameY = maxFrameY;
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
    if (image) 
    {
        cout << "들어왔따" << endl;
        currentFrameX = currentFrameX % (frameImageInfo->maxFrameX + 1);
        currentFrameY = currentFrameY % (frameImageInfo->maxFrameY + 1);

        Graphics g(hdc);
        Rect destRect(destX, destY, frameImageInfo->frameWidth, frameImageInfo->frameHeight);
        int sourceX = currentFrameX * frameImageInfo->frameWidth;
        int sourceY = currentFrameY * frameImageInfo->frameHeight;

        g.DrawImage(image, destRect,
            sourceX, sourceY, frameImageInfo->frameWidth, frameImageInfo->frameHeight,
            UnitPixel);
    }
}

void PNGRender::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
    if (image) {
        currentFrameX = currentFrameX % (frameImageInfo->maxFrameX + 1);
        currentFrameY = currentFrameY % (frameImageInfo->maxFrameY + 1);

        Graphics g(hdc);

        ColorMatrix colorMatrix = { 1.0, 0.0, 0.0, 0.0, 0.0,
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
