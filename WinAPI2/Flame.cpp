#include "stdafx.h"
#include "Flame.h"

HRESULT Flame::init(const char* imageName,float* x, float* y)
{
	
	_image = IMAGEMANAGER->addFrameImage("불", "Resources/Images/ShootingGame/Player/Flame.bmp",
		432, 297,
		9, 1,
		true,
		RGB(255, 0, 255));
	_posX = x;
	_posY = y;

	_rc = RectMakeCenter((int)_posX, (int)_posY, _image->getFrameWidth(), _image->getFrameHeight());
	_flameTick = 7.f;

	return S_OK;
}

void Flame::release(void)
{
}

void Flame::update(void)
{
	if (FLAME_COUNT + _flameTick <= GetTickCount())
	{
		_flameTick = GetTickCount();
		_image->setFrameX(_image->getFrameX() + 1);
		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
	}

	_rc = RectMakeCenter(*_posX, *_posY + 180, _image->getFrameWidth(),
		_image->getFrameHeight());
}

void Flame::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());

}




/*
과제1. 로켓에 flame이미지 추가

- Flame 이미지는 프레임으로 렌더를 시킨다.

※ Flame 클래스에는 로켓에 대한 정보가 있으면 안되며 MainGame 또한 Flame에 대한 정보를 알 필요가 없다.

- 로켓에 플레임을 넣어야되나?

과제2.


*/