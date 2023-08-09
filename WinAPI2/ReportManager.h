#pragma once
#include "GameNode.h"
#include "MainGame11.h"
#include "MainGame12.h"
#include "MainGame13.h"
#include "MainGame14.h"
#include "MainGame15.h"
#include "MainGame16.h"
#include "CarRaceGame.h"
#include "BlackHoll.h"
#define GAME_CNT 8

struct BUTTON
{
	RECT rc;
	char Text[128];

};
enum SELECT
{
	LOBBY,
	MG11, MG12,
	MG13, MG14,
	MG15, MG16,
	CAR, BLACKHOLE

};

/*enum class CURRENT_RECT : UINT8 
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_NULL
};*/

class ReportManager : public GameNode
{
private:
	//GameNode* currentscene;
	MainGame11* mg11;
	MainGame12* mg12;
    MainGame13* mg13;
	MainGame14* mg14;
	MainGame15* mg15;
	MainGame16* mg16;
	CarRaceGame* car;
	BlackHoll* _blackHole;

	SELECT _select;
	BUTTON _bt[GAME_CNT];

	int _gameNum;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void lobbyRender(void);
};

