#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"
class ShootingMap : public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);
	//virtual void fight(void);
};

