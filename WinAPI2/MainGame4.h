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

과제 2. 1 VS 1 횡스크롤 슈팅 게임

- 왼쪽에 1P / 오른쪽에 2P

- 체력 바는 대전게임처럼 중앙을 기준으로 좌우 배치
ㄴ 체력 바 상태에 따라 녹 / 노 / 빨

- 공격 당하면 당한쪽은 당연히 체력이 감소해야 한다.

※ 필수 :
스킬 2개 + 2개 = 4개
아이템을 2종 구현해 온다.

*/