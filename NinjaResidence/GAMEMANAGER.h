/**
* @file GAMEMANAGER.h
* @brief Main���[�v����,Window�֘A
* @author Toshiya Matsuoka
*/
#pragma once

#include "DirectX.h"
#include "SceneManager.h"
#include "SoundsManager.h"


#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

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
	static SoundsManager* pSoundManager;
};
