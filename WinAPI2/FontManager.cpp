#include "stdafx.h"
#include "FontManager.h"

//char*
void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT font = CreateFont
	(
		fontSize,
		0,
		0,
		0,
		fontweight,
		0,
		0,
		0,
		HANGEUL_CHARSET,
		0,
		0,
		0,
		0,
		TEXT(fontName)
	);

	//auto font = (HFONT)SelectObject(hdc, font);
	auto oldFont = (HFONT)SelectObject(hdc, font);;

	SetTextColor(hdc, color);

	const int stringLength = strlen(printString);
	wchar_t charBuffer[256];
	//ZeroMemory(charBuffer, stringLength);

	TextOut(hdc, destX, destY, printString, stringLength);
	//TextOutW(hdc,);


	SelectObject(hdc, oldFont);
	DeleteObject(font);// 올드폰트에 넣어주고 더이상쓸모없으니 딜리트해준다
}
