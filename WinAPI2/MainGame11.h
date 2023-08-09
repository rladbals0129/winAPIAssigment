#pragma once
#include "GameNode.h"
class MainGame11 : public GameNode
{
private:
	enum GameMode {
		game,end
	};
	GameMode _gameMode;
	RECT _rc[9];
	int _rcIdx[9];
	RECT _clearRC;

	RECT _rcAns[9];
	int _rcAnsIdx[9];

	bool _endCheck[9];

	int _cntA;
	int _alphaA;

	int _cntAnsA;
	int _cntAnsAlpha;


public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
	void shuffleMap();
};

