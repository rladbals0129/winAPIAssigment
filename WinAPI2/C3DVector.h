#pragma once
#include "GameNode.h"
struct Point3D
{
	float x, y, z;

	Point3D(float x, float y, float z) : x(x), y(y), z(z) {}
};

class C3DVector : public GameNode
{
private:
	float _xAngle;
	float _yAngle;
	float ROTATION_SPEED = 0.05f;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void Draw3DLine(HDC hdc, Point3D startPoint, Point3D endPoint);
	Point3D Rotate3D(const Point3D& p);
};

