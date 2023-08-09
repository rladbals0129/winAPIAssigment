#include "stdafx.h"
#include "CarRaceGame.h"



HRESULT CarRaceGame::init(void)
{
	GameNode::init(true);
	
	IMAGEMANAGER->addImage("길", "Resources/Images/0703Race/Rode.bmp",
		840, 650);
	IMAGEMANAGER->addImage("내차", "Resources/Images/0703Race/PlayerCar.bmp",
		WINSIZE_X / 2 - 50, WINSIZE_Y - 300,
		50,125,
		true,
		RGB(255,0,255));
	IMAGEMANAGER->addImage("홍해가르기", "Resources/Images/0703Race/skill1.bmp",
		420, 0,
		200, 1000,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드", "Resources/Images/0703Race/skill2.bmp",
		200, 200,
		true,
		RGB(255, 0, 255));
	for (int i = 0; i < ENEMYMAX; i++)
	{
		_enemy[i].posX = 150 + (i*150);
		_enemy[i].posY = WINSIZE_Y - 300;

		switch (i)
		{
		case 0:
			IMAGEMANAGER->addImage("빨간적", "Resources/Images/0703Race/enemyR.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		case 1:
			IMAGEMANAGER->addImage("초록적", "Resources/Images/0703Race/enemyG.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		case 2:
			IMAGEMANAGER->addImage("파란적", "Resources/Images/0703Race/enemyB.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		case 3:
			IMAGEMANAGER->addImage("노란적", "Resources/Images/0703Race/enemy.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		}
	}
	
	

	IMAGEMANAGER->addImage("계기판", "Resources/Images/0703Race/speedmeter1.bmp",
		WINSIZE_X - 350, WINSIZE_Y - 350,
		300, 300,
		true,
		RGB(182, 185, 183));
	_plSpeed = 0;

	_speedPanel.startX = IMAGEMANAGER->findImage("계기판")->getX() + 150;
	_speedPanel.startY = IMAGEMANAGER->findImage("계기판")->getY() + 150;

	_redSea = false;
	_booster = false;
	_shield = false;
	//cout << _speedPanel.startX << " " << _speedPanel.startY;
	_maxSpeed = 50.0f;
	return S_OK;
}

void CarRaceGame::release(void)
{
	
	IMAGEMANAGER->deleteImage("계기판");
	IMAGEMANAGER->deleteImage("빨간적");
	IMAGEMANAGER->deleteImage("파란적");
	IMAGEMANAGER->deleteImage("노란적");
	IMAGEMANAGER->deleteImage("내차");
	IMAGEMANAGER->deleteImage("홍해가르기");
	IMAGEMANAGER->deleteImage("쉴드");

}

void CarRaceGame::update(void)
{
	GameNode::update();
	//=================플레이어 컨트롤================
	
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _car.speed < _maxSpeed)
	{
		_car.speed += 0.2f;
		_car.isAccel = true;
		if (_car.speed > _maxSpeed)
		{
			_car.speed = _maxSpeed;
		}

	
	}
	
	


	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_car.isAccel = false;
	}
	if (!_car.isAccel && _car.speed > 0.2f)
	{
		_car.speed -= 0.2f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _car.speed>0.4f)
	{
		_car.speed -= 0.4f;
	}
	_score += _car.speed;
	_plSpeed -= _car.speed;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && IMAGEMANAGER->findImage("내차")->getX() > 100)
	{
		IMAGEMANAGER->findImage("내차")->setX(IMAGEMANAGER->findImage("내차")->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && IMAGEMANAGER->findImage("내차")->getX() < 700)
	{
		IMAGEMANAGER->findImage("내차")->setX(IMAGEMANAGER->findImage("내차")->getX() + 5.0f);
	}
	if (KEYMANAGER->isOnceKeyDown(0x51) || KEYMANAGER->isOnceKeyDown(0x71))
	{
		crossingTheRedSea();
	}
	if (KEYMANAGER->isOnceKeyDown(0x57) || KEYMANAGER->isOnceKeyDown(0x77))
	{
		shield();
	}
	if (KEYMANAGER->isOnceKeyDown(0x45) || KEYMANAGER->isOnceKeyDown(0x65))
	{
		booster();
	}
	
	if (_redSea)
	{
		_redSeaCnt++;
	}
		
	_alphaRed = RND->getInt(255);
	
	if (_redSeaCnt % 300 == 0)
	{
		_redSea = false;
		_redSeaCnt = 0;
	}

	if (_shield)
	{
		_shieldCnt++;
	}
	_alphaShield = RND->getInt(255);

	if (_shieldCnt % 300 == 0)
	{
		_shield = false;
		_shieldCnt = 0;
	}

	if (_booster)
	{
		_boosterCnt++;
	}

	if (_boosterCnt % 300 == 0)
	{
		_car.isAccel = false;
		_booster = false;
		_boosterCnt = 0;
		_maxSpeed = 50.0f;
		
		
	}
	cout << _car.speed << endl;




	_car.rc = { (long)IMAGEMANAGER->findImage("내차")->getX(),
	(long)IMAGEMANAGER->findImage("내차")->getY(),
	(long)IMAGEMANAGER->findImage("내차")->getX() + 50,
	(long)IMAGEMANAGER->findImage("내차")->getY() + 125 };

	//=========================================================================
	
	//===============================계기판=====================================
	_speedPanel.endX = cosf(REDIAN((_car.speed * 4) - 225.0f)) * 100 + _speedPanel.startX;
	_speedPanel.endY = sinf(REDIAN((_car.speed * 4) - 225.0f)) * 100 + _speedPanel.startY;



	//========================================================================== 

	//==============적=====================
	for (int i = 0; i < ENEMYMAX; i++)
	{
		switch (i)
		{
		case 0:
			_enemy[i].cnt++;
			if (_enemy[i].cnt % 2 == 0 && _enemy[i].acceleration < 40.0f)
			{
				_enemy[i].acceleration += 0.5f;
			}
			_enemy[i].speed = _car.speed - _enemy[i].acceleration;

			_enemy[i].posY += _enemy[i].speed;
			break;
		case 1:
			_enemy[i].cnt++;

			if (_enemy[i].cnt % 2 == 0 && _enemy[i].acceleration < 45.0f)
			{
				_enemy[i].acceleration += 0.4f;
			}
			_enemy[i].speed = _car.speed - _enemy[i].acceleration;

			_enemy[i].posY += _enemy[i].speed;
			break;
		case 2:
			_enemy[i].cnt++;

			if (_enemy[i].cnt % 2 == 0 && _enemy[i].acceleration < 47.0f)
			{
				_enemy[i].acceleration += 0.3f;
			}
			_enemy[i].speed = _car.speed - _enemy[i].acceleration;

			_enemy[i].posY += _enemy[i].speed;
			break;
		case 3:
			_enemy[i].cnt++;

			if (_enemy[i].acceleration < 46.0f)
			{
				_enemy[i].acceleration += 0.2f;
			}
			_enemy[i].speed = _car.speed - _enemy[i].acceleration;

			_enemy[i].posY += _enemy[i].speed;
			break;
		}
	
		if (_enemy[i].posY > WINSIZE_Y+300)
		{
			_enemy[i].posY = -200;
		}
		//cout << " i : " << _enemy[i].posY;
		if (_enemy[i].cnt % 3 == 0)
		{
			_enemy[i].posX += RND->getFromIntTo(-5, 5);
		}
	
		if (_enemy[i].posX > 700)
		{
			_enemy[i].posX -= 10;
		}
		if (_enemy[i].posX < 100)
		{
			_enemy[i].posX += 10;
		}

		_enemy[i].rc = RectMakeCenter(_enemy[i].posX + 50, _enemy[i].posY + 50, 50, 125);

		if (!_shield)
		{
			if (IntersectRect(&_collider, &_car.rc, &_enemy[i].rc) && _car.speed > 0.0f)
			{
				_car.speed -= 0.7f;
			}
		}
		

		//if()

	}
	//cout << endl;

	//cout << _enemy.speed << endl;

	
}

void CarRaceGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //사각형안에 영역을 브러쉬로 채우는 함수
//=================================================
	
	
	wsprintf(strScore, "Score : %d", _score);
	TextOut(getMemDC(), 1000, 50, strScore, strlen(strScore));
	IMAGEMANAGER->loopRender("길", getMemDC(),
		&RectMake(0, 0, 840, WINSIZE_Y),
		0, _plSpeed);
	IMAGEMANAGER->render("내차", getMemDC(),
		IMAGEMANAGER->findImage("내차")->getX(),
		IMAGEMANAGER->findImage("내차")->getY());	
	IMAGEMANAGER->render("빨간적", getMemDC(), _enemy[0].posX, _enemy[0].posY);
	IMAGEMANAGER->render("초록적", getMemDC(), _enemy[1].posX, _enemy[1].posY);
	IMAGEMANAGER->render("파란적", getMemDC(), _enemy[2].posX, _enemy[2].posY);
	IMAGEMANAGER->render("노란적", getMemDC(), _enemy[3].posX, _enemy[3].posY);

	if (_redSea)
	{
		IMAGEMANAGER->alphaRender("홍해가르기", getMemDC(),330,0,_alphaRed);
	}
	if (_shield)
	{
		IMAGEMANAGER->alphaRender("쉴드",getMemDC(), _car.rc.left - 70,
			_car.rc.top- 70, _alphaShield);
	}
		
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		DrawRectMake(getMemDC(), _car.rc);
		for (int i = 0; i < ENEMYMAX; i++)
		{
			DrawRectMake(getMemDC(), _enemy[i].rc);
		}
	}

	IMAGEMANAGER->render("계기판", getMemDC(), IMAGEMANAGER->findImage("계기판")->getX(),
		IMAGEMANAGER->findImage("계기판")->getY());


	LineMake(getMemDC(), _speedPanel.startX, _speedPanel.startY,
		_speedPanel.endX, _speedPanel.endY);

//=================================================

	this->getBackBuffer()->render(getHDC());

}

void CarRaceGame::crossingTheRedSea()
{
	_redSea = true;
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (_enemy[i].posX < 420 && _enemy[i].posX > 200)
		{
			_enemy[i].posX = 210;
		}
		if (_enemy[i].posX >= 420 && _enemy[i].posX < 650)
		{
			_enemy[i].posX += 640;
		}
	}
}

void CarRaceGame::shield()
{
	_shield = true;
}

void CarRaceGame::booster()
{
	_booster = true;
	_maxSpeed = 70.0f;
}


