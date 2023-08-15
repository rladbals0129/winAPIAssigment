#include "stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Snake.h"
HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("���ĸ�", "Resources/Images/ShootingGame/Enemy/JellyFish.bmp", 0.f, 0.f,
		1140, 47,
		19, 1, true, RGB(255, 0, 255));
	setMinion();

	IMAGEMANAGER->addFrameImage("��idle", "Resources/Images/ShootingGame/Enemy/snakeIdle.bmp",
		0.f, 0.f, 88, 189,
		2, 4,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��attack", "Resources/Images/ShootingGame/Enemy/snakeAttack.bmp",
		0.f, 0.f, 135, 190,
		3, 4,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��move", "Resources/Images/ShootingGame/Enemy/snakeMove.bmp",
		0.f, 0.f, 140, 189,
		3, 4,
		true,
		RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��die", "Resources/Images/ShootingGame/Enemy/snakeDie.bmp",
		0.f, 0.f,
		38, 32,
		true,
		RGB(255, 0, 255));
	setSnake();
	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
}

void EnemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
		

	}
	for (_viSnake = _vSnake.begin(); _viSnake != _vSnake.end(); ++_viSnake)
	{
		(*_viSnake)->update();
	}
}

void EnemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	for (_viSnake = _vSnake.begin(); _viSnake != _vSnake.end(); ++_viSnake)
	{
		(*_viSnake)->render();
	}
}

void EnemyManager::setMinion(void)
{
	POINT center = { 640, 400 };
	int numRows = 3;
	int numCols = 5;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion(MovePattern::CIRCLE_PATTERN);// Minion ��ü ����
			// �� �߰� �� �ʱ�ȭ
			float startAngle = static_cast<float>(i * numCols + j) / (numRows * numCols) * (2 * PI); 
			jellyFish->init("���ĸ�", center, startAngle);
			
			_vMinion.push_back(jellyFish); // ���Ϳ� �� ��ü �߰�
		}
	}


	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion(MovePattern::BOUNCE_PATTERN);
			jellyFish->init("���ĸ�", PointMake(250 + j * 200, 100 + i * 100));
			_vMinion.push_back(jellyFish);
		}

	}
	

	
}

void EnemyManager::setSnake(void)
{
	Enemy* snake;
	snake = new Snake;
	snake->init("��move", PointMake(400.f, 400.f));
	
	_vSnake.push_back(snake);
}
