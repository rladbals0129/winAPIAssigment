#include "stdafx.h"
#include "MainGame4.h"



HRESULT MainGame4::init(void)
{
	GameNode::init();

	_player1.rc = RectMakeCenter(WINSIZE_X / 4, WINSIZE_Y / 2 + 200, 40, 20);
	_player1.hp = 300;
	_player1.hpbar = RectMake(0, 0, _player1.hp, 20);
	_player1.die = false;  
	_player1.speed = 5;    

	for (int i = 0; i < BULLET_MAX; i++)
	{
		_bullet1[i].fire = false;
	}

	_player2.rc = RectMakeCenter(WINSIZE_X - (WINSIZE_X / 4), WINSIZE_Y / 2 + 200, 40, 20);
	_player2.hp = 300;
	_player2.hpbar = RectMake(500 , 0, 300, 20);
	_player2.die = false;
	_player2.speed = 5;  

	for (int i = 0; i < BULLET_MAX; i++)
	{
		_bullet2[i].fire = false;
	}

	return S_OK;
}

void MainGame4::release(void)
{
	GameNode::release();
}

void MainGame4::update(void)
{
	GameNode::update();

	//-----------------------플레이어1 이동과 슛-----------------------
	if ((KEYMANAGER->isStayKeyDown(0x57)|| KEYMANAGER->isStayKeyDown(0x77) )&& _player1.rc.top > 30) //up
	{
		_player1.rc.top -= _player1.speed;
		_player1.rc.bottom -= _player1.speed;

	}
	if ((KEYMANAGER->isStayKeyDown(0x53) || KEYMANAGER->isStayKeyDown(0x73)) && _player1.rc.bottom < WINSIZE_Y)//down
	{
		_player1.rc.top += _player1.speed;
		_player1.rc.bottom += _player1.speed;
	}
	if ((KEYMANAGER->isStayKeyDown(0x41) || KEYMANAGER->isStayKeyDown(0x61)) && _player1.rc.left > 0)//left
	{
		_player1.rc.left -= _player1.speed;
		_player1.rc.right -= _player1.speed;
	}
	if ((KEYMANAGER->isStayKeyDown(0x44) || KEYMANAGER->isStayKeyDown(0x64)) && _player1.rc.right < WINSIZE_X /2 )//right
	{
		_player1.rc.left += _player1.speed;
		_player1.rc.right += _player1.speed;
	}

 	if (KEYMANAGER->isOnceKeyDown(0x47))//attack
	{
		fireBullet(PLAYER1_NUM);
	}
	
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet1[i].fire) continue;
		_bullet1[i].rc.left += 14;
		_bullet1[i].rc.right += 14;

		if (_bullet1[i].rc.right > 800 ) _bullet1[i].fire = false;

		
		if (IntersectRect(&_colider, &_bullet1[i].rc, &_player2.rc))//적과 총알 충돌
		{
			_bullet1[i].fire = false;
			_player2.hp -= 15;
		}
		

	}


	// -----------------------------플레이어2 이동과 슛 -------------------------------
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player2.rc.top > 30) //up
	{
		_player2.rc.top -= _player2.speed;
		_player2.rc.bottom -= _player2.speed;

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player2.rc.bottom < WINSIZE_Y)//down
	{
		_player2.rc.top += _player2.speed;
		_player2.rc.bottom += _player2.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player2.rc.left > WINSIZE_X - WINSIZE_X / 2)//left
	{
		_player2.rc.left -= _player2.speed;
		_player2.rc.right -= _player2.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)&& _player2.rc.right < WINSIZE_X)//right
	{
		_player2.rc.left += _player2.speed;
		_player2.rc.right += _player2.speed;
	}
	if (KEYMANAGER->isOnceKeyDown(0x4C))//attack
	{
		fireBullet(PLAYER2_NUM);
	}
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet2[i].fire)continue;
		_bullet2[i].rc.left -= 14;
		_bullet2[i].rc.right -= 14;

		if (_bullet2[i].rc.right < 0) _bullet2[i].fire = false;

		if (IntersectRect(&_colider, &_bullet2[i].rc, &_player1.rc))//적과 총알 충돌
		{
			_bullet2[i].fire = false;
			_player1.hp -= 15;
		}
	}

}

void MainGame4::render(void)
{

	//DrawRectMake(hdc, _player1.hpbar);
	DrawRectMake(getMemDC(), _player2.hpbar);
	LineMake(hdc, 400, 0, 400, 800);
	HBRUSH hp1;
	HBRUSH hp2;
	if (_player1.hp <= 300 && _player1.hp >= 200)
	{
		hp1 = CreateSolidBrush(RGB(0, 255, 0));				
	}
	else if (_player1.hp < 200 && _player1.hp >= 100)
	{
		hp1 = CreateSolidBrush(RGB(255, 255, 0));		
	}
	else
	{
		hp1 = CreateSolidBrush(RGB(255, 0, 0));
	}
	
	if (_player2.hp <= 300 && _player2.hp >= 200)
	{
		hp2 = CreateSolidBrush(RGB(0, 255, 0));
	}
	else if (_player2.hp < 200 && _player2.hp >= 100)
	{
		hp2 = CreateSolidBrush(RGB(255, 255, 0));				
	}
	else
	{
		hp2 = CreateSolidBrush(RGB(255, 0, 0));				
	}
	FillRect(hdc, &_player1.hpbar, hp1);
	FillRect(hdc, &_player2.hpbar, hp2);
	DeleteObject(hp1);
	DeleteObject(hp2);
	_player1.hpbar.right = _player1.hp;
	_player2.hpbar.left = WINSIZE_X - _player2.hp;
	DrawRectMake(hdc, _player1.rc);
	DrawRectMake(hdc, _player2.rc);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet1[i].fire) continue;
		Ellipse(hdc, _bullet1[i].rc.left, _bullet1[i].rc.top, _bullet1[i].rc.right, _bullet1[i].rc.bottom);
	}
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet2[i].fire) continue;
		Ellipse(hdc, _bullet2[i].rc.left, _bullet2[i].rc.top, _bullet2[i].rc.right, _bullet2[i].rc.bottom);
	}
}

void MainGame4::fireBullet(int playerNum)
{
	if (playerNum == 1)
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (_bullet1[i].fire)continue;

			_bullet1[i].fire = true;
			_bullet1[i].rc = RectMakeCenter
			(
				_player1.rc.right + 10,
				_player1.rc.top + (_player1.rc.bottom - _player1.rc.top) / 2 , 10, 10
			);
			break;
		}
	}
	else if (playerNum == 2)
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (_bullet2[i].fire)continue;

			_bullet2[i].fire = true;
			_bullet2[i].rc = RectMakeCenter
			(
				_player2.rc.left - 10 ,
				_player2.rc.top + (_player2.rc.bottom - _player2.rc.top) / 2, 10, 10
			);
			break;
		}
	}
	
}








MainGame4::MainGame4()
{
}


MainGame4::~MainGame4()
{
}
