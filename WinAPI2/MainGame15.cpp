#include "stdafx.h"
#include "MainGame15.h"

HRESULT MainGame15::init(void)
{
	GameNode::init(true);
	
	/*Idle = new GImage;
	Idle->init("Resources/Images/0629Player/Idle.bmp",
		WINSIZE_X / 2- 200, WINSIZE_Y / 2 - 200,
		3600, 800,
		9, 2,
		true,
		RGB(255, 0, 255));
	Move = new GImage;
	Move->init("Resources/Images/0629Player/Move.bmp",
		WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
		4800, 800,
		12, 2,
		true,
		RGB(255, 0, 255));
	Attack = new GImage;
	Attack->init("Resources/Images/0629Player/Attack.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2 - 200,
		8300, 900,
		10, 2,
		true,
		RGB(255, 0, 255));*/

	IMAGEMANAGER->addFrameImage("���", "Resources/Images/0629Player/Idle.bmp",
		WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
		3600, 800,
		9, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�̵�", "Resources/Images/0629Player/Move.bmp",
		WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200,
		4800, 800,
		12, 2,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "Resources/Images/0629Player/Attack.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2 - 200,
		8300, 900,
		10, 2,
		true,
		RGB(255, 0, 255));
	for (int i = 0; i < 9; i++)
	{
		if (i < 4)
		{ //0 ��� 1�̵� 2 ��� 3�밢����� 4 ������� 5�������� 6 �¸����� 7 ��ų 8�й�
			_button[i] = RectMakeCenter(100, 100 + (i * 150), 100, 80);
		}
		else if (i == 4)
		{
			_button[i] = RectMakeCenter(WINSIZE_X / 2, 100, 100, 80);
		}
		else
		{
			_button[i] = RectMakeCenter(WINSIZE_X - 100, 100 + ((i-5) * 150), 100, 80);
		}
	}
	
	
	return S_OK;
}

void MainGame15::release(void)
{
	IMAGEMANAGER->deleteImage("���");
	IMAGEMANAGER->deleteImage("�̵�");
	IMAGEMANAGER->deleteImage("����");
}

void MainGame15::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cnt = 0;
		_idx = 0;
		_isLeft = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cnt = 0;
		_idx = 0;
		_isLeft = false;
	}

	if (_state == IDLE)
	{	
		idle();
	}
	if (_state == MOVE)
	{	
		move();		
	}
	if (_state == ATTACK)
	{
		attack();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 9; i++)
		{
			if (PtInRect(&_button[i], _ptMouse))
			{
				switch (i)
				{
				case 0:
					_cnt = 0;
					_idx = 0;
					_state = IDLE;
					break;
				case 1:
					_cnt = 0;
					_idx = 0;
					_state = MOVE;
					break;
				case 2:
					_cnt = 0;
					_idx = 0;
					_state = ATTACK;
					break;
				case 3:
					
					break;
				case 4:
				
					break;
				case 5:
				
					break;
				case 6:
					
					break;
				case 7:
				
					break;
				case 8:
				
					break;
				default:
					break;
				}
			}
		
		}
	}

	
}

void MainGame15::render(void)
{
	char strPT[128];
	char strBtn[256];
	char test1212[128];
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	wsprintf(strPT, "X : %d Y: %d", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 20, 10, strPT, strlen(strPT));

	wsprintf(test1212, "state : %d ", _state);
	TextOut(getMemDC(), 50, 40, test1212, strlen(test1212));
	//SetTextColor(hdc, RGB(255, 255, 255));
	for (int i = 0; i < 9; i++)
	{
		DrawRectMake(getMemDC(), _button[i]);
		switch (i)
		{
		case 0:
			wsprintf(strBtn, "���");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn),
				strBtn, strlen(strBtn));
			break;
		case 1:
			wsprintf(strBtn, "�̵�");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn),
				strBtn, strlen(strBtn));
			break;
		case 2:
			wsprintf(strBtn, "���");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn),
				strBtn, strlen(strBtn));
			break;
		case 3:
			wsprintf(strBtn, "�밢�����");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn),
				strBtn, strlen(strBtn));
			break;
		case 4:
			wsprintf(strBtn, "�������");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn), 
				strBtn, strlen(strBtn));
			break;
		case 5:
			wsprintf(strBtn, "��������");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn),
				strBtn, strlen(strBtn));
			break;
		case 6:
			wsprintf(strBtn, "�¸�");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn),
				strBtn, strlen(strBtn));
			break;
		case 7:
			wsprintf(strBtn, "��ų");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn), 
				strBtn, strlen(strBtn));
			break;
		case 8:
			wsprintf(strBtn, "�й�");
			TextOut(getMemDC(), (_button[i].left + _button[i].right) / 2 - strlen(strBtn) * 4,
				(_button[i].top + _button[i].bottom) / 2 - strlen(strBtn), 
				strBtn, strlen(strBtn));
			break;
		default:
			break;
		}
	}
	if (_state == IDLE)
	{
		IMAGEMANAGER->frameRender("���", getMemDC(), IMAGEMANAGER->findImage("���")->getX(),
			IMAGEMANAGER->findImage("���")->getY());
	}
	if (_state == MOVE)
	{
		IMAGEMANAGER->frameRender("�̵�", getMemDC(), IMAGEMANAGER->findImage("�̵�")->getX(),
			IMAGEMANAGER->findImage("�̵�")->getY());
	}
	if (_state == ATTACK)
	{
		IMAGEMANAGER->frameRender("����", getMemDC(), 
		IMAGEMANAGER->findImage("����")->getX() - IMAGEMANAGER->findImage("����")->getFrameWidth() / 2,
		IMAGEMANAGER->findImage("����")->getY());
		

	}
	this->getBackBuffer()->render(getHDC());
}

void MainGame15::idle()
{
	
	if (_isLeft)
	{
		_cnt++;

		IMAGEMANAGER->findImage("���")->setFrameY(1);

		if (_cnt % 8 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 10;
			}

			IMAGEMANAGER->findImage("���")->setFrameX(_idx);
		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("���")->setFrameY(0);

		if (_cnt % 8 == 0)
		{
			_idx++;
			if (_idx > 10)
			{
				_idx = 0;
			}

			IMAGEMANAGER->findImage("���")->setFrameX(_idx);
		}

	}

}

void MainGame15::move(void)
{
	if (_isLeft)
	{
		_cnt++;

		IMAGEMANAGER->findImage("�̵�")->setFrameY(1);

		if (_cnt % 5 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 12;
			}

			IMAGEMANAGER->findImage("�̵�")->setFrameX(_idx);
		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("�̵�")->setFrameY(0);

		if (_cnt % 5 == 0)
		{
			_idx++;
			if (_idx > 12)
			{
				_idx = 0;
			}

			IMAGEMANAGER->findImage("�̵�")->setFrameX(_idx);
		}

	}

}

void MainGame15::attack(void)
{
	if (_isLeft)
	{
		_cnt++;

		IMAGEMANAGER->findImage("����")->setFrameY(1);

		if (_cnt % 5 == 0)
		{
			_idx--;
			if (_idx < 0)
			{
				_idx = 10;
			}

			IMAGEMANAGER->findImage("����")->setFrameX(_idx);
		}

	}
	else
	{
		_cnt++;

		IMAGEMANAGER->findImage("����")->setFrameY(0);

		if (_cnt % 5 == 0)
		{
			_idx++;
			if (_idx > 10)
			{
				_idx = 0;
			}

			IMAGEMANAGER->findImage("����")->setFrameX(_idx);
		}

	}


}
