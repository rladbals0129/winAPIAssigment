#pragma once
#include "GameNode.h"
#include <gdiPlus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;



struct FrameImageInfo
{
    Image* image;   //�̹��� ��ü�� ���� ������
    int frameWidth; // �������� �ʺ�
    int frameHeight;//�������� ����
    int maxFrameX; //���ι��� �ִ������� ����
    int maxFrameY; //���ι��� �ִ������� ����
};

class PNGRender : public GameNode
{
private:
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Image* image;
    FrameImageInfo* frameImageInfo;
    REAL _angle;
public:
    HRESULT init(void);
    void release(void);
    void LoadImage(wchar_t* filePath);
    void LoadImage(wchar_t* filePath, int Width, int Height, int maxFrameX, int maxFrameY);

    void RotateRender(HDC hdc , int x, int y, int width, int height, bool render);
    void rotateImage(REAL delta_angle, bool isColliding);


    void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
    void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);


    inline Image* getImage(void) { return image; }

    inline int getFrameWidth(void) { return frameImageInfo->frameWidth; }

    inline int getFrameHeight(void) { return frameImageInfo->frameHeight; }


    inline int getMaxFrameX(void) { return frameImageInfo->maxFrameX; }

    inline int getMaxFrameY(void) { return frameImageInfo->maxFrameY; }

    inline void deleteImage(Image** _image) {
        if (*_image == nullptr) return; 
        delete* _image;
        *_image = nullptr; 
    }
};

