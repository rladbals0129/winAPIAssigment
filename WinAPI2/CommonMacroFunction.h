#pragma once

//일반적으로 사용하는 함수를 매크로화 시키겠다.

inline POINT PointMake(int x, int y)  //2d 방향벡터
{
	POINT pt = { x,y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}

inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2 , y - height / 2 ,x + width / 2, y + height / 2 };

	return rc;
	
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void DrawEllipseMake(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline void EllipaseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipaseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void EllipaseMakeCenter(HDC hdc, int x, int y, int redius)
{
	Ellipse(hdc, x - redius, y - redius, x + redius, y + redius);
}

inline RECT CollisionAreaResizing(RECT& rcDest, int width, int height)
{
	RECT rc =
	{
		rcDest.left + width / 2,
		rcDest.top + height / 2,
		rcDest.right + width / 2,
		rcDest.bottom + height / 2
	};
	return rc;
}