#include "Stdafx.h"
#include "C3DVector.h"
#include "C3DMatrix.h"




HRESULT C3DVector::init()
{
    GameNode::init(true);
    return S_OK;
}

void C3DVector::release()
{
}

void C3DVector::update()
{
    GameNode::update();
    if (KEYMANAGER->isStayKeyDown(VK_UP))
    {
        _xAngle += ROTATION_SPEED;
    }
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        _xAngle -= ROTATION_SPEED;
    }
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _yAngle -= ROTATION_SPEED;
    }
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _yAngle += ROTATION_SPEED;
    }
}

void C3DVector::render()
{
    GameNode::render();


    PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
    const int gridSize = 300;

    for (int i = 0; i < 300; i += gridSize) {
        for (int j = 0; j < 300; j += gridSize) {
            for (int k = 0; k < 300; k += 30) {
                Point3D vertices[] = {
                    Rotate3D(Point3D(i + (WINSIZE_X / 2), j + (WINSIZE_Y / 2), k)),
                    Rotate3D(Point3D(i + (WINSIZE_X / 2) + gridSize, j + (WINSIZE_Y / 2), k)),
                    Rotate3D(Point3D(i + (WINSIZE_X / 2) + gridSize,(WINSIZE_Y / 2) + j + gridSize, k)),
                    Rotate3D(Point3D(i + (WINSIZE_X / 2),(WINSIZE_Y / 2) + j + gridSize, k)),
                    Rotate3D(Point3D(i + (WINSIZE_X / 2), j + (WINSIZE_Y / 2), k + gridSize)),
                    Rotate3D(Point3D(i + (WINSIZE_X / 2) + gridSize, j + (WINSIZE_Y / 2), k + gridSize)),
                    Rotate3D(Point3D(i + (WINSIZE_X / 2) + gridSize, (WINSIZE_Y / 2) + j + gridSize, k + gridSize)),
                    Rotate3D(Point3D(i + (WINSIZE_X / 2),(WINSIZE_Y / 2) + j + gridSize, k + gridSize)),
                };


                Draw3DLine(getMemDC(), vertices[0], vertices[1]);
                Draw3DLine(getMemDC(), vertices[1], vertices[2]);
                Draw3DLine(getMemDC(), vertices[2], vertices[3]);
                Draw3DLine(getMemDC(), vertices[3], vertices[0]);


                Draw3DLine(getMemDC(), vertices[4], vertices[5]);
                Draw3DLine(getMemDC(), vertices[5], vertices[6]);
                Draw3DLine(getMemDC(), vertices[6], vertices[7]);
                Draw3DLine(getMemDC(), vertices[7], vertices[4]);


                Draw3DLine(getMemDC(), vertices[0], vertices[4]);
                Draw3DLine(getMemDC(), vertices[1], vertices[5]);
                Draw3DLine(getMemDC(), vertices[2], vertices[6]);
                Draw3DLine(getMemDC(), vertices[3], vertices[7]);
            }
        }
    }

    this->getBackBuffer()->render(getHDC());
    /*  Point3D startPoint = Rotate3D(Point3D(100, 100,0));
      Point3D endPoint = Rotate3D(Point3D(200, 200, 0));

      Draw3DLine(getMemDC(), startPoint, endPoint);*/
}

void C3DVector::Draw3DLine(HDC hdc, Point3D startPoint, Point3D endPoint)
{
    int startX = static_cast<int>(startPoint.x);
    int startY = static_cast<int>(startPoint.y);
    int endX = static_cast<int>(endPoint.x);
    int endY = static_cast<int>(endPoint.y);

    LineMake(hdc, startX, startY, endX, endY);
}

Point3D C3DVector::Rotate3D(const Point3D& p)
{
    float sinX = sin(_xAngle);
    float cosX = cos(_xAngle);
    float sinY = sin(_yAngle);
    float cosY = cos(_yAngle);

    float x = p.x * cosY + p.z * sinY;
    float y = p.y * cosX - p.z * sinX * cosY + p.x * sinX * sinY;
    float z = 0;//-p.x * sinY * cosX + p.y * sinX + p.z * cosX * cosY;
    return Point3D(x, y, z);
}
