#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy; 
	//타입 재정의: 여러 종류의 적을 관리하기 위한
	//Enemy포인터 벡터
	typedef vector<Enemy*>::iterator viEnemy;
private:
	vEnemy _vMinion; //고정된 부모 객체를 기반으로
	//파생될 적을 저장할 벡터
	viEnemy _viMinion;
	int* _minionHP;

	vEnemy _vSnake;
	viEnemy _viSnake;

	/*
	vEnemy 슬라임
	....등등
	
	
	*/
private:
	//총알 충돌
	RECT _colider;
	MissileM1* _missileM1;
	Beam* _beam;

private:

	//ui
	RECT _hpBar;
	RECT _currentHpBar;
	//int* _hp = nullptr;
	//float* _hpPosX = nullptr;
	//float* _hpPosY = nullptr;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void setSnake(void);

	void removeMinion(int arrNum);

	vector<Enemy*> getMinions(void) { return _vMinion; }
	vector<Enemy*> getSnake(void) { return _vSnake; }
	//void setMissileM1(MissileM1* missileM1) { _missileM1 = missileM1; }
	//void setBeam(Beam* beam) { _beam = beam; }

	//void checkCollisions();
};



/*
	
*/
