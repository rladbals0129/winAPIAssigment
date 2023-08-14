#include "stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"

HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/ShootingGame/Enemy/JellyFish.bmp", 0.f, 0.f,
		1140, 47,
		19, 1, true, RGB(255, 0, 255));
	setMinion();
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
}

void EnemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
}

void EnemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion; // Minion 객체 생성
			// 적 추가 및 초기화
			jellyFish->init("해파리", PointMake(250 + j * 200, 100 + i * 100));
			_vMinion.push_back(jellyFish); // 벡터에 적 객체 추가
		}
	}
}
