#include "stdafx.h"
#include "Flame.h"

HRESULT Flame::init(void)
{
	_idx = 0;
	_cnt = 0;
	IMAGEMANAGER->addFrameImage("불", "Resources/Images/ShootingGame/Player/Flame.bmp",
		432, 297,
		9, 1,
		true,
		RGB(255, 0, 255));

	return S_OK;
}

void Flame::release(void)
{
}

void Flame::update(void)
{
	FlameRender();
}

void Flame::render()
{
	IMAGEMANAGER->frameRender("불",getMemDC(), *_posX-25, *_posY+25, _idx, 0);
}

void Flame::FlameRender()
{
	_cnt++;
	if (_cnt % 3 == 0)
	{
		_idx++;
		if (_idx > 8)
		{
			_idx = 0;
		}
	}
}


/*
과제1. 로켓에 flame이미지 추가

- Flame 이미지는 프레임으로 렌더를 시킨다.

※ Flame 클래스에는 로켓에 대한 정보가 있으면 안되며 MainGame 또한 Flame에 대한 정보를 알 필요가 없다.

- 로켓에 플레임을 넣어야되나?

과제2.


*/