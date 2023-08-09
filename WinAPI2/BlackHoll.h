#pragma once
#include "GameNode.h"
#include "Hole.h"
#include "Object.h"
#include <math.h>
#define MAX_OBJECT 1000
#define PI 3.141592

class BlackHoll : public GameNode
{
private:
	Hole* _hole;
	//Object* _object;
	vector<Object> _object;
	float _radian;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createDust();

	BlackHoll() {}
	~BlackHoll() {}
};

