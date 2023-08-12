#include "Stdafx.h"
#include "C3DMatrix.h"




C3DMatrix::C3DMatrix() : objPosition(3, 0.0f), prevMousePos({ 0, 0 }), isLeftButtonPressed(false)
{
}

C3DMatrix::~C3DMatrix() { }

HRESULT C3DMatrix::init()
{
    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.z = 0.0f;
    camera.pitch = 0.0f;
    camera.yaw = 0.0f;
    return S_OK;
}

void C3DMatrix::release() { }

void C3DMatrix::update()
{
    if (KEYMANAGER->isStayKeyDown(VK_UP))
    {
        objPosition[1] += 1.0f;
    }
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        objPosition[1] -= 1.0f;
    }
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        objPosition[0] -= 1.0f;
    }
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        objPosition[0] += 1.0f;
    }

    if (isLeftButtonPressed)
    {
        POINT curMousePos = _ptMouse;

        float deltaX = static_cast<float>(curMousePos.x - prevMousePos.x);
        float deltaY = static_cast<float>(curMousePos.y - prevMousePos.y);

        camera.yaw -= deltaX * 0.005f;
        camera.pitch -= deltaY * 0.005f;

        prevMousePos = curMousePos;
    }
    else
    {
        prevMousePos = _ptMouse;
    }

    isLeftButtonPressed = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
}

void C3DMatrix::render()
{
    DrawGrid(getMemDC(), 50, 100); // 50 x 50 격자 그리기

    camera.x = objPosition[0];
    camera.y = objPosition[1];
    camera.z = objPosition[2] - 5000.0f;
    camera.pitch = -3.14159f / 2; // 탑뷰를 보도록 수정

    // 정육면체 정점 좌표 변경
    std::vector<float> objectVertices = {
               0.0f, 0.0f, 0.0f,
        100.0f, 0.0f, 0.0f,
        100.0f, 0.0f, -100.0f,
        0.0f, 0.0f, -100.0f,
        0.0f, 100.0f, 0.0f,
        100.0f, 100.0f, 0.0f,
        100.0f, 100.0f, -100.0f,
        0.0f, 100.0f, -100.0f
    };
    RenderObject(objectVertices, getMemDC(), camera);
}

C3DMatrix::Point2D C3DMatrix::WorldToScreen(float x, float y, float z, const Camera& camera)
{
    float radians = (camera.pitch);
    float cx = (x * cos(radians)) - (z * sin(radians));
    float cy = (y * cos(radians)) - (z * sin(radians));
    float cz = (y * sin(radians)) + (z * cos(radians));

    radians = (camera.yaw);
    float rx = (cz * sin(radians)) + (cx * cos(radians));
    float ry = (-cz * sin(radians)) + (cx * cos(radians));

    POINT screenSize;
    screenSize.x = WINSIZE_X;
    screenSize.y = WINSIZE_Y;
    float screenX = (screenSize.x / 2.0f) * (1 + (rx / (cz * 100.0f)));
    float screenY = (screenSize.y / 2.0f) * (1 - (cy / (cz * 100.0f)));

    return { screenX, screenY };
}

//육면체를 그리는 함수입니다
void C3DMatrix::RenderObject(const std::vector<float>& vertices, HDC hdc, const Camera& camera)
{
    std::vector<Point2D> points2D = Calculate2DVertices(vertices, camera);
    DrawLines(hdc, points2D);
}

// 정육면체의 정점을 스크린 좌표로 변환하는 함수입니다.
std::vector<C3DMatrix::Point2D> C3DMatrix::Calculate2DVertices(const std::vector<float>& vertices, const Camera& camera)
{
    std::vector<Point2D> points2D;
    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        points2D.push_back(WorldToScreen(vertices[i], vertices[i + 1], vertices[i + 2], camera));
    }
    return points2D;
}

// 스크린 좌표로 변환된 정점 좌표로 선을 그리는 함수입니다.
void C3DMatrix::DrawLines(HDC hdc, const std::vector<Point2D>& points)
{
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    int nPoints = points.size();

    for (int i = 0; i < nPoints; ++i)
    {
        for(int j = i + 1; j < nPoints; ++j)
    {
        MoveToEx(hdc, (int)points[i].x, (int)points[i].y, nullptr);
        LineTo(hdc, (int)points[j].x, (int)points[j].y);
    }
    }

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}


void C3DMatrix::SetMousePosition(POINT ptMouse) // 추가
{
    _ptMouse = ptMouse;
}

void C3DMatrix::DrawGrid(HDC hdc, int gridSize, int cellSize)
{
    int halfGridSize = gridSize * cellSize / 2;

    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    for (int i = -halfGridSize; i <= halfGridSize; i += cellSize)
    {
        // X 축과 평행한 격자 선
        Point2D startPoint = WorldToScreen(float(i), 0.0f, float(-halfGridSize), camera);
        Point2D endPoint = WorldToScreen(float(i), 0.0f, float(halfGridSize), camera);
        MoveToEx(hdc, int(startPoint.x), int(startPoint.y), nullptr);
        LineTo(hdc, int(endPoint.x), int(endPoint.y));

        // Z 축과 평행한 격자 선
        startPoint = WorldToScreen(float(-halfGridSize), 0.0f, float(i), camera);
        endPoint = WorldToScreen(float(halfGridSize), 0.0f, float(i), camera);
        MoveToEx(hdc, int(startPoint.x), int(startPoint.y), nullptr);
        LineTo(hdc, int(endPoint.x), int(endPoint.y));
    }

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}