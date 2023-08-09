#include "stdafx.h"
#include "Poop.h"



HRESULT Poop::init()
{
	isActive = false;
	return S_OK;
}

void Poop::release(void)
{
}

void Poop::update(void)
{
	_rc.top += 5;
	_rc.bottom += 5;
	if (_rc.bottom > WINSIZE_Y)
	{
		isActive = false;
	}
}

void Poop::render(HDC hdc)
{
	DrawRectMake(hdc, _rc);
}
