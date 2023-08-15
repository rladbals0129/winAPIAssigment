#pragma once
#include "Enemy.h"
enum MovePattern
{
	CIRCLE_PATTERN,
	BOUNCE_PATTERN,
	RANDOM_PATTERN
};
class Minion : public Enemy
{
private:
	
	MovePattern _movePattern;
	int _speedX;
	int _speedY;
public:

	void update(void);
	void render(void);

	void move();
	void animation(void);
	

	Minion(MovePattern movePattern = CIRCLE_PATTERN);
	~Minion();
};
