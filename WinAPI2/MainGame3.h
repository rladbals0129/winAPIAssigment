#pragma once
#include "GameNode.h"

#define ENEMY_MAX 50
#define BULLET_MAX 10
#define PLAYER_SPEED 5

enum GameMode
{
	LOBBY,
	GAME,
	END
};

struct tagBullet
{
	RECT rc;
	bool fire;
};

struct tagEnemy
{
	RECT rc;
	int speed;
	bool die;
};

class MainGame3 : public GameNode 
{
private:
	GameMode _gameMode;
	tagBullet _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];

	RECT _playerRC;
	RECT _playerHPBAR;
	RECT _colider;

	bool _playerDIE;
	int _playerHP;
	

	

	//time_t startTime;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void fireBullet(void);
	

};

/*
���� 1. ����ũ�� ���� ����

- �÷��̾� ü�¹� ����
�� ���� �浹�ϸ� ü���� ���ҵǰ� ü�¹ٴ� 3�ܰ�� ó��
�� �� / �� / ��

- �÷��̾ �߻��� �Ѿ˷� ���� ����

���� 2. 1 VS 1 Ⱦ��ũ�� ���� ����

- ���ʿ� 1P / �����ʿ� 2P

- ü�� �ٴ� ��������ó�� �߾��� �������� �¿� ��ġ
�� ü�� �� ���¿� ���� �� / �� / ��

- ���� ���ϸ� �������� �翬�� ü���� �����ؾ� �Ѵ�.

�� �ʼ� : 
��ų 2�� + 2�� = 4��
�������� 2�� ������ �´�.

*/
