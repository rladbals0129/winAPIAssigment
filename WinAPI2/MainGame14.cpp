#include "stdafx.h"
#include "MainGame14.h"

HRESULT MainGame14::init()
{
	GameNode::init(true);
	IMAGEMANAGER->addFrameImage("제로", "Resources/Images/Zero/zeroAttack.bmp", WINSIZE_X / 2 - 200, WINSIZE_Y / 2 + 200,
		5100, 180,
		34, 2,
		true, RGB(255, 0, 255));
	return S_OK;
}

void MainGame14::release(void)
{
	IMAGEMANAGER->deleteImage("제로");
}

void MainGame14::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		IMAGEMANAGER->findImage("제로")->setX(IMAGEMANAGER->findImage("제로")->getX() - 8.0f);
		//_zeroAttack->setX(_zeroAttack->getX() - 8.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		IMAGEMANAGER->findImage("제로")->setX(IMAGEMANAGER->findImage("제로")->getX() + 8.0f);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isAttack = !_isAttack;
	}	
	
	if (_isAttack && !_isLeft)
	{
		_count++;
		IMAGEMANAGER->findImage("제로")->setFrameY(0);
		//_zeroAttack->setFrameY(0);
		if (_count % 2 == 0)
		{
			_index++;
			if (_index > 34)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("제로")->setFrameX(_index);
			//_zeroAttack->setFrameX(_index);
		}		
	}
	else if (_isAttack && _isLeft)
	{
		_count++;
		IMAGEMANAGER->findImage("제로")->setFrameY(1);
		if (_count % 2 == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = 34;
			}
			IMAGEMANAGER->findImage("제로")->setFrameX(_index);
		}
	}
	if (!_isAttack && !_isLeft)
	{
		_index = 0;
		IMAGEMANAGER->findImage("제로")->setFrameY(0);
		IMAGEMANAGER->findImage("제로")->setFrameX(_index);
	}
	else if (!_isAttack && _isLeft)
	{
		_index = 34;
		IMAGEMANAGER->findImage("제로")->setFrameY(1);
		IMAGEMANAGER->findImage("제로")->setFrameX(_index);
	}
}

void MainGame14::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X,WINSIZE_Y,WHITENESS);
	IMAGEMANAGER->frameRender("제로", getMemDC(), IMAGEMANAGER->findImage("제로")->getX(), IMAGEMANAGER->findImage("제로")->getY());
	this->getBackBuffer()->render(getHDC());
}
