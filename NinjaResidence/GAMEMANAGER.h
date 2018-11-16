#pragma once

#include "DirectXlib.h"
#include "SceneManager.h"

#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

#define _CRTDBG_MAP_ALLOC
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

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
	static DirectX* pDirectX;
	static SceneManager* pSceneManager;
	static HWND hWnd;
	static bool WinMode;	//true:WindowÅ@false:Full
	static bool DeviceLost;
	static RECT WinRect;			//Window Mode Ç≈ÇÃà íuëÂÇ´Ç≥

};

