#pragma once
#include "GameNode.h"
struct PLAYER
{
	RECT rc;
	float speed;
	float jump;

	float gravity;
	bool checkJump;
};

class MainGame12 : public GameNode
{
private:
	RECT _wordRC;
	RECT _miniRC;
	RECT _panalRC;

	RECT _collider;
	RECT _miniCollider;

	RECT _check;
	RECT _miniCheck;

	PLAYER _player;
	PLAYER _miniPlayer;

public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
};

