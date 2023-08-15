#pragma once
#include "GameNode.h"
#include "Enemy.h"

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

	vEnemy _vSnake;
	viEnemy _viSnake;

	/*
	vEnemy ������
	....���
	
	
	*/
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void setSnake(void);
};

