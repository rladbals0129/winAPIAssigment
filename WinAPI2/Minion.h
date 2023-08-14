#pragma once
#include "Enemy.h"
class Minion : public Enemy
{
private:

public:

	void update(void);
	void render(void);

	void move();
	void animation(void);

	Minion();
	~Minion();
};
