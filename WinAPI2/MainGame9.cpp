#include "stdafx.h"
#include "MainGame9.h"


HRESULT MainGame9::init()
{
	GameNode::init();
	_currentX = WINSIZE_X / 2;
	_currentY = WINSIZE_Y;
	_redius = 100;
	_cannon = { WINSIZE_X / 2 , WINSIZE_Y - 50 };
	_cannon.angleMove = -90.0f;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		_bullet[i].fire = false;
		_bullet[i].speed = 4;
		_bullet[i].collisionX = 1;
		_bullet[i].collisionY = 1;	
	}


	return S_OK;
}

void MainGame9::release(void)
{
	GameNode::release();
}

void MainGame9::update(void)
{
	GameNode::update();
	_cannon.endX = cosf(REDIAN(_cannon.angleMove)) * 100 + _cannon.startX;
	_cannon.endY = sinf(REDIAN(_cannon.angleMove)) * 100 + _cannon.startY;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.angleMove >= -165.0f)
	{
		_cannon.angleMove--;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.angleMove <= -15.0f)
	{
		_cannon.angleMove++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fireBullet();
	}


	for (int i = 0; i < BULLET_MAX; ++i)
	{
		if (!_bullet[i].fire)continue;

		_bullet[i].rc.left += cosf(REDIAN(_bullet[i].angle)) * 	_bullet[i].speed * _bullet[i].collisionX;
		_bullet[i].rc.right += cosf(REDIAN(_bullet[i].angle)) * _bullet[i].speed * _bullet[i].collisionX;
		_bullet[i].rc.top += sinf(REDIAN(_bullet[i].angle)) * _bullet[i].speed * _bullet[i].collisionY;
		_bullet[i].rc.bottom += sinf(REDIAN(_bullet[i].angle)) * _bullet[i].speed * _bullet[i].collisionY;

		_bullet[i].centerX = (_bullet[i].rc.right + _bullet[i].rc.left) / 2;
		_bullet[i].centerY = (_bullet[i].rc.bottom + _bullet[i].rc.top) / 2;

		for (int j = 0; j < BULLET_MAX; ++j)
		{
			if (i == j)continue;

			if (!_bullet[j].fire)continue;



			float dx = _bullet[j].centerX - _bullet[i].centerX;
			float dy = _bullet[j].centerY - _bullet[i].centerY;
			float distance = sqrt(dx * dx + dy * dy);

			if (distance <= _bullet[i].redius + _bullet[j].redius)
			{	
				_bullet[i].collisionX = -_bullet[i].collisionX;
				_bullet[i].collisionY = -_bullet[i].collisionY;
				_bullet[j].collisionX = -_bullet[j].collisionX;
				_bullet[j].collisionY = -_bullet[j].collisionY;
			}
		}




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

void MainGame9::render(HDC hdc)
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

void MainGame9::fireBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet[i].fire)continue;

		_bullet[i].fire = true;
		_bullet[i].rc = RectMakeCenter(_cannon.endX, _cannon.endY, 50, 50);
		_bullet[i].angle = _cannon.angleMove;

		_bullet[i].centerX = (_bullet[i].rc.right + _bullet[i].rc.left) / 2;
		_bullet[i].centerY = (_bullet[i].rc.bottom + _bullet[i].rc.top) / 2;
		_bullet[i].redius = 25;

		break;
	}

}

void MainGame9::CircleCollision()
{
	


}




