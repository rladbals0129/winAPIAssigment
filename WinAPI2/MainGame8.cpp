#include "stdafx.h"
#include "MainGame8.h"


HRESULT MainGame8::init()
{
	GameNode::init();
	_currentX = WINSIZE_X / 2;
	_currentY = WINSIZE_Y;
	_redius = 100;
	_cannon = { WINSIZE_X / 2 , WINSIZE_Y - 50 };
	_cannon.angleMove = -90.0f;
	_change = -1;

	for (int i = 0; i < BULLET_MAX; i++)
	{
		_bullet[i].fire = false;
		_bullet[i].speed = 9;
		_bullet[i].collisionX = 1;
		_bullet[i].collisionY = 1;
	}


	return S_OK;
}

void MainGame8::release(void)
{
	GameNode::release();
}

void MainGame8::update(void)
{
	GameNode::update();
	_cannon.endX = cosf(REDIAN(_cannon.angleMove)) * 100 + _cannon.startX;
	_cannon.endY = sinf(REDIAN(_cannon.angleMove)) * 100 + _cannon.startY;
	_cannon.angleMove += _change;
	if (_cannon.angleMove == -165.0f)
	{
		_change = -_change;
	}
	if (_cannon.angleMove == -15.0f)
	{
		_change = -_change;
	}
	



	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fireBullet();
	}


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire)continue;

		_bullet[i].rc.left += cosf(REDIAN(_bullet[i].angle)) * 	_bullet[i].speed * _bullet[i].collisionX;
		_bullet[i].rc.right += cosf(REDIAN(_bullet[i].angle)) * _bullet[i].speed * _bullet[i].collisionX;
		_bullet[i].rc.top += sinf(REDIAN(_bullet[i].angle)) * _bullet[i].speed * _bullet[i].collisionY;
		_bullet[i].rc.bottom += sinf(REDIAN(_bullet[i].angle)) * _bullet[i].speed * _bullet[i].collisionY;

		if (_bullet[i].rc.left < 0)
		{
			_bullet[i].collisionX = -_bullet[i].collisionX;
			_bullet[i].rc.right = 50;
			_bullet[i].rc.left = 0;
		}
		if (_bullet[i].rc.top < 0)
		{
			_bullet[i].collisionY = -_bullet[i].collisionY;
			_bullet[i].rc.top = 0;
			_bullet[i].rc.bottom = 50;

		}
		if (_bullet[i].rc.right > WINSIZE_X)
		{
			_bullet[i].collisionX = -_bullet[i].collisionX;
			_bullet[i].rc.right = WINSIZE_X - 50;
			_bullet[i].rc.left = WINSIZE_X;
		}
		if (_bullet[i].rc.bottom > WINSIZE_Y)
		{
			_bullet[i].collisionY = -_bullet[i].collisionY;
			_bullet[i].rc.top = WINSIZE_Y - 50;
			_bullet[i].rc.bottom = WINSIZE_Y;
		}


	}

}

void MainGame8::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	EllipaseMakeCenter(memDC, _currentX, _currentY, _redius);
	LineMake(memDC, _cannon.startX, _cannon.startY, _cannon.endX, _cannon.endY);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire) continue;
		Ellipse(memDC, _bullet[i].rc.left, _bullet[i].rc.top, _bullet[i].rc.right, _bullet[i].rc.bottom);
	}




	this->getDoubleBuffer()->render(hdc, 0, 0);


}

void MainGame8::fireBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet[i].fire)continue;

		_bullet[i].fire = true;
		_bullet[i].rc = RectMakeCenter(_cannon.endX, _cannon.endY, 50, 50);
		_bullet[i].angle = _cannon.angleMove;
		break;
	}

}
