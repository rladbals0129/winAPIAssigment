#include "stdafx.h"
#include "MainGame3.h"




HRESULT MainGame3::init(void)
{
	GameNode::init();

	
	_playerRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 40, 40);
	_playerDIE = false;
	_playerHP = 3;
	_playerHPBAR = RectMakeCenter(WINSIZE_X / 5, 20, 100 * _playerHP, 20);
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].rc = RectMakeCenter(
			RND->getFromIntTo(20, WINSIZE_X - 20),
			-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
			20, 20);
		_enemy[i].speed = RND->getFromIntTo(2, 8);
		_enemy[i].die = false;
	}
	//startTime = time(nullptr);

	return S_OK;
}

void MainGame3::release(void)
{
	GameNode::release();
	
}

void MainGame3::update(void)
{
	GameNode::update();
	
	if (!_playerDIE)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _playerRC.right)
		{
			_playerRC.left += PLAYER_SPEED;
			_playerRC.right += PLAYER_SPEED;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _playerRC.left)
		{
			_playerRC.left -= PLAYER_SPEED;
			_playerRC.right -= PLAYER_SPEED;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && 0 < _playerRC.top)
		{
			_playerRC.top -= PLAYER_SPEED;
			_playerRC.bottom -= PLAYER_SPEED;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _playerRC.bottom)
		{
			_playerRC.top += PLAYER_SPEED;
			_playerRC.bottom += PLAYER_SPEED;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			fireBullet();
		}

		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (!_bullet[i].fire)continue;
			_bullet[i].rc.top -= 14;
			_bullet[i].rc.bottom -= 14;

			if (_bullet[i].rc.bottom < 0) _bullet[i].fire = false;

			for (int j = 0; j < ENEMY_MAX; j++)
			{
				if (IntersectRect(&_colider, &_bullet[i].rc, &_enemy[j].rc))//적과 총알 충돌
				{
					_bullet[i].fire = false;
					_enemy[j].rc = RectMakeCenter(
						RND->getFromIntTo(20, WINSIZE_X - 20),
						-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
						20, 20);
				}
			}
		}

		//적 객체 이동
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemy[i].die) continue;

			_enemy[i].rc.top += _enemy[i].speed;
			_enemy[i].rc.bottom += _enemy[i].speed;

			if (_enemy[i].rc.top > WINSIZE_Y)	//화면밖으로 넘어가면 위로 올려준다
			{
				_enemy[i].rc = RectMakeCenter(
					RND->getFromIntTo(20, WINSIZE_X - 20),
					-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
					20, 20);
			}
		}

		//플레이어와 적 충돌 피감소
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemy[i].die) continue;

			if (IntersectRect(&_colider, &_playerRC, &_enemy[i].rc))
			{
				_playerHP--;
				_enemy[i].rc = RectMakeCenter(
					RND->getFromIntTo(20, WINSIZE_X - 20),
					-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
					20, 20);
			}


		}

		
	}
		

	
}

void MainGame3::render(HDC hdc)
{

	GameNode::render(hdc);
	
	
		DrawRectMake(hdc, _playerRC);
		if (_playerHP == 3)
		{
			HBRUSH hp = CreateSolidBrush(RGB(255, 0, 0));
			FillRect(hdc, &_playerHPBAR, hp);
			DeleteObject(hp);
		}
		else if (_playerHP == 2)
		{
			_playerHPBAR.right = 200;
			HBRUSH hp = CreateSolidBrush(RGB(242, 101, 34));
			FillRect(hdc, &_playerHPBAR, hp);
			DeleteObject(hp);
		}
		else if (_playerHP == 1)
		{
			_playerHPBAR.right = 100;
			HBRUSH hp = CreateSolidBrush(RGB(0, 255, 0));
			FillRect(hdc, &_playerHPBAR, hp);
			DeleteObject(hp);
		}
		else
		{
			_playerDIE = true;
		}

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemy[i].die) continue;

			Rectangle(hdc, _enemy[i].rc.left, _enemy[i].rc.top, _enemy[i].rc.right, _enemy[i].rc.bottom);
		}

		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (!_bullet[i].fire) continue;
			Ellipse(hdc, _bullet[i].rc.left, _bullet[i].rc.top, _bullet[i].rc.right, _bullet[i].rc.bottom);
		}
	
	


	
}

void MainGame3::fireBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet[i].fire)continue;

		_bullet[i].fire = true;
		_bullet[i].rc = RectMakeCenter
		(
			_playerRC.left + (_playerRC.right - _playerRC.left) / 2,
			_playerRC.top + (_playerRC.bottom - _playerRC.top) / 2 - 24, 10, 10
		);
		break;
	}
}


