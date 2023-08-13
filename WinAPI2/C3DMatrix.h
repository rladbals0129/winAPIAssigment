#pragma once
#include "GameNode.h"
class C3DMatrix : public GameNode
{
	struct Camera
	{
		float x, y, z;     // 카메라 위치
		float pitch, yaw;  // 카메라 회전
		float zaw;

		Camera() : x(0.0f), y(0.0f), z(0.0f), pitch(0.0f), yaw(0.0f), zaw(0.0f){}
	};

	struct Point2D
	{
		float x, y;
	};
public:
	HRESULT init();
	void release();
	void update();
	void render();
	C3DMatrix();
	~C3DMatrix();
	void SetMousePosition(POINT ptMouse);
private:
	Camera camera;
	std::vector<float> objPosition; // 정육면체 위치
	POINT prevMousePos;
	bool isLeftButtonPressed;

	Point2D WorldToScreen(float x, float y, float z, const Camera& camera);
	void RenderObject(const std::vector<float>& vertices, HDC hdc, const Camera& camera);
	std::vector<Point2D> Calculate2DVertices(const std::vector<float>& vertices, const Camera& camera);
	void DrawLines(HDC hdc,const std::vector<Point2D>& points);
	void DrawGrid(HDC hdc, int gridSize, int cellSize);
};

