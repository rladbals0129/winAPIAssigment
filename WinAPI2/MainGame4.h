#pragma once
#include "GameNode.h"

#define BULLET_MAX 10
#define PLAYER1_NUM 1
#define PLAYER2_NUM 2

struct tagBullet
{
	bool fire;
	RECT rc;
	int dmg;
};

struct Player
{
	RECT rc;
	RECT hpbar;
	int hp;
	int speed;
	bool die;
};

class MainGame4 : public GameNode
{
private:
	Player _player1;
	Player _player2;
	tagBullet _bullet1[BULLET_MAX];
	tagBullet _bullet2[BULLET_MAX];
	RECT _colider;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void fireBullet(int playerNum);
};

/*

���� 2. 1 VS 1 Ⱦ��ũ�� ���� ����

- ���ʿ� 1P / �����ʿ� 2P

- ü�� �ٴ� ��������ó�� �߾��� �������� �¿� ��ġ
�� ü�� �� ���¿� ���� �� / �� / ��

- ���� ���ϸ� �������� �翬�� ü���� �����ؾ� �Ѵ�.

�� �ʼ� :
��ų 2�� + 2�� = 4��
�������� 2�� ������ �´�.

*/