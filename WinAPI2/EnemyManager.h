#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy; 
	//Ÿ�� ������: ���� ������ ���� �����ϱ� ����
	//Enemy������ ����
	typedef vector<Enemy*>::iterator viEnemy;
private:
	vEnemy _vMinion; //������ �θ� ��ü�� �������
	//�Ļ��� ���� ������ ����
	viEnemy _viMinion;
	int* _minionHP;

	vEnemy _vSnake;
	viEnemy _viSnake;

	/*
	vEnemy ������
	....���
	
	
	*/
private:
	//�Ѿ� �浹
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
