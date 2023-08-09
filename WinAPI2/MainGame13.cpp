#include "stdafx.h"
#include "MainGame13.h"

HRESULT MainGame13::init()
{
	GameNode::init(true);
	_currentX = WINSIZE_X / 2;
	_currentY = WINSIZE_Y;
	_redius = 100;
	_creat.startX = WINSIZE_X / 2;
	_creat.startY = WINSIZE_Y - 50;
	
	_creat.angleMove = -35.0f;
	for (int i = 0; i < WORM_MAX; i++)
	{
		_worm[i].fire = false;
		_worm[i].speed = 4.0f;
		_worm[i].collisionX = 1;
		_worm[i].collisionY = 1;
	}
	_cnt = 0;
	_createStop = 0;
	_stop = 0;


	//==========item=========
	for (int i = 0; i < ITEM_MAX; i++)
	{
		_item[i].idxNum = 0;
		_item[i].spon = false;
			 
		_item[i].rndL = 0;
		_item[i].rndT = 0;
		_item[i].sizeX = 0;
		_item[i].sizeY = 0;
		_item[i].eat = false;
	}


	return S_OK;
}

void MainGame13::release(void)
{
}

void MainGame13::update(void)
{
	GameNode::update();
	_creat.endX = cosf(REDIAN(_creat.angleMove)) * 100 + _creat.startX;
	_creat.endY = sinf(REDIAN(_creat.angleMove)) * 100 + _creat.startY;
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{	
		_worm[0].angle-=3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_worm[0].angle+=3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		sponItem();
	}
	if (_stop == 0)
	{
		_worm[0].rc.left += (int)(cosf(REDIAN(_worm[0].angle))   * 	_worm[0].speed * _worm[0].collisionX);
		_worm[0].rc.right += (int)(cosf(REDIAN(_worm[0].angle))   * _worm[0].speed * _worm[0].collisionX);
		_worm[0].rc.top += (int)(sinf(REDIAN(_worm[0].angle))    * _worm[0].speed * _worm[0].collisionY);
		_worm[0].rc.bottom += (int)(sinf(REDIAN(_worm[0].angle)) * _worm[0].speed * _worm[0].collisionY);


		if (_worm[0].rc.left < 0)
		{
			_worm[0].rc.right = 50;
			_worm[0].rc.left = 0;

			_worm[0].collisionX = -_worm[0].collisionX;
		}
		if (_worm[0].rc.top < 0)
		{
			_worm[0].rc.top = 0;
			_worm[0].rc.bottom = 50;

			_worm[0].collisionY = -_worm[0].collisionY;
		}
		if (_worm[0].rc.right > WINSIZE_X)
		{
			_worm[0].rc.right = WINSIZE_X - 50;
			_worm[0].rc.left = WINSIZE_X;

			_worm[0].collisionX = -_worm[0].collisionX;
		}
		if (_worm[0].rc.bottom > WINSIZE_Y)
		{
			_worm[0].rc.top = WINSIZE_Y - 50;
			_worm[0].rc.bottom = WINSIZE_Y;

			_worm[0].collisionY = -_worm[0].collisionY;
		}
		_worm[0].centerX = (_worm[0].rc.left + _worm[0].rc.right) / 2;
		_worm[0].centerY = (_worm[0].rc.top + _worm[0].rc.bottom) / 2;
		//생성주기
		if (_createStop == WORM_MAX)
		{
			_cnt = 0;
		}
		else {
			_cnt++;

		}
		if (_cnt % 9 == 0)
		{
			fireWorm();

			for (int i = WORM_MAX-1; i > 0; i--)
			{
				if (!_worm[i].fire)continue;
				_worm[i].centerX = (_worm[i].rc.left + _worm[i].rc.right) / 2;// - cosf(REDIAN(_worm[i - 1].angle)) * 50;
				_worm[i].centerY = (_worm[i].rc.top + _worm[i].rc.bottom) / 2;// - sinf(REDIAN(_worm[i - 1].angle)) * 50;

			}
			_createStop++;
		}

		
		for (int i = WORM_MAX - 1; i > 0; i--)
		{
			//if (_item[_item[i].idxNum].eat) continue;

			_worm[i].rc.left = _worm[i - 1].centerX - 25;
			_worm[i].rc.right = _worm[i - 1].centerX + 25;
			_worm[i].rc.top   = _worm[i - 1].centerY - 25;
			_worm[i].rc.bottom = _worm[i - 1].centerY + 25;
		}

		//=======아이템=======
		for (int i = 0; i < ITEM_MAX; i++)
		{
			if (IntersectRect(&_collider, &_worm[0].rc, &_item[i].rc))// && !_item[i].eat
			{
				_item[i].eat = true;
				_item[i].spon = false;

				
				_worm[_item[i].idxNum].rc.left -= _item[i].sizeX / 2;
				_worm[_item[i].idxNum].rc.right += _item[i].sizeX / 2;
				_worm[_item[i].idxNum].rc.top -= _item[i].sizeY / 2;
				_worm[_item[i].idxNum].rc.bottom += _item[i].sizeY / 2;
				
				/*_worm[_item[i].idxNum].rc.left = _item[i].sizeX / 2 -25;
				_worm[_item[i].idxNum].rc.right = _item[i].sizeX / 2 - 25;
				_worm[_item[i].idxNum].rc.top = _item[i].sizeY / 2 - 25;
				_worm[_item[i].idxNum].rc.bottom = _item[i].sizeY / 2 - 25;*/
			}
		}

		for (int i = 0; i < ITEM_MAX; i++)
		{
			
		}

	}
	
}

