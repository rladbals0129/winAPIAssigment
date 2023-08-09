#include "stdafx.h"
#include "MainGame2.h"


HRESULT MainGame2::init(void)
{
	GameNode::init();
	_bgImage = new GImage;
	_bgImage->init("Resources/Images/BackGround/BackGround.bmp", WINSIZE_X, WINSIZE_Y);
	for (int i = 0; i < 3; i++)
	{
		_plImage[i] = new GImage;
	}
	_plImage[0]->init("Resources/Images/Mole/Mole1.bmp", 56, 47,true,RGB(255,0,255));
	_plImage[1]->init("Resources/Images/Mole/Mole2.bmp", 56, 47, true, RGB(255, 0, 255));
	_plImage[2]->init("Resources/Images/Mole/Mole3.bmp", 56, 47, true, RGB(255, 0, 255));

	_msImage[0] = new GImage;
	_msImage[1] = new GImage;

	_msImage[0]->init("Resources/Images/Hammer/Hammer1.bmp", 67, 67, true, RGB(255, 0, 255));
	_msImage[1]->init("Resources/Images/Hammer/Hammer2.bmp", 67, 67, true, RGB(255, 0, 255));

	_currentRect = CURRENTRECT_NULL;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_rc[i * 4 + j] = RectMakeCenter(100 + j * 200, 200 + i * 200, 100, 100);
		}
	}
	//_mousePT = { _ptMouse.x,_ptMouse.y };
	_mouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 67, 67);
	_index = 0;
	_count = 0;
	_score = 0;
	_time = RND->getFromIntTo(30, 60);

	_bIsSelected = false;
	_bIsOnceCheck = false;

	


	return S_OK;
}

void MainGame2::release(void)
{
	GameNode::release();
	SAFE_DELETE(_bgImage);
	for (int i = 0; i < 3; i++)
	{
		SAFE_DELETE(_plImage[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		SAFE_DELETE(_msImage[i]);
	}
	
}

void MainGame2::update(void)
{
	GameNode::update();
	
	_mouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 67, 67);
	ShowCursor(false);
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc[_index], _ptMouse) && !_bIsOnceCheck)
		{
			_score += 100;
			_bIsOnceCheck = true;
		}
	}

	if (!_bIsSelected)
	{
		_count++;
		if (_count % _time == 0)
		{
			_count = 0;
			_index = RND->getInt(16);
			_currentRect = (CURRENT_RECT1)_index;
			_bIsSelected = true;
		}
	}
	else
	{
		_count++;
		if (_count % _time == 0)
		{
			_bIsOnceCheck = false;
			_bIsSelected = false;
			_currentRect = CURRENTRECT_NULL;
			_time = RND->getFromIntTo(30, 60);
			_index = 100;
		}
	}


}

void MainGame2::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //사각형안에 영역을 브러쉬로 채우는 함수
	//======================================================
		_bgImage->render(memDC, 0, 0);

	
	for (int i = 0; i < 16; i++)
	{
		_plImage[0]->render(memDC, _rc[i].left, _rc[i].top);
	}

	if (_bIsSelected)
	{
		for (int i = 0; i < 16; i++)
		{
			_plImage[1]->render(memDC, _rc[_index].left, _rc[_index].top);
		}
	}
	if (_bIsOnceCheck)
	{
		for (int i = 0; i < 16; i++)
		{
			_plImage[2]->render(memDC, _rc[_index].left, _rc[_index].top);
		}
	}
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < 16; i++)
		{
			
			Rectangle(memDC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
		}
		DrawRectMake(memDC, _mouse);

	}
	if (!_bIsOnceCheck)
	{
		_msImage[0]->render(memDC, _mouse.left, _mouse.top);
	}
	else if (_bIsOnceCheck)
	{
		_msImage[1]->render(memDC, _mouse.left, _mouse.top);
	}
	
	//====================================================================
	this->getDoubleBuffer()->render(hdc, 0, 0);

	char strScore[128];

	wsprintf(strScore, "Score : %d", _score);
	TextOut(hdc, 50, 50, strScore, strlen(strScore));

	

}
