#pragma once
#include "Enemy.h"

class Snake : public Enemy
{
private:
	enum SnakeState
	{
		STATE_IDLE,
		STATE_ATTACK,
		STATE_MOVE,
		STATE_DIE
	};
	SnakeState _state;

public:
	void update(void);
	void render(void);

	void move();
	void animation(void);

	void setSnakeState(SnakeState* state) { _state = *state; }

	Snake();
	~Snake();
};

//void setSnakeState(SnakeState* state) { _state = *state; }