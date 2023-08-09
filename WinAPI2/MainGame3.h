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
과제 1. 종스크롤 슈팅 게임

- 플레이어 체력바 설정
ㄴ 적과 충돌하면 체력이 감소되고 체력바는 3단계로 처리
ㄴ 빨 / 주 / 초

- 플레이어가 발사한 총알로 적을 제거

과제 2. 1 VS 1 횡스크롤 슈팅 게임

- 왼쪽에 1P / 오른쪽에 2P

- 체력 바는 대전게임처럼 중앙을 기준으로 좌우 배치
ㄴ 체력 바 상태에 따라 녹 / 노 / 빨

- 공격 당하면 당한쪽은 당연히 체력이 감소해야 한다.

※ 필수 : 
스킬 2개 + 2개 = 4개
아이템을 2종 구현해 온다.

*/
