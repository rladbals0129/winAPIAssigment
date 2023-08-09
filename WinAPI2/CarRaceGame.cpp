#include "stdafx.h"
#include "CarRaceGame.h"



HRESULT CarRaceGame::init(void)
{
	GameNode::init(true);
	
	IMAGEMANAGER->addImage("��", "Resources/Images/0703Race/Rode.bmp",
		840, 650);
	IMAGEMANAGER->addImage("����", "Resources/Images/0703Race/PlayerCar.bmp",
		WINSIZE_X / 2 - 50, WINSIZE_Y - 300,
		50,125,
		true,
		RGB(255,0,255));
	IMAGEMANAGER->addImage("ȫ�ذ�����", "Resources/Images/0703Race/skill1.bmp",
		420, 0,
		200, 1000,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Resources/Images/0703Race/skill2.bmp",
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
			IMAGEMANAGER->addImage("������", "Resources/Images/0703Race/enemyR.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		case 1:
			IMAGEMANAGER->addImage("�ʷ���", "Resources/Images/0703Race/enemyG.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		case 2:
			IMAGEMANAGER->addImage("�Ķ���", "Resources/Images/0703Race/enemyB.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		case 3:
			IMAGEMANAGER->addImage("�����", "Resources/Images/0703Race/enemy.bmp",
				_enemy[i].posX, _enemy[i].posY,
				100, 125,
				true,
				RGB(255, 0, 255));
			break;
		}
	}
	
	

	IMAGEMANAGER->addImage("�����", "Resources/Images/0703Race/speedmeter1.bmp",
		WINSIZE_X - 350, WINSIZE_Y - 350,
		300, 300,
		true,
		RGB(182, 185, 183));
	_plSpeed = 0;

	_speedPanel.startX = IMAGEMANAGER->findImage("�����")->getX() + 150;
	_speedPanel.startY = IMAGEMANAGER->findImage("�����")->getY() + 150;

	_redSea = false;
	_booster = false;
	_shield = false;
	//cout << _speedPanel.startX << " " << _speedPanel.startY;
	_maxSpeed = 50.0f;
	return S_OK;
}

void CarRaceGame::release(void)
{
	
	IMAGEMANAGER->deleteImage("�����");
	IMAGEMANAGER->deleteImage("������");
	IMAGEMANAGER->deleteImage("�Ķ���");
	IMAGEMANAGER->deleteImage("�����");
	IMAGEMANAGER->deleteImage("����");
	IMAGEMANAGER->deleteImage("ȫ�ذ�����");
	IMAGEMANAGER->deleteImage("����");

}

void CarRaceGame::update(void)
{
	GameNode::update();
	//=================�÷��̾� ��Ʈ��================
	
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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && IMAGEMANAGER->findImage("����")->getX() > 100)
	{
		IMAGEMANAGER->findImage("����")->setX(IMAGEMANAGER->findImage("����")->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && IMAGEMANAGER->findImage("����")->getX() < 700)
	{
		IMAGEMANAGER->findImage("����")->setX(IMAGEMANAGER->findImage("����")->getX() + 5.0f);
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




	_car.rc = { (long)IMAGEMANAGER->findImage("����")->getX(),
	(long)IMAGEMANAGER->findImage("����")->getY(),
	(long)IMAGEMANAGER->findImage("����")->getX() + 50,
	(long)IMAGEMANAGER->findImage("����")->getY() + 125 };

	//=========================================================================
	
	//===============================�����=====================================
	_speedPanel.endX = cosf(REDIAN((_car.speed * 4) - 225.0f)) * 100 + _speedPanel.startX;
	_speedPanel.endY = sinf(REDIAN((_car.speed * 4) - 225.0f)) * 100 + _speedPanel.startY;



	//========================================================================== 

	//==============��=====================
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
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); //�簢���ȿ� ������ �귯���� ä��� �Լ�
//=================================================
	
	
	wsprintf(strScore, "Score : %d", _score);
	TextOut(getMemDC(), 1000, 50, strScore, strlen(strScore));
	IMAGEMANAGER->loopRender("��", getMemDC(),
		&RectMake(0, 0, 840, WINSIZE_Y),
		0, _plSpeed);
	IMAGEMANAGER->render("����", getMemDC(),
		IMAGEMANAGER->findImage("����")->getX(),
		IMAGEMANAGER->findImage("����")->getY());	
	IMAGEMANAGER->render("������", getMemDC(), _enemy[0].posX, _enemy[0].posY);
	IMAGEMANAGER->render("�ʷ���", getMemDC(), _enemy[1].posX, _enemy[1].posY);
	IMAGEMANAGER->render("�Ķ���", getMemDC(), _enemy[2].posX, _enemy[2].posY);
	IMAGEMANAGER->render("�����", getMemDC(), _enemy[3].posX, _enemy[3].posY);

	if (_redSea)
	{
		IMAGEMANAGER->alphaRender("ȫ�ذ�����", getMemDC(),330,0,_alphaRed);
	}
	if (_shield)
	{
		IMAGEMANAGER->alphaRender("����",getMemDC(), _car.rc.left - 70,
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

	IMAGEMANAGER->render("�����", getMemDC(), IMAGEMANAGER->findImage("�����")->getX(),
		IMAGEMANAGER->findImage("�����")->getY());


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


