#include "stdafx.h"
#include "Hole.h"



HRESULT Hole::init(void)
{
	_centerX = WINSIZE_X / 2;
	_centerY = WINSIZE_Y / 2;
	_redius = 100.0f;
	return S_OK;
}

void Hole::release(void)
{

}

void Hole::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_centerX -= 5.0f;

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_centerX += 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_centerY -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_centerY += 5.0f;
	}
	//cout << _centerX << "   " << _centerY << endl;

}

void Hole::render(void)
{
	EllipaseMakeCenter(getMemDC(), _centerX, _centerY, _redius);
}

Hole::Hole()
{
}


Hole::~Hole()
{
}
