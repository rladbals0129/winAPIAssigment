#include "stdafx.h"
#include "MainGame14.h"

HRESULT MainGame14::init()
{
	GameNode::init(true);
	IMAGEMANAGER->addFrameImage("����", "Resources/Images/Zero/zeroAttack.bmp", WINSIZE_X / 2 - 200, WINSIZE_Y / 2 + 200,
		5100, 180,
		34, 2,
		true, RGB(255, 0, 255));
	return S_OK;
}

void MainGame14::release(void)
{
	IMAGEMANAGER->deleteImage("����");
}

void MainGame14::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "���� Ȯ��", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		IMAGEMANAGER->findImage("����")->setX(IMAGEMANAGER->findImage("����")->getX() - 8.0f);
		//_zeroAttack->setX(_zeroAttack->getX() - 8.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		IMAGEMANAGER->findImage("����")->setX(IMAGEMANAGER->findImage("����")->getX() + 8.0f);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isAttack = !_isAttack;
	}	
	
	if (_isAttack && !_isLeft)
	{
		_count++;
		IMAGEMANAGER->findImage("����")->setFrameY(0);
		//_zeroAttack->setFrameY(0);
		if (_count % 2 == 0)
		{
			_index++;
			if (_index > 34)
			{
				_index = 0;
			}
			IMAGEMANAGER->findImage("����")->setFrameX(_index);
			//_zeroAttack->setFrameX(_index);
		}		
	}
	else if (_isAttack && _isLeft)
	{
		_count++;
		IMAGEMANAGER->findImage("����")->setFrameY(1);
		if (_count % 2 == 0)
		{
			_index--;
			if (_index < 0)
			{
				_index = 34;
			}
			IMAGEMANAGER->findImage("����")->setFrameX(_index);
		}
	}
	if (!_isAttack && !_isLeft)
	{
		_index = 0;
		IMAGEMANAGER->findImage("����")->setFrameY(0);
		IMAGEMANAGER->findImage("����")->setFrameX(_index);
	}
	else if (!_isAttack && _isLeft)
	{
		_index = 34;
		IMAGEMANAGER->findImage("����")->setFrameY(1);
		IMAGEMANAGER->findImage("����")->setFrameX(_index);
	}
}

void MainGame14::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X,WINSIZE_Y,WHITENESS);
	IMAGEMANAGER->frameRender("����", getMemDC(), IMAGEMANAGER->findImage("����")->getX(), IMAGEMANAGER->findImage("����")->getY());
	this->getBackBuffer()->render(getHDC());
}