void MainGame13::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	_strNum[128];

	for (int i = WORM_MAX-1; i > 0; i--)
	{
		if (!_worm[i].fire) continue;
		Ellipse(getMemDC(), _worm[i].rc.left, _worm[i].rc.top, _worm[i].rc.right, _worm[i].rc.bottom);
		wsprintf(_strNum, " %d ", i);
		TextOut(getMemDC(), _worm[i].centerX, _worm[i].centerY, _strNum, strlen(_strNum));
		
	}
	wsprintf(_strNum, " %d ", 0);
	TextOut(getMemDC(), _worm[0].centerX, _worm[0].centerY, _strNum, strlen(_strNum));
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (!_item[i].spon)continue;
		Ellipse(getMemDC(), _item[i].rc.left, _item[i].rc.top, _item[i].rc.right, _item[i].rc.bottom);
	}


	this->getBackBuffer()->render(getHDC());
}


void MainGame13::fireWorm(void)
{
	for (int i = 0; i < WORM_MAX; i++)
	{
		if (_worm[i].fire)continue;

		_worm[i].fire = true;
		_worm[i].rc = RectMakeCenter(_creat.endX, _creat.endY, 50, 50);
		//_worm[i].angle = _creat.angleMove;
		break;
	}

}

void MainGame13::sponItem(void)
{

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (_item[i].spon) continue;

	  /*if (_item[i].rndL == _item[i - 1].rndL && _item[i].rndT == _item[i - 1].rndT &&
			_item[i].sizeX == _item[i - 1].sizeX && _item[i].sizeY == _item[i - 1].sizeY)
		{
			i++;
		}*/

		_item[i].spon = true;
		_item[i].rndL = RND->getFromIntTo(200, 600);
		_item[i].rndT = RND->getFromIntTo(200, 600);
		_item[i].sizeX = RND->getFromIntTo(100, 190);
		_item[i].sizeY = RND->getFromIntTo(100, 190);
		_item[i].rc = RectMakeCenter(_item[i].rndL, _item[i].rndT, _item[i].sizeX, _item[i].sizeY);
		_item[i].idxNum = RND->getInt(20);
		break;
	}
	

}




/*
과제1. 지렁이만들기

- 지렁이는 구슬이 꼬리를 물고 이어지는 형태
ㄴ 각 구슬마다 번호를 표기한다.

- 지렁이는 화면밖의 무작위 위치에서 등장을 한다.

- 특별한 키 입력이 없어도 지렁이는 화면안에서 움직인다.

- 벽에 부딪히면 팅겨 나가야 하고 왼쪽 / 오른쪽 방향키로 조종이 가능해야함

- 따라오는 구슬은 머리가 방향을 튼다고 같이 틀면 안되고 머리가 있던 위치까지
와서 방향을 전환한다.

- 임의의 숫자가 표시된 아이템이 게임이 시작되면 생성되고 지렁이가 아이템을
먹으면 해당하는 번호의 구슬이 커진다.
*/