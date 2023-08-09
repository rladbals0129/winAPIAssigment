#pragma once
#include "GameNode.h"
class MainGame15 : public GameNode
{
private:
	enum GAMEMODE 
	{
		lobby,game
	};

	enum STATE
	{
		IDLE,
		MOVE,
		ATTACK
	};
	GAMEMODE _gameMode;

	STATE _state;

	int _cnt;
	int _idx;
	bool _isLeft;
	RECT _button[9];

	//bool _idle;
	//bool _move;
	//bool _attack;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void idle(void);
	void move(void);
	void attack(void);
};

