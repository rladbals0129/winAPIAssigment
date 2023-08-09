#include "stdafx.h"
#include "ReportManager.h"

HRESULT ReportManager::init()
{
	GameNode::init(true);

	_gameNum = 0;

	for (int i = 0; i < GAME_CNT; i++)
	{
		if (i < 4)
		{ 
			_bt[i].rc = RectMakeCenter(100, 100 + (i * 150), 100, 80);
		}
		else if (i >= 4)
		{
			_bt[i].rc = RectMakeCenter(WINSIZE_X / 4, 100 + ((i - 4) * 150), 100, 80);
		}/*
		else
		{
			_bt[i].rc = RectMakeCenter(WINSIZE_X - 100, 100 + ((i - 5) * 150), 100, 80);
		}*/
	}

	return S_OK;
}

void ReportManager::release(void)
{
	GameNode::release();
}

void ReportManager::update(void)
{
	if (_select == LOBBY)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < GAME_CNT; i++)
			{
				if (PtInRect(&_bt[i].rc, _ptMouse))
				{
					_gameNum = i;
					switch (i)
					{
					case 0:
						mg11 = new MainGame11;
						mg11->init();
						
						_select = MG11;
						break;
					case 1:

						mg12 = new MainGame12;
						mg12->init();
						
						_select = MG12;
						break;
					case 2:
						mg13 = new MainGame13;
						
						mg13->init();
					
						_select = MG13;
						break;
					case 3:
						mg14 = new MainGame14;
						
						mg14->init();
					
						_select = MG14;
						break;
					case 4:mg15 = new MainGame15;
					

						mg15->init();
						
						_select = MG15;
						break;
					case 5:
						mg16 = new MainGame16;
					
						mg16->init();

						_select = MG16;
						break;
					case 6:
						car = new CarRaceGame;
						car->init();

						_select = CAR;
						break;
					case 7:
						_blackHole = new BlackHoll;
						_blackHole->init();

						_select = BLACKHOLE;
						break;
					case 8:

						break;
					default:
						break;
					}
				}


			}
		}
	}
	if (_select == MG11)
	{
		mg11->update();
	}
	if (_select == MG12)
	{
		mg12->update();
	}
	if (_select == MG13)
	{
		mg13->update();
	}
	if (_select == MG14)
	{
		mg14->update();
	}
	if (_select == MG15)
	{
		mg15->update();
	}
	if (_select == MG16)
	{
		mg16->update();
	}
	if (_select == CAR)
	{
		car->update();
	}
	if (_select == BLACKHOLE)
	{
		_blackHole->update();
	}
	//cout << _gameNum << endl;
	//cout << _select << endl;

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		
			switch (_gameNum)
			{
			case 0:
				mg11->release();
				break;
			case 1:
				mg12->release();
				break;
			case 2:	
				mg13->release();
				break;
			case 3:	
				mg14->release();
				break;
			case 4:
				mg15->release();
				break;
			case 5:	
				mg16->release();
				break;
			case 6:	car->release();
				break;

			case 7: _blackHole->release();
				break;
			}
		
	
		_select = LOBBY;
	
	

	
	

	

	}

	
	
//	mg12->update();
//	mg13->update();
//	mg14->update();
//mg15->update();
}

void ReportManager::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	wsprintf(_bt[0].Text, "슬라이드퍼즐");
	wsprintf(_bt[1].Text, "맵이동");
	wsprintf(_bt[2].Text, "지렁이");
	wsprintf(_bt[3].Text, "제로공격");
	wsprintf(_bt[4].Text, "프레임이미지");
	wsprintf(_bt[5].Text, "벽 타기");
	wsprintf(_bt[6].Text, "레이싱");
	wsprintf(_bt[7].Text, "블랙홀");
	if (_select == LOBBY)
	{
		lobbyRender();
	}
	if (_select == MG11)
	{
		mg11->render();
	}
	if (_select == MG12)
	{
		mg12->render();
	}
	if (_select == MG13)
	{
		mg13->render();
	}
	if (_select == MG14)
	{
		mg14->render();
	}
	if (_select == MG15)
	{
		mg15->render();
	}
	if (_select == MG16)
	{
		mg16->render();
	}
	if (_select == CAR)
	{
		car->render();
	}
	if (_select == BLACKHOLE)
	{
		_blackHole->render();
	}
	
//	mg12->render();
//	mg13->render();
//	mg14->render();
//	mg15->render();

}

void ReportManager::lobbyRender(void)
{
	for (int i = 0; i < GAME_CNT; i++)
	{
		DrawRectMake(getMemDC(), _bt[i].rc);
		TextOut(getMemDC(), (_bt[i].rc.left + _bt[i].rc.right) / 2 - strlen(_bt[i].Text) * 4,
			(_bt[i].rc.top + _bt[i].rc.bottom) / 2 - strlen(_bt[i].Text),
			_bt[i].Text, strlen(_bt[i].Text));
		this->getBackBuffer()->render(getHDC());
	}

}
