#include "stdafx.h"
#include "Bullets.h"

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;
	cout << "부모" << endl;
	for (int i = 0; i <bulletMax; i++)
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
		_viBullet->angle = getAngle(x, y, _ptMouse.x, _ptMouse.y);
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
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();	++_viBullet )
	{
		if (!_viBullet->fire) continue;
		

		_viBullet->fireX += cos(_viBullet->angle) * _viBullet->speed;
		_viBullet->fireY -= sin(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->fireX, _viBullet->fireY, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

	

		if (_viBullet->frameTick + BULLETS_COUNT <= GetTickCount())
		{
			_viBullet->frameTick = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
		}

		if (getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY) > _range)
		{
			_viBullet->fire = false;
			
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
	bullet.angle = getAngle(x, y, _ptMouse.x, _ptMouse.y);
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
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), _viBullet->img->getFrameY());
		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void MissileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= sin(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(),
			_viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void MissileM1::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT Beam::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void Beam::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void Beam::update(void)
{
	move();
}

void Beam::render()
{
	draw();
}

void Beam::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/ShootingGame/Bullet/beam.bmp",
		0.0f, 0.0f,
		426, 801,
		4, 1,
		true,
		RGB(255, 0, 255));
	bullet.speed = 0.1f;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

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

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameX(), _viBullet->img->getFrameY());

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

/*
과제1 .
미사일 충돌처리

-내가 발사한 미사일로 적을 제거한다.
ㄴ 본인이 생각한 가장 효율적인(객체지향적인)방법으로

과제2.
체력바 구현

-로켓과 적의 체력바를 구현한다.

2가지버전으로

1. 체력바를 각각의 객체 위에 띄워주는 방법

2. 적 객체 한정으로 체력바를 공유하는 방법


*/

HRESULT EnemyMissile::init(int bulletMax, float range)
{
	return S_OK;
}

void EnemyMissile::release(void)
{
}

void EnemyMissile::update(void)
{
}

void EnemyMissile::render()
{
}

void EnemyMissile::fire(float x, float y)
{
}

void EnemyMissile::draw(void)
{
}

void EnemyMissile::move(void)
{
}

void EnemyMissile::removeBullet(int arrNum)
{
}
