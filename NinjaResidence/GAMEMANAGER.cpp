#include "GAMEMANAGER.h"

DirectX* GAMEMANAGER::pDirectX;
SceneManager* GAMEMANAGER::pSceneManager;
HWND GAMEMANAGER::hWnd = NULL;
bool GAMEMANAGER::WinMode = true;
bool GAMEMANAGER::DeviceLost = false;
RECT GAMEMANAGER::WinRect;

GAMEMANAGER::GAMEMANAGER(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	hWnd = NULL;
	WinMode = true;	
	DeviceLost = false;
	pDirectX = new DirectX;
	WNDCLASS Wndclass;
	//Windows初期化情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TEXT("忍者屋敷");	//クラス名
											//Windowの登録
	RegisterClass(&Wndclass);
	//Windowの生成
	hWnd = CreateWindow(
		TEXT("忍者屋敷"),					//ウィンドウのクラス名
		TEXT("忍者屋敷"), 					//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		DISPLAY_WIDTH,						// Width（幅）
		DISPLAY_HEIGHT,						// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	pDirectX->InitPresentParameters(hWnd);
	pDirectX->BuildDXDevice(hWnd, WinMode, "texture/Block_Integration.png");

}

GAMEMANAGER::~GAMEMANAGER()
{
	delete pDirectX;
}


// 画面モードの変更
void GAMEMANAGER::ChangeDisplayMode(void)
{
	HRESULT hr = NULL;
	WinMode = !WinMode;
	pDirectX->ClearDisplay();
	pDirectX->DrowSceneBegin();
	pDirectX->DrowSceneEnd();
	pDirectX->PresentsDevice();

	hr = pDirectX->ResetDevice(WinMode, &WinRect,hWnd);

	pDirectX->ReleaseDx();
	pDirectX->BuildDXDevice(hWnd, WinMode, "texture/Block_Integration.png");
	//MUST:ファイルの再読込
	pSceneManager->ReadTexture();

	if (FAILED(hr)) {
		if (hr == D3DERR_DEVICELOST) {
			DeviceLost = true;
		}
		if (hr == D3DERR_DRIVERINTERNALERROR) {
			DestroyWindow(hWnd);
		}
		return;
	}

	if (WinMode) {
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

//メッセージ処理　ウィンドウプロシージャWndProcの設定
LRESULT CALLBACK GAMEMANAGER::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SYSKEYDOWN:     // Alt + 特殊キーの処理に使う
		switch (wp) {
		case VK_RETURN:     // Alt + Enterを押すと切り替え
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
	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;
	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	pSceneManager = new SceneManager(pDirectX);
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
			if (SyncNow - SyncOld >= 1000 / 60)//1秒間に60回この中に入るはず
			{
				pDirectX->CheckKeyStatus();
				pDirectX->ClearDisplay();
				//シーンのUpdateとRender
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


//メインルーチン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GAMEMANAGER* pGameManager = new GAMEMANAGER(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
	pGameManager->MessageLoop();
	delete pGameManager;
}
