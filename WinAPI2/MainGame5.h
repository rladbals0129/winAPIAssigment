#pragma once
#include "GameNode.h"

struct CheckRC
{
	RECT rc;
	bool anser;
};


class MainGame5 : public GameNode
{
private:
	enum GameMode
	{
		stage1,
		stage2,
		gameOver,
		gameClear
	};
	GameMode _gameMode;
	GImage* _stage1;
	GImage* _stage2;
	CheckRC checkStage1[4];
	CheckRC checkStage2[7];

	//RECT _rc1[4];
	//RECT _rc2[7];
	//RECT _timerRC;
	int _timer;
	int _delay;

	bool _minus;
	bool _gameOver;
	bool _stage1Clear;
	bool _gameClear;
	
public:

	HRESULT init();
	void release(void);
	void update(void);
	void render(void);



};

