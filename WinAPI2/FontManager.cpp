#include "stdafx.h"
#include "FontManager.h"

//char*
void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontweight, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	/*
font = CreateFopnt
(
	v문자크기, 문자폭, 기울기(전체), 문자 방향, v문자 굵기,
	기울기( t / f ), 밑줄( t / f ), 취소선,
	v문자세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, v폰트
);
*/
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
