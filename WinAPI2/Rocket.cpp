#include "stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_x = static_cast<float>(WINSIZE_X / 2);
	_y = static_cast<float>(WINSIZE_Y / 2);	
	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/ShootingGame/Player/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_flame = new Flame;
	_flame->init("불",&_x,&_y);


	_beam = new Beam;
	_beam->init(1, 0.5f);
	_beamIrradiation = false;

	_missile = new MissileM1;
	_missile->init(50,600.f);

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);

	_missile->release();
	SAFE_DELETE(_missile);

	_beam->release();
	SAFE_DELETE(_beam);

}

void Rocket::update(void)
{

	if (KEYMANAGER->isStayKeyDown('D') && _rc.right < WINSIZE_X && !_beamIrradiation)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown('A') && _rc.left > 0 && !_beamIrradiation)
	{
		_x -= ROCKET_SPEED;

	}

	if (KEYMANAGER->isStayKeyDown('S') && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown('W') && _rc.top > 0)
	{
		_y -= ROCKET_SPEED;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());



	usingSkill();

	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_missile->fire((_rc.left + _rc.right) / 2, _rc.top);
		}
		break;
	case BEAM:
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_beam->fire(_x,_y - 430);
			_beamIrradiation = true;
		}
		else
		{
			_beamIrradiation = false;
		}

		break;
	default:
		break;
	}



	_missile->update();
	_beam->update();
	_flame->update();
}

void Rocket::render()
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_missile->render();
	_beam->render();
}

void Rocket::usingSkill()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_setWeapon = MISSILE;
		/*_missile = nullptr;
		_missile = new MissileBase;
		_missile->init(50,600.f);*/
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_setWeapon = BEAM;
		//_missile = nullptr;
	

		//_missile = new MissileShotGun;
		//_missile->init(50,600.f);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
	
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		
	}
}



/*
과제1. 움직이는 적 패턴 추가

- 움직임을 서로 다르게 해온다.
ㄴ 패턴은 총 3가지를 만들면 ok

과제2. 로켓 무장변경 추가 (무기)
- F1 : 일반미사일

- F2 : 산탄

- F3 : 미니로켓

- F4 : 쉴드

- F5 : 유도미사일

- F6 : 레이저

- F7 : 블랙홀
ㄴ 영향을 받는적과 아닌적으로 구분
ㄴ 블랙홀의 중점에 가까운 적일수록 스킬이 끝나면 튕겨나가는 관성이 강해진다.

*/