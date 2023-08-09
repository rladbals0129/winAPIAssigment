#pragma once
#include "GameNode.h"
#define ENEMYMAX 4
#define PI 3.141592
#define REDIAN(dig) ((dig) * PI) / 180.0f

struct CAR
{
	RECT rc;
	float speed;
	bool isAccel;
};

struct ENEMY
{
	RECT rc;
	float acceleration;
	float speed;
	float posX;
	float posY;	
	int cnt;

};

struct SPEEDPANEL
{
	float startX, startY;
	float endX, endY;
};

class CarRaceGame : public GameNode
{
private:
	CAR _car;
	ENEMY _enemy[ENEMYMAX];
	SPEEDPANEL _speedPanel;
	RECT _collider;
	float _plSpeed;
	float _enSpeed;
	float _maxSpeed;

	bool _redSea;
	int _redSeaCnt;
	int _alphaRed;

	bool _shield;
	int _shieldCnt;
	int _alphaShield;

	bool _booster;
	int _boosterCnt;
	
	int _score;
	char strScore[128];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void crossingTheRedSea();
	void shield();
	void booster();
};

