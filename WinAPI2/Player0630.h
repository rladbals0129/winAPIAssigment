#pragma once
#include "GameNode.h"

enum STATE {
	IDLE,MOVE,
	JUMP,SLAP
};

class Player0630 : public GameNode
{
private:
	STATE _currentState;
	int _cnt;
	int _idx;
	bool _isLeft;

	float _posX;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void idle(void);
	void move(void);
	void jump(void);

	Player0630();
	~Player0630();
};

