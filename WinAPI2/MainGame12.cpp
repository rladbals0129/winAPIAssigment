#include "stdafx.h"
#include "MainGame12.h"

HRESULT MainGame12::init()
{
	GameNode::init(true);
	_wordRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 1280, 800);
	_miniRC = RectMake(1024, 640, 256, 160);
	_panalRC = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, WINSIZE_X / 2, WINSIZE_Y / 2);
	IMAGEMANAGER->addImage("배경", "Resources/Images/BackGround/Back.bmp", WINSIZE_X, WINSIZE_Y);
//	_worldImg->init("Resources/Images/BackGround/Back.bmp", WINSIZE_X, WINSIZE_Y);
	/*_miniImg = new GImage;
	_miniImg->init("Resources/Images/BackGround/Back.bmp", 256, 160);
	*/

	_player.rc = RectMakeCenter(128, 80, 50, 100);
	_player.speed = 5.0f;
	_player.checkJump = false;

	_player.gravity = 5.0f;
	_player.jump = 0.0f;
	_collider = RectMake(0, WINSIZE_Y - 80, WINSIZE_X, 80);

	_miniPlayer.rc = RectMakeCenter(1048, 780, 10, 20);
	_miniPlayer.gravity = 1.0f;
	_miniPlayer.jump = 0.0f;
	_miniPlayer.speed = 1.0f;
	//_miniPlayer.rc = RectMakeCenter()

	return S_OK;
}

void MainGame12::release(void)
{
	IMAGEMANAGER->deleteImage("배경");
}

void MainGame12::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _player.rc.right)
	{
		_player.rc.left += _player.speed;
		_player.rc.right += _player.speed;

		_miniPlayer.rc.left += _miniPlayer.speed;
		_miniPlayer.rc.right += _miniPlayer.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _player.rc.left)
	{
		_player.rc.left -= _player.speed;
		_player.rc.right -= _player.speed;


		_miniPlayer.rc.left -= _miniPlayer.speed;
		_miniPlayer.rc.right -= _miniPlayer.speed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _player.checkJump)
	{
		
		_player.jump -= 0.1;
		if (_player.jump > -50)
		{
			_player.jump = -50;
		}
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
	
	//IntersectRect(&_colider, &_playerRC, &_enemy[i].rc)

}

void MainGame12::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	IMAGEMANAGER->render("배경",getMemDC(), _wordRC.left, _wordRC.top);
//	_worldImg->render(memDC,_wordRC.left,_wordRC.top);
	DrawRectMake(getMemDC(), _player.rc);
	IMAGEMANAGER->alphaRender("배경", getMemDC(), _miniRC.left, _miniRC.top, 256, 160, 0, 0, 1280, 800, 150);
	//_worldImg->alphaRender(memDC, _miniRC.left, _miniRC.top, 256, 160, 0, 0, 1280, 800, 150);
	//_miniImg->alphaRender(memDC, _miniRC.left, _miniRC.top, 150);
	DrawRectMake(getMemDC(), _miniPlayer.rc);
//	DrawRectMake(memDC, _panalRC);
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		DrawRectMake(getMemDC(), _collider);
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->alphaRender("배경",getMemDC(), _panalRC.left, _panalRC.top, 640, 400,0,0, 1280, 800, 150);
	}
	
	this->getBackBuffer()->render(getHDC());
}

/*

과제2. 미니맵 만들기

- 2가지 버전

- 플레이어의 움직임을 미니맵에서도 확인할 수 있어야 한다.  --> 클리핑을 사용해보자
ㄴ 1.화면에 표시되는 작은 GUI형태의 미니맵
ㄴ 2.화면위에 그려지는 전체화면 미니맵 (TAB키 누르면 블랜딩패널)

*/