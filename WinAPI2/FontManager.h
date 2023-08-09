#pragma once
#include "SingletonBase.h"
class FontManager : public SingletonBase <FontManager>
{


public:
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight,
		char* printString, int length, COLORREF color);

	

};