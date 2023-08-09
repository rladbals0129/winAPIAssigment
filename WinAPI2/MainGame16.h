#pragma once
#include "GameNode.h"
#include "Player0630.h"
class MainGame16 : public GameNode
{
private:
	Player0630* _player;

	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//void idle(void);
};

