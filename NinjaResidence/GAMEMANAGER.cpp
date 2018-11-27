/**
* @file GAMEMANAGER.cpp
* @brief Mainï¿½ï¿½ï¿½[ï¿½vï¿½ï¿½ï¿½ï¿½,Windowï¿½Ö˜A
* @author Toshiya Matsuoka
*/
#include "GAMEMANAGER.h"
#include <ctype.h>
#include <cstdio>
#include <cstdlib>



DirectX* GAMEMANAGER::pDirectX = NULL;
SceneManager* GAMEMANAGER::pSceneManager = NULL;
SoundsManager* GAMEMANAGER::pSoundManager = NULL;
HWND GAMEMANAGER::hWnd = NULL;
bool GAMEMANAGER::isWindowMode = true;
bool GAMEMANAGER::isDeviceLost;
RECT GAMEMANAGER::WinRect;

GAMEMANAGER::GAMEMANAGER(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	hWnd = NULL;
	isWindowMode = true;	
	isDeviceLost = false;
	pDirectX = new DirectX;
	WNDCLASS Wndclass;
	pSoundManager =new SoundsManager;
	//Windows‰Šú‰»î•ñ‚ÌÝ’è
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = ApiName;	//ƒNƒ‰ƒX–¼
	//Window‚Ì“o˜^
	RegisterClass(&Wndclass);
	//Window‚Ì¶¬
	hWnd = CreateWindow(
		ApiName,					//ƒEƒBƒ“ƒhƒE‚ÌƒNƒ‰ƒX–¼
		ApiName, 					//ƒEƒBƒ“ƒhƒE‚Ìƒ^ƒCƒgƒ‹
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ƒEƒBƒ“ƒhƒEƒXƒ^ƒCƒ‹
		CW_USEDEFAULT,						// ƒEƒBƒ“ƒhƒE‚Ì‰¡•ûŒü‚ÌˆÊ’ux
		CW_USEDEFAULT,						// ƒEƒBƒ“ƒhƒE‚Ìc•ûŒü‚ÌˆÊ’uy
		DISPLAY_WIDTH,						// Widthi•j
		DISPLAY_HEIGHT,						// Heighti‚‚³j
		NULL,
		NULL,
		hInstance,							// ƒAƒvƒŠƒP[ƒVƒ‡ƒ“ƒCƒ“ƒXƒ^ƒ“ƒX‚Ìƒnƒ“ƒhƒ‹
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	pSoundManager->Initialize();
	pDirectX->InitPresentParameters(hWnd);
	pDirectX->BuildDXDevice(hWnd, isWindowMode, "texture/Block_Integration.png");

}

GAMEMANAGER::~GAMEMANAGER()
{
	delete pDirectX;
	delete pSoundManager;
}


// ‰æ–Êƒ‚[ƒh‚Ì•ÏX
void GAMEMANAGER::ChangeDisplayMode(void)
{
	HRESULT hr = NULL;
	isWindowMode = !isWindowMode;
	pDirectX->ClearDisplay();
	pDirectX->DrawSceneBegin();
	pDirectX->DrawSceneEnd();
	pDirectX->PresentsDevice();

	hr = pDirectX->ResetDevice(isWindowMode, &WinRect,hWnd);

	pDirectX->ReleaseDx();
	pDirectX->BuildDXDevice(hWnd, isWindowMode, "texture/Block_Integration.png");
	//MUST:ƒtƒ@ƒCƒ‹‚ÌÄ“Çž
	pSoundManager->Initialize();
	pSceneManager->ReadTexture();

	if (FAILED(hr)) {
		if (hr == D3DERR_DEVICELOST) {
			isDeviceLost = true;
		}
		if (hr == D3DERR_DRIVERINTERNALERROR) {
			DestroyWindow(hWnd);
		}
		return;
	}

	if (isWindowMode) {
		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		SetWindowPos(hWnd, HWND_NOTOPMOST,
			WinRect.left, WinRect.top,
			WinRect.right - WinRect.left,
			WinRect.bottom - WinRect.top,
			SWP_SHOWWINDOW);
	}
	else {
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}
}

//ƒƒbƒZ[ƒWˆ—@ƒEƒBƒ“ƒhƒEƒvƒƒV[ƒWƒƒWndProc‚ÌÝ’è
LRESULT CALLBACK GAMEMANAGER::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SYSKEYDOWN:     // Alt + “ÁŽêƒL[‚Ìˆ—‚ÉŽg‚¤
		switch (wp) {
		case VK_RETURN:     // Alt + Enter‚ð‰Ÿ‚·‚ÆØ‚è‘Ö‚¦
			ChangeDisplayMode();
			return 0;
		case VK_F4:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		default:
			return 0;
		}
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

int GAMEMANAGER::MessageLoop()
{
	MSG msg;
	DWORD SyncOld = timeGetTime();	//	ƒVƒXƒeƒ€ŽžŠÔ‚ðŽæ“¾
	DWORD SyncNow;
	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	pSceneManager = new SceneManager(pDirectX,pSoundManager);
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)//1•bŠÔ‚É60‰ñ‚±‚Ì’†‚É“ü‚é‚Í‚¸
			{
				pDirectX->CheckKeyStatus();
				pDirectX->ClearDisplay();
				//ƒV[ƒ“‚ÌUpdate‚ÆRender
				pSceneManager->Update();
				pSceneManager->Render();
				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);
	delete pSceneManager;
	
	return (int)msg.wParam;
}


//ƒƒCƒ“ƒ‹[ƒ`ƒ“
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GAMEMANAGER* pGameManager = new GAMEMANAGER(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
	pGameManager->MessageLoop();
	delete pGameManager;
}
