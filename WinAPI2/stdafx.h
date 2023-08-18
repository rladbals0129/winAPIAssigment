#pragma once
#pragma warning(disable : 4005)
#include <SDKDDKVER.h>
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")  //?



#pragma comment (lib,"msimg32.lib")

#include <Windows.h>
#include <mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

//#include <windows.h>

//! C런타임 헤더파일
#include <stdlib.h> 
#include <malloc.h>
#include <memory.h> 
#include <tchar.h> 
#include <time.h>

#include <stdio.h>

#include <iostream>

#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map> 
#include <algorithm> 
#include <functional>
#include <cassert> 
#include <bitset>

using namespace std;

#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "Utils.h"
#include "TimeManager.h"

#define PI 3.141592
#define REDIAN(dig) ((dig) * PI) / 180.0f

using namespace MY_UTIL;



#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()

#define WINNAME		(LPTSTR)(TEXT("WindowsAPI"))

//전체화면
//#define FULLSCREEN

#ifdef FULLSCREEN

#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	GetSystemMetrics(SM_CXSCREEN) //GetSystemMetrics()인자로 전달되는 시스템 설정 정보를 반환
#define WINSIZE_Y	GetSystemMetrics(SM_CYSCREEN) //SM_CXSCREEN ,SM_CYSCREEN 현제 화면 해상도 반환(x,y축) 
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE


#else
#define WINSTART_X	0
#define WINSTART_Y	0
#define WINSIZE_X	1280
#define WINSIZE_Y	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#endif

#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}
#define SAFE_RELEASE(p)	{if(p) {(p)->release(); (p) = nullptr; }}


extern HINSTANCE _hInstance;
extern HWND      _hWnd;

extern POINT	 _ptMouse;



