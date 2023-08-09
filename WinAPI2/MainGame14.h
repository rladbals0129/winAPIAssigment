#pragma once
#include "GameNode.h"
class MainGame14 : public GameNode
{
private:

	int _count;
	int _index;
	bool _isLeft;
	bool _isAttack;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

