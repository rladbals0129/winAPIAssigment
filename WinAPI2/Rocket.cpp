#include "stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_x = static_cast<float>(WINSIZE_X / 2);
	_y = static_cast<float>(WINSIZE_Y / 2);	
	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/ShootingGame/Player/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_flame = new Flame;

	_flame->init();
	_flame->setFlamePos(&_x, &_y);

	return S_OK;
}

void Rocket::release(void)
{
}

void Rocket::update(void)
{

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_x -= ROCKET_SPEED;

	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKET_SPEED;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

	}


	_flame->update();
}

void Rocket::render()
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
}



/*
과제1. 로켓에 flame이미지 추가

- Flame 이미지는 프레임으로 렌더를 시킨다.

※ Flame 클래스에는 로켓에 대한 정보가 있으면 안되며 MainGame 또한 Flame에 대한 정보를 알 필요가 없다.

- 로켓에 플레임을 넣어야되나?

과제2.


*/