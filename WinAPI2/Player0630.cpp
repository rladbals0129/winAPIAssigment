#include "stdafx.h"
#include "Player0630.h"



HRESULT Player0630::init(void)
{
	IMAGEMANAGER->addFrameImage("Idle", "Resources/Images/0630Playerr/PlayerIdle.bmp",
		WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
		700, 100,
		14, 2,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ӹ�", "Resources/Images/0630Playerr/TabletFaces.bmp",
		IMAGEMANAGER->findImage("Idle")->getX() + 20, IMAGEMANAGER->findImage("Idle")->getY(),
		20, 20);

	IMAGEMANAGER->addImage("�⺻ǥ��", "Resources/Images/0630Playerr/idleFace.bmp",
		IMAGEMANAGER->findImage("�Ӹ�")->getX(), IMAGEMANAGER->findImage("�Ӹ�")->getY(),
		20, 20,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Move", "Resources/Images/0630Playerr/PlayerRun.bmp",
		WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
		1250, 100,
		25, 2,
		true,
		RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Jump", "Resources/Images/0630Playerr/PlayerJump.bmp",
		WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
		1150, 100,
		23,2,
		true,
		RGB(255, 0, 255));


	_isLeft = false;
	_posX = 0.0f;
	return S_OK;
}

void Player0630::release(void)
{
	IMAGEMANAGER->deleteImage("�Ӹ�");
	IMAGEMANAGER->deleteImage("�⺻ǥ��");
	IMAGEMANAGER->deleteImage("Idle");
	IMAGEMANAGER->deleteImage("Move");
	IMAGEMANAGER->deleteImage("Jump");

}

void Player0630::update(void)
{
	_posX = IMAGEMANAGER->findImage("Move")->getX();
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_currentState = MOVE;
		if (_currentState == MOVE)
		{
			move();

			IMAGEMANAGER->findImage("Move")->setX(_posX - 4.0f);
		//	IMAGEMANAGER->findImage("�Ӹ�")->setX(IMAGEMANAGER->findImage("Move")->getX() + 20);
		//	IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());

		}
	//	IMAGEMANAGER->findImage("Idle")->setX(IMAGEMANAGER->findImage("Idle")->getX() - 8.0f);
	//	IMAGEMANAGER->findImage("�Ӹ�")->setX(IMAGEMANAGER->findImage("Idle")->getX() + 20);
	//	IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());
	}
	if(KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_currentState = IDLE;

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_currentState = MOVE; 
		if (_currentState == MOVE)
		{
			move();
			IMAGEMANAGER->findImage("Move")->setX(_posX + 4.0f);
		//	IMAGEMANAGER->findImage("�Ӹ�")->setX(IMAGEMANAGER->findImage("Move")->getX() + 20);
		//	IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());

		}
		//IMAGEMANAGER->findImage("Idle")->setX(IMAGEMANAGER->findImage("Idle")->getX() + 8.0f);
	//	IMAGEMANAGER->findImage("�Ӹ�")->setX(IMAGEMANAGER->findImage("Idle")->getX() + 20);
	//	IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_currentState = IDLE;
	}
	if (_currentState == IDLE)
	{
		idle();
	}

	////IMAGEMANAGER->findImage("Idel")->setX(IMAGEMANAGER->findImage("Move")->getX());
	////IMAGEMANAGER->findImage("Idel")->setY(IMAGEMANAGER->findImage("Move")->getY());

	
}


void Player0630::render(void)
{
	if (_currentState == IDLE)
	{
		IMAGEMANAGER->frameRender("Idle", getMemDC(), IMAGEMANAGER->findImage("Move")->getX(),
			IMAGEMANAGER->findImage("Move")->getY());
		IMAGEMANAGER->render("�Ӹ�", getMemDC(), IMAGEMANAGER->findImage("�Ӹ�")->getX(), IMAGEMANAGER->findImage("�Ӹ�")->getY());

		IMAGEMANAGER->render("�⺻ǥ��", getMemDC(), IMAGEMANAGER->findImage("�⺻ǥ��")->getX(), IMAGEMANAGER->findImage("�⺻ǥ��")->getY());

	}

	if (_currentState == MOVE)
	{
		IMAGEMANAGER->frameRender("Move", getMemDC(), IMAGEMANAGER->findImage("Move")->getX(),
			IMAGEMANAGER->findImage("Move")->getY());
		IMAGEMANAGER->render("�Ӹ�", getMemDC(), IMAGEMANAGER->findImage("�Ӹ�")->getX(), IMAGEMANAGER->findImage("�Ӹ�")->getY());

		IMAGEMANAGER->render("�⺻ǥ��", getMemDC(), IMAGEMANAGER->findImage("�⺻ǥ��")->getX(), IMAGEMANAGER->findImage("�⺻ǥ��")->getY());
	}

	if (_currentState == JUMP)
	{

	}
}

void Player0630::idle(void)
{
	if (_isLeft)
	{
		_cnt++;

		IMAGEMANAGER->findImage("Idle")->setFrameY(1);
		IMAGEMANAGER->findImage("�Ӹ�")->setX(_posX +10);
		IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());

		if (_cnt % 4 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 14;
			}

			IMAGEMANAGER->findImage("Idle")->setFrameX(_idx);
		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("Idle")->setFrameY(0);
		IMAGEMANAGER->findImage("�Ӹ�")->setX(_posX + 20);
		IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());
		if (_cnt % 4 == 0)
		{
			_idx++;
			if (_idx > 14)
			{
				_idx = 0;
			}

			IMAGEMANAGER->findImage("Idle")->setFrameX(_idx);
		}

	}
	cout << "cnt : " << _cnt << "      ";
	cout << "idx : " << _idx << endl;
}

void Player0630::move(void)
{
	if (_isLeft)
	{
		_cnt++;

		IMAGEMANAGER->findImage("Move")->setFrameY(1);
		IMAGEMANAGER->findImage("�Ӹ�")->setX(_posX + 4);
		IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());

		if (_cnt % 4 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 25;
			}

			IMAGEMANAGER->findImage("Move")->setFrameX(_idx);
		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("Move")->setFrameY(0);
		IMAGEMANAGER->findImage("�Ӹ�")->setX(_posX+24);
		IMAGEMANAGER->findImage("�⺻ǥ��")->setX(IMAGEMANAGER->findImage("�Ӹ�")->getX());
		if (_cnt % 4 == 0)
		{
			_idx++;
			if (_idx > 25)
			{
				_idx = 0;
			}

			IMAGEMANAGER->findImage("Move")->setFrameX(_idx);
		}

	}
}

void Player0630::jump(void)
{

}

/*
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _player.checkJump)
	{

		_player.jump -= 50;
		_miniPlayer.rc.top -= 5;
		_miniPlayer.rc.bottom -= 5;
	}

	if (!IntersectRect(&_check, &_player.rc, &_collider))
	{
		_player.checkJump = false;
		_player.jump += _player.gravity;

		if (_player.jump > 0)
		{
			_player.jump = 0;

		}
		_player.rc.top += _player.gravity;
		_player.rc.bottom += _player.gravity;


	}
	else
	{
		_player.checkJump = true;
		_miniPlayer.rc.bottom = 790;
		_miniPlayer.rc.top = 770;
	}

	_player.rc.top += _player.jump;
	_player.rc.bottom += _player.jump;
*/


Player0630::Player0630()
{
}


Player0630::~Player0630()
{
}
