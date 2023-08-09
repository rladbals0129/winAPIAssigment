#include "stdafx.h"
#include "Player.h"



//Player::Player()
//{
//}
//
//
//Player::~Player()
//{
//}

HRESULT Player::init()
{
	_rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 30, 80, 60);


	return S_OK;
}

void Player::release(void)
{
	
}

void Player::update(void)
{
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_rc.left -= 3;
		_rc.right -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rc.left += 3;
		_rc.right += 3;
	}

}

void Player::render(HDC hdc)
{
	DrawRectMake(hdc, _rc);
}


