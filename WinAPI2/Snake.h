#pragma once
#include "Enemy.h"
enum SnakeState
{
	STATE_IDLE,
	STATE_ATTACK,
	STATE_MOVE,
	STATE_DIE
};
class Snake : public Enemy
{
private:
	SnakeState _state;
public:

	void update(void);
	void render(void);

	void move();
	void animation(void);

	Snake();
	~Snake();
};

