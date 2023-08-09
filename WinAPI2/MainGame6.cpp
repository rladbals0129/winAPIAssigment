#include "stdafx.h"
#include "MainGame6.h"



HRESULT MainGame6::init()
{
	GameNode::init();
	//_second.x = cosf()
	currentX = WINSIZE_X / 2;
	currentY = WINSIZE_Y / 2 - 100;
	_redius = 300;

	return S_OK;
}

void MainGame6::release(void)
{
	GameNode::release();
}

void MainGame6::update(void)
{
	GameNode::update();
	

	GetLocalTime(&_st);
	_st.wSecond;
	_st.wMinute;
	_st.wHour;

	_second.x = cosf(REDIAN(_st.wSecond * 6.0f - 90)) * (_redius - 50) + currentX;
	_second.y = sinf(REDIAN(_st.wSecond * 6.0f - 90)) * (_redius - 50) + currentY;

	_minute.x = cosf(REDIAN(_st.wMinute * 6.0f - 90)) * (_redius - 100) + currentX;
	_minute.y = sinf(REDIAN(_st.wMinute * 6.0f - 90)) * (_redius - 100) + currentY;

	_hour.x = cosf(REDIAN(_st.wHour * 30.0f - 90)) * (_redius - 150) + currentX;
	_hour.y = sinf(REDIAN(_st.wHour * 30.0f - 90)) * (_redius - 150) + currentY;

}

void MainGame6::render(HDC hdc)
{
	GameNode::render(hdc);
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	EllipaseMakeCenter(memDC, currentX, currentY, _redius);
	char strSecond[128];
	char strMinute[128];
	char strHour[128];

	sprintf_s(strSecond, "%d ÃÊ", _st.wSecond);
	TextOut(memDC, WINSIZE_X / 2, 100, strSecond, strlen(strSecond));

	sprintf_s(strMinute, "%d ºĞ", _st.wMinute);
	TextOut(memDC, WINSIZE_X / 2 - 50, 100, strMinute, strlen(strMinute));

	sprintf_s(strHour, "%d ½Ã", _st.wHour);
	TextOut(memDC, WINSIZE_X / 2- 100, 100, strHour, strlen(strHour));
	
	LineMake(memDC, currentX, currentY, _second.x, _second.y);
	LineMake(memDC, currentX, currentY, _minute.x, _minute.y);
	LineMake(memDC, currentX, currentY, _hour.x, _hour.y);


	this->getDoubleBuffer()->render(hdc, 0, 0);
}
