#include "stdafx.h"
#include "Minion.h"




HRESULT Minion::init(const char* imageName, POINT position)
{
	Enemy::init(imageName, position);
	_hp = 100;
	//cout << _hp << endl;
	_speedX = 2;
	_speedY = 2;
	return S_OK;
}

HRESULT Minion::init(const char* imageName, POINT position, float startAngle)
{
	Enemy::init(imageName, position, startAngle);
	_hp = 100;
	//cout << _hp << endl;
	_speedX = 2;
	_speedY = 2;
	return S_OK;
}

void Minion::update(void)
{
	move();
}

void Minion::render(void)
{
	Enemy::render();
//	IMAGEMANAGER->render("체력", getMemDC(), _rc.left, _rc.bottom);
//	IMAGEMANAGER->render("체력바", getMemDC(), _rc.left+40, _rc.bottom);
	
}

void Minion::move()
{
	switch (_movePattern) 
	{
		case CIRCLE_PATTERN: 
		{
			radius = 300.0f;
			_angle += 0.01f;
			_x = _center.x + radius * cos(_angle + _startAngle);
			_y = _center.y + radius * sin(_angle + _startAngle);

			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
		}
		case BOUNCE_PATTERN:
		{
		
			_x += _speedX;
			_y += _speedY;
			if (_x < 0 || _x > WINSIZE_X) _speedX = -_speedX;
			if (_y < 0 || _y > WINSIZE_Y) _speedY = -_speedY;
			break;
		}
		case CENTER_CIRCLE_PATTERN:
		{
			radius = 100.0f;
			_angle += 0.05f;
			_x = _center.x + radius * cos(_angle + _startAngle);
			_y = _center.y + radius * sin(_angle+ _startAngle);

			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
		}
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}




Minion::Minion(MovePattern movePattern) : _movePattern(movePattern) 
{

}

Minion::~Minion()
{
	//!Do Nothing
}



/*
과제1. 움직이는 적 패턴 추가
 - 움직임을 서로 다르게 해온다.
  1. 원을 그리며 이동
  2. WINSIZE_X WINSIZE_Y 에 튕기면 반대방향으로 튕김
  3. 3초에 한번 플레이어의 위치를 추적


과제2. 로켓 무장 변경 추가
 - f1: 일반미사일
 - f2: 산탄
 - f3: 미니로켓생성
 - f4: 실드
 - f5: 유도미사일
 - f6: 레이저
 - f7: 블랙홀
 ㄴ 영향을 받는 적과 아닌 적으로 구분
 ㄴ 블랙홀의 중점에 가까운 적일수록 슼리이 끝나면 팅겨나가는 관성이 강해진다


다른클래스에 이식할 수 있게 잘 구조적으로 재활용 될 수 있게 잘 파츠화 시켜놓아라



*/

/*


*/