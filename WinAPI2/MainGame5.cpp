#include "stdafx.h"
#include "MainGame5.h"



HRESULT MainGame5::init()
{
	GameNode::init();
	_stage1 = new GImage;
	_stage1->init("Resources/Images/FindPicture/Stage1.bmp", WINSIZE_X, WINSIZE_Y);
	_stage2 = new GImage;
	_stage2->init("Resources/Images/FindPicture/Stage2.bmp", WINSIZE_X, WINSIZE_Y);
	_gameMode = stage1;
	checkStage1[0].rc = RectMakeCenter(1120, 250, 70, 30);
	checkStage1[1].rc = RectMakeCenter(1100, 210, 70, 30);
	checkStage1[2].rc = RectMakeCenter(1000, 160, 100, 30);
	checkStage1[3].rc = RectMakeCenter(900, 280, 70, 30);
	for (int i = 0; i < 4; i++)
	{
		checkStage1[i].anser = false;
	}
	checkStage2[0].rc = RectMakeCenter(1175, 135, 70, 70);
	checkStage2[1].rc = RectMakeCenter(1225, 328, 50, 50);
	checkStage2[2].rc = RectMakeCenter(1012, 240, 50, 30);
	checkStage2[3].rc = RectMakeCenter(700, 164, 70, 30);
	checkStage2[4].rc = RectMakeCenter(1025, 658, 50, 50);
	checkStage2[5].rc = RectMakeCenter(944, 711, 50, 50);
	checkStage2[6].rc = RectMakeCenter(675, 531, 70, 50);
	for (int i = 0; i < 7; i++)
	{
		checkStage2[i].anser = false;
	}

	_timer = 10000;
	_delay = 500;
	_gameOver = false;
	_stage1Clear = false;
	_gameClear = false;
	_minus = false;
	
	return S_OK;
}

void MainGame5::release(void)
{
	GameNode::release();
	SAFE_DELETE(_stage1);
	SAFE_DELETE(_stage2);
}

void MainGame5::update(void)
{
	GameNode::update();


	
	
	if (_timer <= 0)
	{
		_gameMode = gameOver;
	}

	if (_gameMode == stage1 && !_gameOver)
	{
		if (!_stage1Clear)
		{
			_timer--;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&checkStage1[i].rc, _ptMouse) && !checkStage1[i].anser)
				{
					checkStage1[i].anser = true;
					_timer += 1000;
				}
				else
				{
					_minus = true;
				}
			}
			if (_minus)
			{
				_timer -= 500;
				_minus = false;
			}
			
		}

		if (checkStage1[0].anser &&checkStage1[1].anser&&checkStage1[2].anser&&checkStage1[3].anser)
		{
			_stage1Clear = true;
			_timer = _timer;
			_delay--;
			if (_delay < 0)
			{
				_delay = 0;
			}
		}
	
		if (_stage1Clear && _delay <=0 )
		{
			_gameMode = stage2;
		}


	}

	else if (_gameMode == stage2 && !_gameOver)
	{
		
		if (!_gameClear)
		{
			_timer--;
			_delay = 500;
		}
		

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 7; i++)
			{
				if (PtInRect(&checkStage2[i].rc, _ptMouse) && !checkStage2[i].anser)
				{
					checkStage2[i].anser = true;
					_timer += 500;
				}
			}

		}

		if (checkStage2[0].anser &&checkStage2[1].anser&&checkStage2[2].anser&&checkStage2[3].anser)
		{
			_gameClear = true;
			_timer = _timer;
			_delay--;
			if (_delay < 0)
			{
				_delay = 0;
			}
		}

		if (_gameClear && _delay <= 0)
		{
			_gameMode = gameClear;
		}

	}
	

}

void MainGame5::render(HDC hdc)
{
	HDC memDC;
	memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	char strTimer[128];


	if (_gameMode == stage1)
	{
		_stage1->render(memDC, 0, 0);
		for (int i = 0; i < 4; i++)
		{
			if (checkStage1[i].anser)
			{
				
				HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
				HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, myBrush);
				HPEN MyPen = CreatePen(PS_SOLID, 7, RGB(255, 0, 0));
				HPEN OldPen = (HPEN)SelectObject(memDC, MyPen);

				DrawEllipseMake(memDC, checkStage1[i].rc);
				DrawEllipseMake(memDC, checkStage1[i].rc);

				SelectObject(memDC, oldBrush);
				DeleteObject(myBrush);
				SelectObject(memDC, OldPen);
				DeleteObject(MyPen);
			}
		}
		


	}
	
	else if (_gameMode == stage2)
	{
		_stage2->render(memDC, 0, 0);

		for (int i = 0; i < 7; i++)
		{
			if (checkStage2[i].anser)
			{

				HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
				HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, myBrush);
				HPEN MyPen = CreatePen(PS_SOLID, 7, RGB(255, 0, 0));
				HPEN OldPen = (HPEN)SelectObject(memDC, MyPen);

				DrawEllipseMake(memDC, checkStage2[i].rc);
				DrawEllipseMake(memDC, checkStage2[i].rc);

				SelectObject(memDC, oldBrush);
				DeleteObject(myBrush);
				SelectObject(memDC, OldPen);
				DeleteObject(MyPen);
			}
		}



	}

	else if (_gameMode == gameOver)
	{
		_stage1->release();
		_stage2->release();
	}

	else if (_gameMode == gameClear)
	{
		_stage1->release();
		_stage2->release();
	}

	wsprintf(strTimer, "남은 시간: %2d", _timer / 100);
	TextOut(memDC, 50, 100, strTimer, strlen(strTimer));




	this->getDoubleBuffer()->render(hdc, 0, 0);


}


