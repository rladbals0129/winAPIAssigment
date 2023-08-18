#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0,0)),
_currentFrameX(0),
_currentFrameY(0),
_x(0.f),
_y(0.f),
_worldTimeCount(0.f),
_rndTimeCount(0.f)
{
}

HRESULT Enemy::init(void)
{
	//!DO nothing
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50.f, 150.f);

	_image = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_die = false;

	IMAGEMANAGER->addImage("체력", "Resources/Images/ShootingGame/UI/hpUI.bmp", 152, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력바", "Resources/Images/ShootingGame/UI/hpbarUI.bmp", 117, 20, true, RGB(255, 0, 255));
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position, float startAngle )
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50.f, 150.f);

	_image = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_startAngle = startAngle;
	_center = position;
	_angle = 0.f;
	radius = 300.f;
	_die = false;
	return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
	if (!_die)
	{
		move();
	}
	
}

void Enemy::render(void)
{
	if (!_die)
	{
		draw();
		animation();
	}

}


void Enemy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

void Enemy::move(void)
{
	//적마다 구현 다르므로 자식에서
}


void Enemy::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;

		}
	}
}

