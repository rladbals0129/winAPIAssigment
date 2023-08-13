#include "stdafx.h"
#include "Bullets.h"

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet)); //ZeroMemory : 0으로 채운다 (memset)차이점 -> 1. 0으로초기화 2. 0이아닌 값으로 초기화 가능
		/*
			MoveMemory
			CopyMemory
			FillMemory
			ZeroMemory
		*/
		bullet.img = new GImage;
		bullet.img->init("Resources/Images/ShootingGame/Bullet/Missile.bmp",
			0.0f, 0.0f,
			416, 64,
			13, 1,
			true,
			RGB(255, 0, 255));
		bullet.fire = false;
		bullet.frameTick = 7.0f;
		bullet.speed = 5.0f;
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void Missile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();


}

void Missile::update(void)
{
	move();
}

void Missile::render()
{
	draw();
}

void Missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void Missile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire)
		{
			_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameX(), _viBullet->img->getFrameY());

		}

	}
}

void Missile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->angle = getAngle(_viBullet->x, _viBullet->y, _ptMouse.x, _ptMouse.y);

		_viBullet->fireX += cos(_viBullet->angle) * _viBullet->speed;
		_viBullet->fireY -= sin(_viBullet->angle) * _viBullet->speed;
		//_viBullet->fireY -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->fireX, _viBullet->fireY, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY) > _range)
		{
			_viBullet->fire = false;
		}

		if (_viBullet->frameTick + BULLETS_COUNT <= GetTickCount())
		{
			_viBullet->frameTick = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
		}


	}
}



//===========================================





HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;




	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();

}

void MissileM1::render()
{
	draw();
}

void MissileM1::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/ShootingGame/Bullet/Missile.bmp",
		0.0f, 0.0f,
		416, 64,
		13, 1,
		true,
		RGB(255, 0, 255));
	bullet.speed = 5.0f;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	//	_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
	_vBullet.push_back(bullet);



	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void MissileM1::draw(void)
{
}

void MissileM1::move(void)
{
}
