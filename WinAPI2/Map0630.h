#pragma once
#include "GameNode.h"
class Map0630 : public GameNode
{
	RECT _gournd;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Map0630();
	~Map0630();
};

