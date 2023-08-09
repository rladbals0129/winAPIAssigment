#pragma once
#include "GameNode.h"
class Hole :public GameNode
{
	float _centerX;
	float _centerY;
	float _redius;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getCenterX() { return _centerX; }
	float getCenterY() { return _centerY; }
	float getRedius() { return _redius; }


	Hole();
	~Hole();
};

