/**
* @file GAMEMANAGER.h
* @brief Main���[�v����
* @author Toshiya Matsuoka
*/
#pragma once

#include "DirectX.h"
#include "SceneManager.h"
#include "SoundsManager.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib,"SoundLib.lib")

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

using SoundLib::SoundsManager;

class SceneManager;

static class GAMEMANAGER
{
public:
	GAMEMANAGER(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow);
	~GAMEMANAGER();
	int MessageLoop();
	static void ChangeDisplayMode(void);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
private:
	const char ApiName[10] = "�E�҉��~";
	static DirectX* pDirectX;
	static SceneManager* pSceneManager;
	static HWND hWnd;
	static bool isWindowMode;	//true:Window�@false:Full
	static bool isDeviceLost;
	static RECT WinRect;			//Window Mode �ł̈ʒu�傫��
	static SoundLib::SoundsManager* pSoundManager;
};
