#include "stdafx.h"
#include "MainGame11.h"


HRESULT MainGame11::init()
{
	GameNode::init(true);
	
	IMAGEMANAGER->addImage("퍼즐", "Resources/Images/Slide/Slide.bmp", 600, 600);
	//_pzImage->init("Resources/Images/Slide/Slide.bmp", 600, 600);
	_gameMode = game;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_rc[i * 3 + j] = RectMakeCenter(100 + j * 200, 100 + i * 200, 200, 200);
			_rcIdx[i * 3 + j] = i * 3 + j;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_rcAns[i * 3 + j] = RectMakeCenter(100 + j * 200, 100 + i * 200, 200, 200);
			_rcAnsIdx[i * 3 + j] = i * 3 + j;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		_endCheck[i] = false;
	}

	for (int i = 0; i < 9; i++)
	{
		int num1 = RND->getInt(9);
		int num2 = RND->getInt(9);

		int temp = _rcIdx[num1];
		_rcIdx[num1] = _rcIdx[num2];
		_rcIdx[num2] = temp;

	}
	_clearRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y/2, 600, 600);
	_cntA = 0;
	_alphaA = 255;
	return S_OK;
}

void MainGame11::release(void)
{
	IMAGEMANAGER->deleteImage("퍼즐");
}

void MainGame11::update(void)
{
	GameNode::update();
	if (_gameMode == game)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			for (int i = 0; i < 9; i++)
			{
				if (_rcIdx[i] == 8 && i % 3 != 0)
				{
					int temp = _rcIdx[i];
					_rcIdx[i] = _rcIdx[i - 1];
					_rcIdx[i - 1] = temp;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			for (int i = 8; i >= 0; i--)
			{
				if (_rcIdx[i] == 8 && i % 3 != 2)
				{
					int temp = _rcIdx[i];
					_rcIdx[i] = _rcIdx[i + 1];
					_rcIdx[i + 1] = temp;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			for (int i = 0; i < 9; i++)
			{
				if (_rcIdx[i] == 8 && i > 2)
				{
					int temp = _rcIdx[i];
					_rcIdx[i] = _rcIdx[i - 3];
					_rcIdx[i - 3] = temp;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			for (int i = 8; i >= 0; i--)
			{
				if (_rcIdx[i] == 8 && i < 6)
				{
					int temp = _rcIdx[i];
					_rcIdx[i] = _rcIdx[i + 3];
					_rcIdx[i + 3] = temp;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			for (int i = 0; i < 7; i++)
			{
				_rcIdx[i] = _rcAnsIdx[i];	
			}
			_rcIdx[7] = 8;
			_rcIdx[8] = 7;

		}
		for (int i = 0; i < 8; i++)
		{
			if(_rcIdx[i] == _rcAnsIdx[i])
			{
				_endCheck[i] = true;
			}
			else if (_rcIdx[i] != _rcAnsIdx[i])
			{
				_endCheck[i] = false;
			}
			
		}

		if (_endCheck[0] && _endCheck[1] && _endCheck[2] && _endCheck[3] && _endCheck[4] &&
			_endCheck[5] && _endCheck[6] && _endCheck[7])
		{
			_cntA++;
			if (_cntA % 3 == 0)
			{
				_alphaA-=5;
				if (_alphaA <= 0)
				{
					_alphaA = 0;
					_gameMode = end;
				}
			}
			

		}

	}

	else if (_gameMode == end)
	{

		



		if (_cntAnsAlpha < 255)
		{
			_cntAnsA++;
		}
		
		if (_cntAnsA % 3 == 0)
		{
			_cntAnsAlpha+=5;
			if (_cntAnsAlpha >= 255)
			{
				_cntAnsAlpha = 255;
			}
		}


	}
	
}

void MainGame11::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	
	//_bgImage->render(memDC, 0, 0);
	
	//680
	//============================
	
	if (_gameMode == game)
	{
		for (int i = 0; i < 9; i++)
		{
			IMAGEMANAGER->alphaRender("퍼즐", getMemDC(), _rcAns[i].left, _rcAns[i].top, _rcAns[_rcAnsIdx[i]].left, _rcAns[_rcAnsIdx[i]].top, 200, 200, _alphaA);
			//_pzImage->alphaRender(memDC, _rcAns[i].left, _rcAns[i].top, _rcAns[_rcAnsIdx[i]].left, _rcAns[_rcAnsIdx[i]].top, 200, 200, _alphaA);
		}
		for (int i = 0; i < 9; i++)
		{
			//DrawRectMake(memDC, _rc[i]);
			if (_rcIdx[i] != 8)
			{
				IMAGEMANAGER->alphaRender("퍼즐", getMemDC(), _rc[i].left + 620, _rc[i].top, _rc[_rcIdx[i]].left, _rc[_rcIdx[i]].top, 200, 200, _alphaA);

			//	_pzImage->alphaRender(memDC, _rc[i].left + 620, _rc[i].top, _rc[_rcIdx[i]].left, _rc[_rcIdx[i]].top, 200, 200, _alphaA);
			}
			//이미지를 잘라 그리겠다. 랙트 지점에서 win출력 시작 , 자를 이미지의 위치값, 크기
		
		}
	}
	else if (_gameMode == end)
	{
		IMAGEMANAGER->alphaRender("퍼즐", getMemDC(), _clearRC.left, _clearRC.top, _cntAnsAlpha);
		//_pzImage->alphaRender(memDC, _clearRC.left, _clearRC.top, _cntAnsAlpha);
	}
	
	this->getBackBuffer()->render(getHDC());


	//=============================


}

void MainGame11::shuffleMap()
{

}


/*while(_cnt > 0)
	{
		_index = RND->getInt(9);

		if (_checkIndex[_index]) continue;

		_checkIndex[_index] = true;
		_pzImage->render(memDC, _rc1[_index].left + 580, _rc1[_index].top, _rc1[_index].left, _rc1[_index].top, 200, 200);
		_cnt--;
	}*/