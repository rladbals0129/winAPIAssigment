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
#include "C3DVector.h"
#include "ShootingMap.h"


struct Button
{
	RECT rect;
	string text;

	Button(int left, int top, int width, int height, const string& buttonText)
	{
		rect.left = left;
		rect.top = top;
		rect.right = left + width;
		rect.bottom = top + height;
		text = buttonText;
	}
};
enum SELECT
{
	LOBBY,
	MG11, MG12,
	MG13, MG14,
	MG15, MG16,
	CAR, BLACKHOLE,
	C3DVECTOR,SHOOTING

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
	ShootingMap* _shooting;
	BlackHoll* _blackHole;
	C3DVector* _c3dvector;
	SELECT _select;
	
	int _gameNum;
	//BUTTON _bt[GAME_CNT];


	vector<Button> _buttons;
	const int _buttonWidth = 150;
	const int _buttonHeight = 100;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void lobbyRender(void);
	void onButtonClick(int buttonIndex);
};

